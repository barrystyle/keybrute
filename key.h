#ifndef KEY_H
#define KEY_H

#include <openssl/rand.h>

#include <openssl/ripemd.h>
#include <openssl/sha.h>

#include <secp256k1.h>

void random_privkey(unsigned char* pk);
void priv_to_public(secp256k1_context* ctx, unsigned char* pk, unsigned char* pkh);

#endif // KEY_H
