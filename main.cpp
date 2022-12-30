#include <QtCore/QCoreApplication>
#include <stdio.h>
#include <windows.h>
#include <openssl/bn.h>
#include <rsa_new.h>

#define NUM 100

BIGNUM *h1, *e;
BIGNUM *pp[NUM], *qq[NUM], *qqinv[NUM], *nn[NUM], *dd[NUM], *ee[NUM], *cc[NUM], *mm[NUM], *mm0[NUM], *mm1[NUM], *mm2[NUM],  *mmr[NUM], *ddpp[NUM],
 *ddqq[NUM], *zz1[NUM], *zz2[NUM], *d1_pp[NUM], *d1_qq[NUM], *d0_pp[NUM], *d0_qq[NUM], *hh[NUM], *d1_p[NUM], *d1_q[NUM], *d0_p[NUM], *d0_q[NUM];
BN_CTX *ctx;
BN_MONT_CTX *mont;

void init_func()
{
    h1=BN_new();
    e=BN_new();
    BN_set_bit(h1, 512);//h1=2^512
    ctx=BN_CTX_new();
    mont=BN_MONT_CTX_new();

    for(int i=0; i<NUM; i ++)
    {
       pp[i]=BN_new();
       qq[i]=BN_new();
       qqinv[i]=BN_new();
       nn[i]=BN_new();
       dd[i]=BN_new();
       ee[i]=BN_new();
       cc[i]=BN_new();
       mm[i]=BN_new();
       mm0[i]=BN_new();
       mm1[i]=BN_new();
       mm2[i]=BN_new();
       mmr[i]=BN_new();
       ddpp[i]=BN_new();
       ddqq[i]=BN_new();
       zz1[i]=BN_new();
       zz2[i]=BN_new();
       d1_pp[i]=BN_new();
       d1_qq[i]=BN_new();
       d0_pp[i]=BN_new();
       d0_qq[i]=BN_new();
       d1_p[i]=BN_new();
       d1_q[i]=BN_new();
       d0_p[i]=BN_new();
       d0_q[i]=BN_new();
       hh[i]=BN_new();
   }
}
void free_func()
{
    BN_free(h1);
    BN_free(e);
    BN_CTX_free(ctx);
    BN_MONT_CTX_free(mont);
    for(int i=0; i<NUM; i ++)
    {
        BN_free(pp[i]);
        BN_free(qq[i]);
        BN_free(qqinv[i]);
        BN_free(nn[i]);
        BN_free(dd[i]);
        BN_free(ee[i]);
        BN_free(cc[i]);
        BN_free(mm[i]);
        BN_free(mm0[i]);
        BN_free(mm1[i]);
        BN_free(mm2[i]);
        BN_free(mmr[i]);
        BN_free(ddpp[i]);
        BN_free(ddqq[i]);
        BN_free(zz1[i]);
        BN_free(zz2[i]);
        BN_free(d1_pp[i]);
        BN_free(d0_pp[i]);
        BN_free(d1_qq[i]);
        BN_free(d0_qq[i]);
        BN_free(d1_p[i]);
        BN_free(d0_p[i]);
        BN_free(d1_q[i]);
        BN_free(d0_q[i]);
        BN_free(hh[i]);
   }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    init_func();//variables clear

    //Message generation
    printf("-----------------------  Generating messages...  -------------------------\n");
    for(int i=0; i<NUM; i++){
        BN_rand(mm[i], 2046, NULL, NULL);//message generation
    }

    //Key generation
    printf("-----------------------  Generating keys...  -------------------------\n");
    for(int i=0; i<NUM; i++){
        generateKeys(pp[i], qq[i], dd[i], ddpp[i], ddqq[i], d1_p[i], d0_p[i], d1_q[i], d0_q[i], d1_pp[i], d0_pp[i], d1_qq[i], d0_qq[i], nn[i], e, hh[i], ctx);//key generation
        BN_mod_inverse(qqinv[i], qq[i], pp[i], ctx);//q_inv=q^-1 mod p
        printf("%3d", i+1);
    }
    printf("\nKey Generation Success!\n");

    //##################################### RSA-CRT #############################################

    //encryption (CRT)
    printf("\n-----------------------  Encrypting messages(CRT)...  ----------------\n");

    DWORD t1=GetTickCount();
    for(int i=0; i<NUM; i++){        
        encrypt_crt(cc[i], mm[i], e, nn[i], ctx);//encrytion
    }
    DWORD t2=GetTickCount();
    printf("RSA-CRT Encryption time = %fms\n", (t2-t1)*1.0 / NUM);

    //decryption(CRT)
    printf("\n-----------------------  Decrypting messages(CRT)...  --------------\n");

    t1=GetTickCount();
    for(int i=0; i<NUM; i++){        
        decrypt_crt(mm0[i], cc[i], pp[i], qq[i], qqinv[i],ddpp[i], ddqq[i], ctx); //decryption (CRT)
    }
    t2=GetTickCount();
    printf("RSA-CRT Decryption time = %fms\n", (t2-t1)*1.0 / NUM);

    //verifying(CRT)
    printf("\n-----------------------  Verifying messages(CRT)...  --------------\n");
    int flag = 1;
    for(int i=0; i<NUM; i++)
    {
        flag=BN_cmp(mm[i], mm0[i]); //if mm[i]=mm0[i] then flag = 0;
        if(flag != 0)
        {
            printf("%d error occured!\n", i);
        }
    }
    printf("Decryption and Verification(CRT) completed\n");

    //##################################### Scheme1 #############################################

    //encryption(scheme1)
    printf("\n\n-----------------------  Encrypting messages(Scheme1)...  --------------\n");

    t1=GetTickCount();
    for(int i=0; i<NUM; i++){
        encrypt_scheme1(cc[i], mm[i], e, nn[i], h1, zz1[i], ctx);//encryption
    }
    t2=GetTickCount();
    printf("Scheme1 Encryption time = %fms\n", (t2-t1)*1.0 / NUM);

    //decryption (scheme1)
    printf("\n-----------------------  Decrypting messages(Scheme1)...  ------------\n");
    t1=GetTickCount();
    for(int i=0; i<NUM; i++){        
        decrypt_scheme1(mm1[i], cc[i], pp[i], qq[i], qqinv[i], d1_p[i], d0_p[i], d1_q[i], d0_q[i], zz1[i], ctx);
    }
    t2=GetTickCount();
    printf("Scheme1 Decryption time = %fms\n", (t2-t1)*1.0 / NUM);

    //verifying(Scheme1)
    printf("\n-----------------------  Verifying messages(Scheme1)...  --------------\n");
    flag = 1;
    for(int i=0; i<NUM; i++)
    {
        flag=BN_cmp(mm[i], mm1[i]); //if mm[i]=mm1[i] then flag = 0;
        if(flag != 0)
        {
            printf("%d error occured!\n", i);
        }
    }
    printf("Decryption and Verification(Scheme1) completed\n");

    //##################################### Scheme2 #############################################

    //encryption(Scheme2)

    printf("\n\n-----------------------  Encrypting messages(Scheme2)...  ----------\n");
    t1=GetTickCount();
    for(int i=0; i<NUM; i++){
        encrypt_scheme2(cc[i], mm[i], e, nn[i], hh[i], zz2[i], ctx);//encryption
    }
    t2=GetTickCount();
    printf("Scheme2 Encryption time = %fms\n", (t2-t1)*1.0 / NUM);
  
    //decryption (Scheme2)
    printf("\n-----------------------  Decrypting messages(Scheme2)...  ----------\n");    
    t1=GetTickCount();
    for(int i=0; i<NUM; i++){        
        decrypt_scheme2(mm2[i], cc[i], pp[i], qq[i], qqinv[i], zz2[i], d1_pp[i], d1_qq[i], d0_pp[i], d0_qq[i], ctx);//decryption (new)
    }
    t2=GetTickCount();
    printf("Scheme2 Decryption time = %fms\n", (t2-t1)*1.0 / NUM);

    //verifying(Scheme2)
    printf("\n-----------------------  Verifying messages(Scheme2)...  --------------\n");
    flag = 1;
    for(int i=0; i<NUM; i++)
    {
        flag=BN_cmp(mm[i], mm2[i]); //if mm[i]=mm2[i] then flag = 0;
        if(flag != 0)
        {
            printf("%d error occured!\n", i);
        }
    }
    printf("Decryption and Verification(Scheme2) completed\n");

    //##################################### Rebalanced RSA #############################################


    //key generation(Rebalanced)
    printf("\n\n-----------------------  Generating keys(Rebalanced RSA)...  ----------------\n");
    for(int i=0; i<NUM; i++){
        generateKeys_rebalanced(pp[i], qq[i], dd[i], ddpp[i], ddqq[i], nn[i], ee[i], ctx);//key generation
        printf("%3d", i+1);
        BN_mod_inverse(qqinv[i], qq[i], pp[i], ctx);
    }
    printf("\nKey Generation(Rebalanced) Success!\n");

    //encryption (rebalanced RSA)
    printf("\n-----------------------  Encrypting messages(Rebalanced RSA)...  ----------\n");
    t1=GetTickCount();
    for(int i=0; i<NUM; i++){        
        encrypt_rebalanced(cc[i], mm[i], ee[i], nn[i], ctx);//encrytion
    }
    t2=GetTickCount();
    printf("Rebalanced RSA Encryption time = %fms\n", (t2-t1)*1.0 / NUM);

    //decryption(Rebalanced RSA)
    printf("\n-----------------------  Decrypting messages(Rebalanced RSA)...  --------\n");
    t1=GetTickCount();
    for(int i=0; i<NUM; i++){        
        decrypt_rebalanced(mmr[i], cc[i], pp[i], qq[i], qqinv[i], ddpp[i], ddqq[i], ctx);//decryption (Rebalanced)
    }
    t2=GetTickCount();
    printf("RSA-CRT Decryption time = %fms\n", (t2-t1)*1.0 / NUM);

    //verifying(Rebalanced RSA)
    printf("\n-----------------------  Verifying messages(Rebalanced RSA)...  --------------\n");
    flag = 1;
    for(int i=0; i<NUM; i++)
    {
        flag=BN_cmp(mm[i], mmr[i]); //if mm[i]=mmr[i] then flag = 0;
        if(flag != 0)
        {
            printf("%d error occured!\n", i);
        }
    }
    printf("Decryption and Verification(Rebalanced RSA) completed\n");

    free_func();//variables free
    return a.exec();
}
