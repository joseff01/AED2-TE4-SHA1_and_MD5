#include "SHA1_Algorithm.h"


SHA1::SHA1(const unsigned char *rePhrase, size_t phraseLength)
{
    this->length = phraseLength;
    process(rePhrase);

}
void SHA1::process(const unsigned char *rePhrase)
{
    std::string message = divideToBinary(rePhrase);
    message = pad(message);
    divideInChunks(message);

}

std::string SHA1::divideToBinary(const unsigned char *rePhrase)
{
    std::string binList;

    for (size_t i = 0; i < this->length; i++)
    {
        std::string bin = std::bitset<8>(rePhrase[i]).to_string();
        binList += bin;
    }
    binList = binList+"1";
    return binList;
}

std::string SHA1::pad(std::string list)
{
    while(list.length()%512 != 448) { list += '0'; }
    std::cout <<list.length() << std::endl;
    list += std::bitset<64>(this->length).to_string();
    std::cout <<list << std::endl;
    return list;
}

void SHA1::divideInChunks(std::string list)
{
    std::string currentStr = "";
    List<std::string> newList;
    int num = 0;
    int intgr =0;
    int i = 0;
    while( i <16)
    {
        currentStr += list[intgr];
        intgr++;
        num++;
        if(num ==32)
        {
            std::cout << currentStr << std::endl;
            newList.push_back(currentStr);
            currentStr ="";
            num = 0;
            i++;
        }
    }
    chunks512.push_back(newList);

}
