#ifndef SHA1_H
#define SHA1_H

#include "../LinkedList/List.h"
#include <iostream>
#include <cstring>
#include <cstdint>

class SHA1
{
    public:
    SHA1(const unsigned char rePhrase[], size_t phraseLength);

    private:
    size_t length;
    void divide(const unsigned char *rePhrase);
    void pad();

};

#endif