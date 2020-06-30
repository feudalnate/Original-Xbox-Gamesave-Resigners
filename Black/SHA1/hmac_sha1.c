#include <string.h>
#include <stdint.h>
#include "hmac.h"

#define SHA_BLOCKSIZE   (64)

/**
* Function to compute the digest
*
* @param k   Secret key
* @param lk  Length of the key in bytes
* @param d   Data
* @param ld  Length of data in bytes
* @param out Digest output
* @param t   Size of digest output
*/
void hmac_sha1(const uint8_t *k, size_t lk, const uint8_t *d, size_t ld, uint8_t *out) {

    SHA_CTX ictx, octx;
    uint8_t isha[SHA_DIGEST_LENGTH], osha[SHA_DIGEST_LENGTH];
    uint8_t key[SHA_DIGEST_LENGTH];
    uint8_t buf[SHA_BLOCKSIZE];
    size_t i;

    if (lk > SHA_BLOCKSIZE) {
        SHA_CTX tctx;
        SHA1_Init(&tctx);
        SHA1_Update(&tctx, k, lk);
        SHA1_Final(key, &tctx);
        k = key;
        lk = SHA_DIGEST_LENGTH;
    }

    /**** Inner Digest ****/

    SHA1_Init(&ictx);

    /* Pad the key for inner digest */
    for (i = 0; i < lk; ++i) buf[i] = k[i] ^ 0x36;
    for (i = lk; i < SHA_BLOCKSIZE; ++i) buf[i] = 0x36;

    SHA1_Update(&ictx, buf, SHA_BLOCKSIZE);
    SHA1_Update(&ictx, d, ld);
    SHA1_Final(isha, &ictx);

    /**** Outer Digest ****/

    SHA1_Init(&octx);

    /* Pad the key for outter digest */

    for (i = 0; i < lk; ++i) buf[i] = k[i] ^ 0x5c;
    for (i = lk; i < SHA_BLOCKSIZE; ++i) buf[i] = 0x5c;

    SHA1_Update(&octx, buf, SHA_BLOCKSIZE);
    SHA1_Update(&octx, isha, SHA_DIGEST_LENGTH);
    SHA1_Final(osha, &octx);

    /* truncate and print the results */
    memcpy(out, osha, SHA_DIGEST_LENGTH);
}
