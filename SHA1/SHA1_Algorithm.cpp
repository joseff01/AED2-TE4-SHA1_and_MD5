#include "SHA1_Algorithm.h"

SHA1::SHA1(const unsigned char *rePhrase, size_t phraseLength)
{
    this->length = phraseLength;
    //divide(rePhrase);

}

void SHA1::divide(const unsigned char *rePhrase)
{
    List<unsigned char> divList;
    
    for (size_t i = 0; i <this->length ; i++)
    {
        //int temp = rePhrase[i];
        divList.push_back(rePhrase[i]);
        std::cout<<rePhrase[i]<<std::endl;
    }

}
