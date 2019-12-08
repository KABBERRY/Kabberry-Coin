<<<<<<< Updated upstream
// Copyright (c) 2014-2018 The Bitcoin Core developers
=======
// Copyright (c) 2014 The Bitcoin developers
>>>>>>> Stashed changes
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CRYPTO_COMMON_H
#define BITCOIN_CRYPTO_COMMON_H

<<<<<<< Updated upstream
#if defined(HAVE_CONFIG_H)
#include <config/pivx-config.h>
#endif

#include <stdint.h>
#include <string.h>

#include <compat/endian.h>

uint16_t static inline ReadLE16(const unsigned char* ptr)
{
    uint16_t x;
    memcpy((char*)&x, ptr, 2);
    return le16toh(x);
}

uint32_t static inline ReadLE32(const unsigned char* ptr)
{
    uint32_t x;
    memcpy((char*)&x, ptr, 4);
    return le32toh(x);
=======
#include <stdint.h>

#if defined(HAVE_ENDIAN_H)
#include <endian.h>
#endif

uint32_t static inline ReadLE32(const unsigned char* ptr)
{
#if HAVE_DECL_LE32TOH == 1
    return le32toh(*((uint32_t*)ptr));
#elif !defined(WORDS_BIGENDIAN)
    return *((uint32_t*)ptr);
#else
    return ((uint32_t)ptr[3] << 24 | (uint32_t)ptr[2] << 16 | (uint32_t)ptr[1] << 8 | (uint32_t)ptr[0]);
#endif
>>>>>>> Stashed changes
}

uint64_t static inline ReadLE64(const unsigned char* ptr)
{
<<<<<<< Updated upstream
    uint64_t x;
    memcpy((char*)&x, ptr, 8);
    return le64toh(x);
}

void static inline WriteLE16(unsigned char* ptr, uint16_t x)
{
    uint16_t v = htole16(x);
    memcpy(ptr, (char*)&v, 2);
=======
#if HAVE_DECL_LE64TOH == 1
    return le64toh(*((uint64_t*)ptr));
#elif !defined(WORDS_BIGENDIAN)
    return *((uint64_t*)ptr);
#else
    return ((uint64_t)ptr[7] << 56 | (uint64_t)ptr[6] << 48 | (uint64_t)ptr[5] << 40 | (uint64_t)ptr[4] << 32 |
            (uint64_t)ptr[3] << 24 | (uint64_t)ptr[2] << 16 | (uint64_t)ptr[1] << 8 | (uint64_t)ptr[0]);
#endif
>>>>>>> Stashed changes
}

void static inline WriteLE32(unsigned char* ptr, uint32_t x)
{
<<<<<<< Updated upstream
    uint32_t v = htole32(x);
    memcpy(ptr, (char*)&v, 4);
=======
#if HAVE_DECL_HTOLE32 == 1
    *((uint32_t*)ptr) = htole32(x);
#elif !defined(WORDS_BIGENDIAN)
    *((uint32_t*)ptr) = x;
#else
    ptr[3] = x >> 24;
    ptr[2] = x >> 16;
    ptr[1] = x >> 8;
    ptr[0] = x;
#endif
>>>>>>> Stashed changes
}

void static inline WriteLE64(unsigned char* ptr, uint64_t x)
{
<<<<<<< Updated upstream
    uint64_t v = htole64(x);
    memcpy(ptr, (char*)&v, 8);
=======
#if HAVE_DECL_HTOLE64 == 1
    *((uint64_t*)ptr) = htole64(x);
#elif !defined(WORDS_BIGENDIAN)
    *((uint64_t*)ptr) = x;
#else
    ptr[7] = x >> 56;
    ptr[6] = x >> 48;
    ptr[5] = x >> 40;
    ptr[4] = x >> 32;
    ptr[3] = x >> 24;
    ptr[2] = x >> 16;
    ptr[1] = x >> 8;
    ptr[0] = x;
#endif
>>>>>>> Stashed changes
}

uint32_t static inline ReadBE32(const unsigned char* ptr)
{
<<<<<<< Updated upstream
    uint32_t x;
    memcpy((char*)&x, ptr, 4);
    return be32toh(x);
=======
#if HAVE_DECL_BE32TOH == 1
    return be32toh(*((uint32_t*)ptr));
#else
    return ((uint32_t)ptr[0] << 24 | (uint32_t)ptr[1] << 16 | (uint32_t)ptr[2] << 8 | (uint32_t)ptr[3]);
#endif
>>>>>>> Stashed changes
}

uint64_t static inline ReadBE64(const unsigned char* ptr)
{
<<<<<<< Updated upstream
    uint64_t x;
    memcpy((char*)&x, ptr, 8);
    return be64toh(x);
=======
#if HAVE_DECL_BE64TOH == 1
    return be64toh(*((uint64_t*)ptr));
#else
    return ((uint64_t)ptr[0] << 56 | (uint64_t)ptr[1] << 48 | (uint64_t)ptr[2] << 40 | (uint64_t)ptr[3] << 32 |
            (uint64_t)ptr[4] << 24 | (uint64_t)ptr[5] << 16 | (uint64_t)ptr[6] << 8 | (uint64_t)ptr[7]);
#endif
>>>>>>> Stashed changes
}

void static inline WriteBE32(unsigned char* ptr, uint32_t x)
{
<<<<<<< Updated upstream
    uint32_t v = htobe32(x);
    memcpy(ptr, (char*)&v, 4);
=======
#if HAVE_DECL_HTOBE32 == 1
    *((uint32_t*)ptr) = htobe32(x);
#else
    ptr[0] = x >> 24;
    ptr[1] = x >> 16;
    ptr[2] = x >> 8;
    ptr[3] = x;
#endif
>>>>>>> Stashed changes
}

void static inline WriteBE64(unsigned char* ptr, uint64_t x)
{
<<<<<<< Updated upstream
    uint64_t v = htobe64(x);
    memcpy(ptr, (char*)&v, 8);
}

/** Return the smallest number n such that (x >> n) == 0 (or 64 if the highest bit in x is set. */
uint64_t static inline CountBits(uint64_t x)
{
#if HAVE_DECL___BUILTIN_CLZL
    if (sizeof(unsigned long) >= sizeof(uint64_t)) {
        return x ? 8 * sizeof(unsigned long) - __builtin_clzl(x) : 0;
    }
#endif
#if HAVE_DECL___BUILTIN_CLZLL
    if (sizeof(unsigned long long) >= sizeof(uint64_t)) {
        return x ? 8 * sizeof(unsigned long long) - __builtin_clzll(x) : 0;
    }
#endif
    int ret = 0;
    while (x) {
        x >>= 1;
        ++ret;
    }
    return ret;
}

#endif // BITCOIN_CRYPTO_COMMON_H
=======
#if HAVE_DECL_HTOBE64 == 1
    *((uint64_t*)ptr) = htobe64(x);
#else
    ptr[0] = x >> 56;
    ptr[1] = x >> 48;
    ptr[2] = x >> 40;
    ptr[3] = x >> 32;
    ptr[4] = x >> 24;
    ptr[5] = x >> 16;
    ptr[6] = x >> 8;
    ptr[7] = x;
#endif
}

#endif // BITCOIN_CRYPTO_COMMON_H
>>>>>>> Stashed changes
