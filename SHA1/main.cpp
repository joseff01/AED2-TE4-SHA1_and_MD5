  
#include <iostream>
#include "SHA1_Algorithm.h"

int main() 
{
    char phrase[] = "quick brown foxes jump over the lazy dog";
    const unsigned char *rePhrase = reinterpret_cast<const unsigned char *>(phrase);
    //std::cout << strlen(phrase) << std::endl;
    //std::cout << phrase << std::endl;
    SHA1(rePhrase,strlen(phrase));
}
//MD5/main.cpp