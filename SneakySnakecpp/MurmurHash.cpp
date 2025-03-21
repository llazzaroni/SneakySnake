#include <iostream>
#include <string>
#include <cstring>


//uint32_t: unsigned which guarantees 32 bits
//uint8_t: unsigned int which guarantees 8 bits
//size::t stores the maximum size of a type
/*memcpy: copies the values of *third argument* values from the *second argument*
pointer to the *first argument* pointer*/
//>>: shifting of *right operand* bits
//| binary or
//^ binary XOR



//murmur_32_scramble scrambles the values of an array of 32 bytes
static inline uint32_t murmur_32_scramble(uint32_t k) {
    k *= 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;
    return k;
}


//takes a pointer to an array of 8 bytes (the key), a certain number (which will
//influence the computations) and returns an array of 32 bytes.
uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed)
{
    uint32_t h = seed; //h will be the output, and it is in the beginning equal to the input
    uint32_t k; //k is empty
    

    for (size_t i = len >> 2; i; i--) { //here the second key is used
    
        memcpy(&k, key, sizeof(uint32_t)); //the values of the key are copied into
                                           //the empty array k
        
        key += sizeof(uint32_t); //key is somehow changed
        
        h ^= murmur_32_scramble(k); //k, which always contains the values of key,
                                    //gets scrambled; an XOR operation with h is
                                    //conducted and h gets zugewiesen to it
        h = (h << 13) | (h >> 19); //h gets somehow again scrambled
        h = h * 5 + 0xe6546b64;
    }
    
    
    //in this for loop k gets somehow changed, and it depends on the second key
    //and on the first key; then an XOR operation is conducted with h
    k = 0;
    for (size_t i = len & 3; i; i--) {
        k <<= 8;
        k |= key[i - 1];
    }
    h ^= murmur_32_scramble(k);
    
    
    
    //h gets again scrambled
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}
