#ifndef ONEPIECE_BASE_HASH_SIPHASH_H_
#define ONEPIECE_BASE_HASH_SIPHASH_H_

/**
 * siphash is from redis
 */ 

#include <stdlib.h>
#include <stdint.h>
/**
 * @param k hash seed , uint8_t[16], it can be got from util.h/getRandomHexChars 
 */ 
uint64_t siphash(const uint8_t *in, const size_t inlen, const uint8_t *k);
uint64_t siphash_nocase(const uint8_t *in, const size_t inlen, const uint8_t *k);

#endif  // ONEPIECE_BASE_HASH_SIPHASH_H_