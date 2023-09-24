#include <key.h>

void random_privkey(unsigned char* pk)
{
    RAND_bytes(pk, 32);
}

void priv_to_public(secp256k1_context* ctx, unsigned char* pk, unsigned char* pkh)
{
    secp256k1_pubkey pubkey;
    secp256k1_ec_pubkey_create(ctx, &pubkey, (const unsigned char*)pk);

    uint8_t pubkey_serialized[33];
    size_t pubkeylen = sizeof(pubkey_serialized);
    secp256k1_ec_pubkey_serialize(ctx, pubkey_serialized, &pubkeylen, &pubkey, SECP256K1_EC_COMPRESSED);

    unsigned char hash[32];
    SHA256(pubkey_serialized, 33, hash);
    RIPEMD160(hash, 32, pkh);
}
