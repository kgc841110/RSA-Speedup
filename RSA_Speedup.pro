# -------------------------------------------------
# Project created by QtCreator 2021-12-02T19:12:30
# -------------------------------------------------
TARGET = RSA_Speedup
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    rsa_keygen.cpp \
    rsa_crypt.cpp \
    openssl/base64.cpp \
    openssl/applink.c
HEADERS += rsa_new.h \
    openssl/x509v3.h \
    openssl/x509_vfy.h \
    openssl/x509.h \
    openssl/whrlpool.h \
    openssl/ui_compat.h \
    openssl/ui.h \
    openssl/txt_db.h \
    openssl/ts.h \
    openssl/tls1.h \
    openssl/symhacks.h \
    openssl/stack.h \
    openssl/ssl23.h \
    openssl/ssl3.h \
    openssl/ssl2.h \
    openssl/ssl.h \
    openssl/srtp.h \
    openssl/srp.h \
    openssl/sha.h \
    openssl/seed.h \
    openssl/safestack.h \
    openssl/rsa.h \
    openssl/ripemd.h \
    openssl/rc4.h \
    openssl/rc2.h \
    openssl/rand.h \
    openssl/pqueue.h \
    openssl/pkcs12.h \
    openssl/pkcs7.h \
    openssl/pem2.h \
    openssl/pem.h \
    openssl/ossl_typ.h \
    openssl/opensslv.h \
    openssl/opensslconf.h \
    openssl/ocsp.h \
    openssl/objects.h \
    openssl/obj_mac.h \
    openssl/modes.h \
    openssl/mdc2.h \
    openssl/md5.h \
    openssl/md4.h \
    openssl/lhash.h \
    openssl/kssl.h \
    openssl/krb5_asn.h \
    openssl/idea.h \
    openssl/hmac.h \
    openssl/evp.h \
    openssl/err.h \
    openssl/engine.h \
    openssl/ecdsa.h \
    openssl/ecdh.h \
    openssl/ec.h \
    openssl/ebcdic.h \
    openssl/e_os2.h \
    openssl/dtls1.h \
    openssl/dso.h \
    openssl/dsa.h \
    openssl/dh.h \
    openssl/des_old.h \
    openssl/des.h \
    openssl/crypto.h \
    openssl/cryptlib.h \
    openssl/conf_api.h \
    openssl/conf.h \
    openssl/comp.h \
    openssl/cms.h \
    openssl/cmac.h \
    openssl/cast.h \
    openssl/camellia.h \
    openssl/buffer.h \
    openssl/bn.h \
    openssl/blowfish.h \
    openssl/bio.h \
    openssl/base64.h \
    openssl/asn1t.h \
    openssl/asn1_mac.h \
    openssl/asn1.h \
    openssl/aes.h
FORMS += mainwindow.ui
LIBS += ./libeay32.dll
