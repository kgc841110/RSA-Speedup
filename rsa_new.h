#ifndef RSA_NEW_H
#define RSA_NEW_H

#include <openssl/bn.h>

void generateKeys(BIGNUM *p, BIGNUM *q, BIGNUM *d, BIGNUM *dp, BIGNUM *dq,//sk parameters
                  BIGNUM *d_p1, BIGNUM *d_p0, BIGNUM *d_q1, BIGNUM *d_q0,
                  BIGNUM *d1_p, BIGNUM *d0_p, BIGNUM *d1_q, BIGNUM *d0_q,
                  BIGNUM *n, BIGNUM *e, BIGNUM *h, BN_CTX *ctx);//pk parameters

void generateKeys_rebalanced(BIGNUM *p, BIGNUM *q, BIGNUM *d, BIGNUM *dp, BIGNUM *dq,//sk parameters
                  BIGNUM *n, BIGNUM *e, BN_CTX *ctx);//pk parameters

void encrypt_rebalanced(BIGNUM *c, BIGNUM *m, BIGNUM *e, BIGNUM *n, BN_CTX *ctx);

void decrypt_rebalanced(BIGNUM *m, BIGNUM *c, BIGNUM *p, BIGNUM *q, BIGNUM *qinv, BIGNUM *dp, BIGNUM *dq, BN_CTX *ctx);

void encrypt_crt(BIGNUM *c, BIGNUM *m, BIGNUM *e, BIGNUM *n, BN_CTX *ctx);

void decrypt_crt(BIGNUM *m, BIGNUM *c, BIGNUM *p, BIGNUM *q, BIGNUM *qinv, BIGNUM *dp, BIGNUM *dq, BN_CTX *ctx);

void encrypt_scheme1(BIGNUM *c, BIGNUM *m, BIGNUM *e, BIGNUM *n, BIGNUM *h, BIGNUM *z, BN_CTX *ctx);

void decrypt_scheme1(BIGNUM *m, BIGNUM *c, BIGNUM *p, BIGNUM *q, BIGNUM *qinv, BIGNUM *d_p1,BIGNUM *d_p0, BIGNUM *d_q1, BIGNUM *d_q0, BIGNUM *zz, BN_CTX *ctx);

void encrypt_scheme2(BIGNUM *c, BIGNUM *m, BIGNUM *e, BIGNUM *n, BIGNUM *h, BIGNUM *z, BN_CTX *ctx);

void decrypt_scheme2(BIGNUM *m, BIGNUM *c, BIGNUM *p, BIGNUM *q, BIGNUM *qinv, BIGNUM *zz, BIGNUM *d1p, BIGNUM *d1q, BIGNUM *d0p, BIGNUM *d0q, BN_CTX *ctx);

char *convert_hex2binary(char hex);

char *convert_bn2binary(BIGNUM *bn);

void mod_exp_speedup(BIGNUM *r, BIGNUM *a, BIGNUM *p, BIGNUM *m, BN_CTX *ctx);

void mod_exp_montgomery(BIGNUM *r, BIGNUM *a, BIGNUM *p, BIGNUM *m, BN_CTX *ctx);

void mod_exp_simultaneity(BIGNUM *r, BIGNUM *a, BIGNUM *p, BIGNUM *b, BIGNUM *q, BIGNUM *m, BN_CTX *ctx);

#endif // RSA_NEW_H
