#ifndef SHA1_H
#define SHA1_H

#include "../LinkedList/List.h"
#include <iostream>
#include <cstring>
#include <cstdint>
#include "bitset"

class SHA1
{
    public:
    SHA1(const unsigned char rePhrase[], size_t phraseLength);

    private:
    size_t length;
    void process(const unsigned char *rePhrase);
    std::string divideToBinary(const unsigned char *rePhrase);
    std::string pad(std::string list);
    void divideInChunks(std::string list);
    List<std::string> chunks512;

};

#endif