#include "rsa_new.h"
#include "openssl/bn.h"

#define Scheme2_K 112
#define Reb_K 250
#define MOD_SIZE 2048
#define E 65537

void generateKeys(BIGNUM *p, BIGNUM *q, BIGNUM *d, BIGNUM *dp, BIGNUM *dq,//sk parameters
                  BIGNUM *d1_p1, BIGNUM *d0_p1, BIGNUM *d1_q1, BIGNUM *d0_q1, //for Scheme1
                  BIGNUM *d1_p2, BIGNUM *d0_p2, BIGNUM *d1_q2, BIGNUM *d0_q2, //for Scheme2
                  BIGNUM *n, BIGNUM *e, BIGNUM *h2, BN_CTX *ctx)//pk parameters
{
    BIGNUM *fai=BN_new();
    BIGNUM *one=BN_new();
    BIGNUM *two=BN_new();
    BN_one(one);
    BN_set_word(two, 2);//z=2
    BIGNUM *p_1=BN_new();
    BIGNUM *q_1=BN_new();
    BIGNUM *z=BN_new();
    BIGNUM *ze=BN_new();
    BIGNUM *gcd=BN_new();
    BIGNUM *pp=BN_new();
    BIGNUM *qq=BN_new();
    BIGNUM *h1=BN_new(); //h1 for Scheme1
    BN_set_bit(h1, MOD_SIZE/4); //h1=2^512
    int flag=-1;//clear
    BN_set_word(e, E);//e=65537

    // Prime Generation gcd(p-1, q-1) = 2,  gcd((p-1)(q-1), 65537) = 1
    do
    {
        BN_generate_prime_ex(p, MOD_SIZE / 2, NULL, NULL, NULL, NULL);//1024bit p
        BN_generate_prime_ex(q, MOD_SIZE / 2, NULL, NULL, NULL, NULL);//1024bit q
        BN_sub(p_1, p, one);//p_1=p-1
        BN_sub(q_1, q, one);//q_1=q-1
        BN_mul(fai, p_1, q_1, ctx);//fai=(p-1)(q-1) 2048bit
        BN_gcd(ze, e, fai, ctx);//z=gcd((p-1), (q-1))
        BN_gcd(z, p_1, q_1, ctx);//z=gcd((p-1), (q-1))       
    }
    while(BN_cmp(z, two)||BN_cmp(ze, one));

    BN_mul(n, p, q, ctx);//n=p*q 2048bit
    BN_div(pp, NULL, p_1, z, ctx); //pp = (p-1)/2
    BN_div(qq, NULL, q_1, z, ctx); //qq = (q-1)/2

    //Key Generation for RSA_CRT
    BN_mod_inverse(d, e, fai, ctx);//d=e^-1 mod fai 2048bit
    BN_nnmod(dp,d,p_1,ctx); //dp=d mod p-1 1024bit
    BN_nnmod(dq,d,q_1,ctx); //dq=d mod q-1 1024bit

    //Key Generation for Scheme1
    BN_div(d1_p1, d0_p1, dp, h1, ctx);//in dp=1024bit, fist 512bit-d1_p1, second 512bit-d0_p1
    BN_div(d1_q1, d0_q1, dq, h1, ctx);//in dq=1024bit, fist 512bit-d1_q1, second 512bit-d0_q1

    //Scheme1 Key Gen Verifying

    BIGNUM *dp_v=BN_new();
    BIGNUM *dq_v=BN_new();
    BN_mul(dp_v, h1, d1_p1, ctx);
    BN_add(dp_v, dp_v, d0_p1);
    BN_mul(dq_v, h1, d1_q1, ctx);
    BN_add(dq_v, dq_v, d0_q1);

    flag=BN_cmp(dp_v, dp);//if dp_v == dp then flag = 0
    if(flag != 0) printf("+++++++++++++++++++++++++++++++++++++ Scheme1 Key Generation Error!!! +++++++++++++++++++++++++++++++++++++\n");
    flag=BN_cmp(dq_v, dq);//if dq_v == dq then flag = 0
    if(flag != 0) printf("+++++++++++++++++++++++++++++++++++++ Scheme1 Key Generation Error!!! +++++++++++++++++++++++++++++++++++++\n");


    // Key Generation for Scheme2
    do
    {
        BN_rand(d1_p2, Scheme2_K, NULL, NULL);
        BN_gcd(gcd, d1_p2, p_1, ctx);//gcd(d1_p2, p_1)
        flag=BN_cmp(gcd, one);//if gcd==1 then flag = 0
    }
    while(flag!=0); ////gcd!=1

    do
    {
        BN_rand(d1_q2, Scheme2_K, NULL, NULL);
        BN_gcd(gcd, d1_q2, q_1, ctx);//gcd(d1_q2, q_1)
        flag=BN_cmp(gcd, one);//if gcd==1 then flag = 0
    }
    while(flag!=0); //gcd!=1

    BIGNUM *d0p_z=BN_new();
    BIGNUM *d0q_z=BN_new();
    do
    {
        BN_rand(d0_p2, Scheme2_K, NULL, NULL);//112bit do_p
        BN_rand(d0_q2, Scheme2_K, NULL, NULL);//112bit do_q
        BN_nnmod(d0p_z, d0_p2, z, ctx); //d0p_z=d0_p%z
        BN_nnmod(d0q_z, d0_q2, z, ctx);//d0q_z=d0_q%z
        flag=BN_cmp(d0p_z, d0q_z);//if d0p_z==d0q_z, break
    }
    while(flag!=0);

    BIGNUM *d1_p2_inv=BN_new();
    BIGNUM *d1_q2_inv=BN_new();
    BIGNUM *d0_p2_t=BN_new();
    BIGNUM *d0_q2_t=BN_new();
    BIGNUM *hp=BN_new();
    BIGNUM *hq=BN_new();

    BN_mod_inverse(d1_p2_inv, d1_p2, p_1, ctx);//d1_p2_inv=d1_p^-1 mod p_1
    BN_mod_inverse(d1_q2_inv, d1_q2, q_1, ctx);//d1_q2_inv=d1_q^-1 mod q_1
    BN_sub(d0_p2_t, dp, d0_p2);//d0_p2_t=dp-d0_p2
    BN_sub(d0_q2_t, dq, d0_q2);//d0_q2_t=dq-d0_q2
    BN_mod_mul(hp, d0_p2_t, d1_p2_inv, p_1, ctx);//hp=d0_p2_t * d1_p2_inv mod (p-1)
    BN_mod_mul(hq, d0_q2_t, d1_q2_inv, q_1, ctx);//hq=d0_q2_t * d1_q2_inv mod (q-1)

    BIGNUM *hpz=BN_new();
    BIGNUM *hqz=BN_new();
    BIGNUM *hhp=BN_new();
    BIGNUM *hhq=BN_new();
    BIGNUM *qq_inv=BN_new();

    BN_div(hhp, hpz, hp, z, ctx);//hhp=hp/z, hpz=hp%z
    BN_div(hhq, hqz, hq, z, ctx);//hhq=hq/z, hqz=hq%z
    BN_mod_inverse(qq_inv, qq, pp, ctx);//qq_inv=qq^-1 mod pp

    //calculate x
    BIGNUM *hhp_hhq=BN_new();
    BIGNUM *t1=BN_new();
    BIGNUM *t2=BN_new();
    BIGNUM *t3=BN_new();
    BIGNUM *x=BN_new();
    BIGNUM *xz=BN_new();

    BN_sub(hhp_hhq, hhp, hhq);//hhp_hhq=hhp-hhq
    BN_mod_add(t1, hhp_hhq, pp, pp, ctx);//t1=(hhp-hhq+pp) mod pp
    BN_mod_mul(t2, t1, qq_inv, pp, ctx);//t2=((hhp-hhq+pp) mod pp) * qq_inv mod pp
    BN_mul(t3, t2, qq, ctx);//t3=t2 * qq
    BN_add(x, t3, hhq);//x=t3+hhq

    //calculate h2
    BN_mul(xz, x, z, ctx);//xz=x * z
    BN_add(h2, xz, hpz);//h2=xz+hpz

    //Scheme2 Key Gen Verifying

    BN_mod_mul(dp_v, h2, d1_p2, p_1, ctx);
    BN_mod_add(dp_v, dp_v, d0_p2, p_1, ctx);
    BN_mod_mul(dq_v, h2, d1_q2, q_1, ctx);
    BN_mod_add(dq_v, dq_v, d0_q2, q_1, ctx);

    flag=BN_cmp(dp_v, dp);//if dp_v == dp then flag = 0
    if(flag != 0) printf("+++++++++++++++++++++++++++++++++++++ Scheme2 Key Generation Error!!! +++++++++++++++++++++++++++++++++++++\n");
    flag=BN_cmp(dq_v, dq);//if dq_v == dq then flag = 0
    if(flag != 0) printf("+++++++++++++++++++++++++++++++++++++ Scheme2 Key Generation Error!!! +++++++++++++++++++++++++++++++++++++\n");
}

void generateKeys_rebalanced(BIGNUM *p, BIGNUM *q, BIGNUM *d, BIGNUM *dp, BIGNUM *dq,//sk parameters
                  BIGNUM *n, BIGNUM *e, BN_CTX *ctx)//pk parameters
{
    BIGNUM *one=BN_new();
    BIGNUM *two=BN_new();
    BN_one(one);
    BIGNUM *p_1=BN_new();
    BIGNUM *q_1=BN_new();
    BIGNUM *fai=BN_new();
    BIGNUM *z=BN_new();
    BN_set_word(two, 2); //z=2

    do
    {
        BN_generate_prime_ex(p, MOD_SIZE / 2, NULL, NULL, NULL, NULL); //1024bit p
        BN_generate_prime_ex(q, MOD_SIZE / 2, NULL, NULL, NULL, NULL); //1024bit q
        BN_sub(p_1, p, one); //p_1=p-1
        BN_sub(q_1, q, one); //q_1=q-1
        BN_gcd(z, p_1, q_1, ctx); //z=gcd((p-1), (q-1))
    }
    while(BN_cmp(z, two)); // if z=2 then break

    BN_mul(n, p, q, ctx);//n=p*q 2048bit

    BIGNUM *dp_z=BN_new();
    BIGNUM *dq_z=BN_new();

    int flag1=-1, flag2=-1;
    do
    {
        BN_rand(dp, Reb_K, NULL, NULL); //250bit dp
        BN_rand(dq, Reb_K, NULL, NULL); //250bit dq
        BN_nnmod(dp_z, dp, z, ctx); //dp_z=dp%2
        BN_nnmod(dq_z, dq, z, ctx); //dq_z=dq%2
        flag1=BN_cmp(dp_z, one);
        flag2=BN_cmp(dq_z, one);       
    }
    while(flag1 != 0 || flag2 != 0);

    //calculate d
    BIGNUM *dpz=BN_new();
    BIGNUM *dqz=BN_new();
    BIGNUM *ddp=BN_new();
    BIGNUM *ddq=BN_new();
    BIGNUM *qq_inv=BN_new();
    BIGNUM *pp=BN_new();
    BIGNUM *qq=BN_new();

    BN_div(ddp, dpz, dp, z, ctx);//ddp=dp/z, dpz=dp%z
    BN_div(ddq, dqz, dq, z, ctx);//ddq=dq/z, dqz=dq%z
    BN_div(pp, NULL, p_1, z, ctx);
    BN_div(qq, NULL, q_1, z, ctx);
    BN_mod_inverse(qq_inv, qq, pp, ctx);//qq_1=qq^-1 mod pp
    //calculate x
    BIGNUM *ddp_ddq=BN_new();
    BIGNUM *t1=BN_new();
    BIGNUM *t2=BN_new();
    BIGNUM *t3=BN_new();
    BIGNUM *x=BN_new();
    BIGNUM *xz=BN_new();

    BN_sub(ddp_ddq, ddp, ddq);//ddp_ddq=ddp-ddq
    BN_mod_add(t1, ddp_ddq, pp, pp, ctx);//t1=(ddp-ddq+pp) mod pp
    BN_mod_mul(t2, t1, qq_inv, pp, ctx);//t2=((ddp-ddq+pp) mod pp)^qq_inv mod pp
    BN_mul(t3, t2, qq, ctx);//t3=t2^qq
    BN_add(x, t3, ddq);//x=t3+ddq
    //calculate d
    BN_mul(xz, x, z, ctx);//xz=x^z
    BN_add(d, xz, dpz);//d=xz+dpz
    //calculate e
    BN_mul(fai, p_1, q_1, ctx);//fai=(p-1)(q-1) 2048bit
    BN_mod_inverse(e, d, fai, ctx);//e=d^-1 mod fai 2048bit

    //Rebalanced RSA Key Gen Verifying
    int flag;
    BIGNUM *dp_v=BN_new();
    BIGNUM *dq_v=BN_new();
    BN_nnmod(dp_v, d, p_1, ctx);
    BN_nnmod(dq_v, d, q_1, ctx);
    flag=BN_cmp(dp_v, dp);//if dp_v == dp then flag = 0
    if(flag != 0) printf("+++++++++++++++++++++++++++++++++++++ Rebalanced RSA Key Generation Error!!! +++++++++++++++++++++++++++++++++++++\n");
    flag=BN_cmp(dq_v, dq);//if dq_v == dq then flag = 0
    if(flag != 0) printf("+++++++++++++++++++++++++++++++++++++ Rebalanced RSA Key Generation Error!!! +++++++++++++++++++++++++++++++++++++\n");
}
