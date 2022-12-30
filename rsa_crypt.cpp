#include <rsa_new.h>
#include <string.h>

void encrypt_crt(BIGNUM *c, BIGNUM *m, BIGNUM *e, BIGNUM *n, BN_CTX *ctx)
{
    BN_mod_exp(c, m, e, n, ctx);
}

void encrypt_scheme1(BIGNUM *c, BIGNUM *m, BIGNUM *e, BIGNUM *n, BIGNUM *h, BIGNUM *z, BN_CTX *ctx)
{
    BN_mod_exp(c, m, e, n, ctx);
    BN_mod_exp(z, c, h, n, ctx);//z=c^h mod n :precalculation
}

void encrypt_scheme2(BIGNUM *c, BIGNUM *m, BIGNUM *e, BIGNUM *n, BIGNUM *h, BIGNUM *z, BN_CTX *ctx)
{
    BN_mod_exp(c, m, e, n, ctx);
    BN_mod_exp(z, c, h, n, ctx);//z=c^h mod n :precalculation
}

void encrypt_rebalanced(BIGNUM *c, BIGNUM *m, BIGNUM *e, BIGNUM *n, BN_CTX *ctx)
{
    BN_mod_exp(c, m, e, n, ctx);
}

void decrypt_crt(BIGNUM *m, BIGNUM *c, BIGNUM *p, BIGNUM *q, BIGNUM *q_inv, BIGNUM *dp, BIGNUM *dq, BN_CTX *ctx)
{
    BIGNUM *cp=BN_new();
    BIGNUM *cq=BN_new();
    BIGNUM *mp=BN_new();
    BIGNUM *mq=BN_new();
    BIGNUM *one=BN_new();
    BN_one(one);

    BN_nnmod(cp, c, p, ctx); //cp = c mod p
    BN_nnmod(cq, c, q, ctx); //cq = c mod q
    BN_mod_exp(mp, cp, dp, p, ctx);//mp=cp^dp mod p
    BN_mod_exp(mq, cq, dq, q, ctx);//mq=cq^dq mod q
    //calculate m
    BIGNUM *mp_mq=BN_new();
    BIGNUM *temp1=BN_new();
    BIGNUM *temp2=BN_new();
    BIGNUM *temp3=BN_new();

    BN_sub(mp_mq, mp, mq);//mp_mq=mp-mq
    BN_mod_add(temp1, mp_mq, p, p, ctx);//temp1=(mp-mq +p)mod p
    BN_mod_mul(temp2, temp1, q_inv, p, ctx);//temp2=((mp-mq +p)mod p)^q_inv mod p
    BN_mul(temp3, temp2, q, ctx);//temp3=( ((mp-mq +p)mod p)^q_inv mod p )*q
    BN_add(m, temp3, mq);//m=temp3+mq
}

void decrypt_scheme1(BIGNUM *m, BIGNUM *c, BIGNUM *p, BIGNUM *q, BIGNUM *q_inv, BIGNUM *d_p1, BIGNUM *d_p0, BIGNUM *d_q1,BIGNUM *d_q0, BIGNUM *zz, BN_CTX *ctx)
{
    BIGNUM *cp=BN_new();
    BIGNUM *cq=BN_new();
    BIGNUM *zp=BN_new();
    BIGNUM *zq=BN_new();
    BIGNUM *one=BN_new();

    BN_one(one);

    BN_nnmod(cp, c, p, ctx);//cp=c mod p
    BN_nnmod(cq, c, q, ctx);//cq=c mod q
    BN_nnmod(zp, zz, p, ctx);//zp=zz mod p
    BN_nnmod(zq, zz, q, ctx);//zq=zz mod q

    //calculate mp, mq
    BIGNUM *mp=BN_new();
    BIGNUM *mq=BN_new();
    mod_exp_simultaneity(mp, cp, d_p0, zp, d_p1, p, ctx);//mp=c^d0p * zz^d1p mod p
    mod_exp_simultaneity(mq, cq, d_q0, zq, d_q1, q, ctx);//mq=c^d0q * zz^d1q mod q

    //calculate m
    BIGNUM *mp_mq=BN_new();
    BIGNUM *temp1=BN_new();
    BIGNUM *temp2=BN_new();
    BIGNUM *temp3=BN_new();

    BN_sub(mp_mq, mp, mq);//mp_mq=mp-mq
    BN_mod_add(temp1, mp_mq, p, p, ctx);//temp1=(mp-mq +p)mod p
    BN_mod_mul(temp2, temp1, q_inv, p, ctx);//temp2=((mp-mq +p)mod p)^q_inv mod p
    BN_mul(temp3, temp2, q, ctx);//temp3=( ((mp-mq +p)mod p)^q_inv mod p )*q
    BN_add(m, temp3, mq);//m=temp3+mq
}

void decrypt_scheme2(BIGNUM *m, BIGNUM *c, BIGNUM *p, BIGNUM *q, BIGNUM *q_inv, BIGNUM *zz, BIGNUM *d1p, BIGNUM *d1q, BIGNUM *d0p, BIGNUM *d0q, BN_CTX *ctx)
{
    BIGNUM *one=BN_new();
    BN_one(one);
    BIGNUM *cp=BN_new();
    BIGNUM *cq=BN_new();
    BIGNUM *zp=BN_new();
    BIGNUM *zq=BN_new();

    BN_nnmod(cp, c, p, ctx);//cp=c mod p
    BN_nnmod(cq, c, q, ctx);//cq=c mod q
    BN_nnmod(zp, zz, p, ctx);//zp=zz mod p
    BN_nnmod(zq, zz, q, ctx);//zq=zz mod q

    //calculate mp, mq
    BIGNUM *mp=BN_new();
    BIGNUM *mq=BN_new();

    mod_exp_simultaneity(mp, zp, d1p, cp, d0p, p, ctx);//mp=zp^d1p * cp^d0p mod p
    mod_exp_simultaneity(mq, zq, d1q, cq, d0q, q, ctx);//mq=zq^d1q * cq^d0q mod q
    //calculate m
    BIGNUM *mp_mq=BN_new();
    BIGNUM *temp1=BN_new();
    BIGNUM *temp2=BN_new();
    BIGNUM *temp3=BN_new();

    BN_sub(mp_mq, mp, mq);//mp_mq=mp-mq
    BN_mod_add(temp1, mp_mq, p, p, ctx);//temp1=(mp-mq +p)mod p
    BN_mod_mul(temp2, temp1, q_inv, p, ctx);//temp2=((mp-mq +p)mod p)^q_inv mod p
    BN_mul(temp3, temp2, q, ctx);//temp3=( ((mp-mq +p)mod p)^q_inv mod p )*q
    BN_add(m, temp3, mq);//m=temp3+mq
}

void decrypt_rebalanced(BIGNUM *m, BIGNUM *c, BIGNUM *p, BIGNUM *q, BIGNUM *q_inv, BIGNUM *dp, BIGNUM *dq, BN_CTX *ctx)
{
    BIGNUM *cp=BN_new();
    BIGNUM *cq=BN_new();
    BIGNUM *mp=BN_new();
    BIGNUM *mq=BN_new();
    BIGNUM *one=BN_new();
    BN_one(one);

    BN_nnmod(cp, c, p, ctx);//cp=c mod p
    BN_nnmod(cq, c, q, ctx);//cq=c mod q
    BN_mod_exp(mp, cp, dp, p, ctx);//mp=cp^dp mod p
    BN_mod_exp(mq, cq, dq, q, ctx);//mq=cq^dq mod q

    //calculate m
    BIGNUM *mp_mq=BN_new();
    BIGNUM *temp1=BN_new();
    BIGNUM *temp2=BN_new();
    BIGNUM *temp3=BN_new();

    BN_sub(mp_mq, mp, mq);//mp_mq=mp-mq
    BN_mod_add(temp1, mp_mq, p, p, ctx);//temp1=(mp-mq +p)mod p
    BN_mod_mul(temp2, temp1, q_inv, p, ctx);//temp2=((mp-mq +p)mod p)^q_inv mod p
    BN_mul(temp3, temp2, q, ctx);//temp3=( ((mp-mq +p)mod p)^q_inv mod p )*q
    BN_add(m, temp3, mq);//m=temp3+mq
}

char *convert_hex2binary(char hex)
{
    char array[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char *bArray[16]={"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
                      "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    for(int i=0; i<16; i++){
        if(hex==array[i]) return bArray[i];
    }
}

char *convert_bn2binary(BIGNUM *bn)
{
    char *temp=new char[bn->dmax*8];
    temp=BN_bn2hex(bn);//getting hex data
    int t_len=strlen(temp);//hex data length
    char *binary[t_len];//binary array
    char *result=new char[(bn->dmax+1)*32];//binary string
    strcpy(result, "");//string clear
    for(int i=0; i<t_len; i++){
        binary[i]=convert_hex2binary(temp[i]);//convert hex to binary string
        strncat(result, binary[i], 4);//adding binary string
    }
    return result;
}

void mod_exp_speedup(BIGNUM *r, BIGNUM *a, BIGNUM *p, BIGNUM *m, BN_CTX *ctx)
{
    char *pp=convert_bn2binary(p);//BIGNUM p-> binary
    int pp_len=strlen(pp);
    BN_one(r);//r=1
    for(int i=0; i<pp_len; i++){
        BN_mul(r, r, r, ctx);//r=r*r
        if(pp[i]=='1') BN_mod_mul(r, r, a, m, ctx);// r=r*a mod m
    }
}

void mod_exp_montgomery(BIGNUM *r, BIGNUM *a, BIGNUM *p, BIGNUM *m, BN_CTX *ctx)
{
    BN_MONT_CTX *mont=NULL;
    mont=BN_MONT_CTX_new();
    BN_MONT_CTX_set(mont, m, ctx);
    BIGNUM *aa=BN_CTX_get(ctx);
    if (a->neg || BN_ucmp(a,m) >= 0)
    {
       BN_nnmod(aa,a,m,ctx);
    }
    else aa=a;

    BN_to_montgomery(r, BN_value_one(), mont, ctx);
    BN_to_montgomery(aa,aa,mont,ctx);
    char *pp=convert_bn2binary(p);//BIGNUM p-> binary
    int pp_len=strlen(pp);
    for(int i=0; i<pp_len; i++){
        BN_mod_mul_montgomery(r, r, r, mont, ctx);//r=r*r
        if(pp[i]=='1') BN_mod_mul_montgomery(r, r, aa, mont, ctx);// r=r*a mod m
    }
    BN_from_montgomery(r, r, mont, ctx);//getting real value r
    if (mont != NULL) BN_MONT_CTX_free(mont);
}

void mod_exp_simultaneity(BIGNUM *r, BIGNUM *a, BIGNUM *p, BIGNUM *b, BIGNUM *q, BIGNUM *m, BN_CTX *ctx)
{
    BIGNUM *ab=BN_new();
    BN_mod_mul(ab, a, b, m, ctx);
    BN_MONT_CTX *mont=NULL;
    mont=BN_MONT_CTX_new();
    BN_MONT_CTX_set(mont, m, ctx);
    BIGNUM *aa=BN_CTX_get(ctx);
    BIGNUM *bb=BN_CTX_get(ctx);
    BIGNUM *aabb=BN_CTX_get(ctx);

    if (a->neg || BN_ucmp(a,m) >= 0)
    {
       BN_nnmod(aa,a,m,ctx);
    }
    else
       aa=a;
    if (b->neg || BN_ucmp(b,m) >= 0)
    {
       BN_nnmod(bb,b,m,ctx);
    }
    else bb=b;

    BN_to_montgomery(r, BN_value_one(), mont, ctx);
    BN_to_montgomery(aabb, ab, mont, ctx);
    BN_to_montgomery(aa,aa,mont,ctx);
    BN_to_montgomery(bb,bb,mont,ctx);

    char *pp=convert_bn2binary(p);//BIGNUM p-> binary
    char *qq=convert_bn2binary(q);//BIGNUM q-> binary
    char *deltas = new char[2048];
    strcpy(deltas, "00000000");

    int plen=strlen(pp);
    int len;
    int qlen = strlen(qq);
    int delta;
    len = plen;

    if(qlen > plen)
    {
        len = qlen;
        delta = (qlen - plen)/8 - 1;
        for(int i = 0; i < delta; i ++) strcat(deltas, "00000000");
        strcat(deltas, pp);
        strcpy(pp, deltas);    
    }
    else if(qlen < plen)
    {
        delta = (plen - qlen)/8 - 1;
        for(int i = 0; i < delta; i ++) strcat(deltas, "00000000");
        strcat(deltas, qq);
        strcpy(qq, deltas);       
    }

    for(int i=0; i<len; i++){
        BN_mod_mul_montgomery(r, r, r, mont, ctx);//r=r*r
        if(pp[i]=='1'&&qq[i]=='1'){
            BN_mod_mul_montgomery(r, r, aabb, mont, ctx);// r=r*ab mod m
        }
        else if(pp[i]=='1'&&qq[i]=='0'){
            BN_mod_mul_montgomery(r, r, aa, mont, ctx);// r=r*aa mod m
        }
        else if(pp[i]=='0'&&qq[i]=='1'){
            BN_mod_mul_montgomery(r, r, bb, mont, ctx);// r=r*bb mod m
        }
    }
    BN_from_montgomery(r, r, mont, ctx);//getting real value r
    if(mont!=NULL) BN_MONT_CTX_free(mont);
}
