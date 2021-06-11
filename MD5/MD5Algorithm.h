#ifndef MD5_MD5ALGORITHM_H
#define MD5_MD5ALGORITHM_H

#include "../LinkedList/List.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdint>

using namespace std;

class MD5Algorithm {

private:
    long long const bit32 = 4294967296;
    long long const bit9 = 512;
    List<int32_t> T;
    int32_t A;
    int32_t B;
    int32_t C;
    int32_t D;
    List<int> messageToBinary(List<char> listMessage);
    List<int> decimalToBinary(int num);
    List<int> decimalTo32BitBinary(uint32_t num);
    int32_t binaryToInt32(List<int> listBinary);
    List<int> bitAddition(List<int> binaryList);
    List<int> sizeBitsAddition(List<int> binaryList, List<int> binarySize);
    void initializeBuffers();
    string transformationProcess(List<int> listMessage);
    int32_t F(int32_t a, int32_t b, int32_t c);
    int32_t FF(int32_t a, int32_t b, int32_t c, int32_t d, int32_t segmentPart, int bitRotation, int TConstant);
    int32_t G(int32_t a, int32_t b, int32_t c);
    int32_t GG(int32_t a, int32_t b, int32_t c, int32_t d, int32_t segmentPart, int bitRotation, int TConstant);
    int32_t H(int32_t a, int32_t b, int32_t c);
    int32_t HH(int32_t a, int32_t b, int32_t c, int32_t d, int32_t segmentPart, int bitRotation, int TConstant);
    int32_t I(int32_t a, int32_t b, int32_t c);
    int32_t II(int32_t a, int32_t b, int32_t c, int32_t d, int32_t segmentPart, int bitRotation, int TConstant);
    int32_t circularLeftShift(int32_t list, int shift);
    int32_t powerOf(int32_t a, int32_t b);
    string hexadecimalValueAllBuffers(List<int> a, List<int> b, List<int> c, List<int> d);
    char intToHex(int num);
public:
    string MD5Encryption(List<char> listMessage);

};


#endif //MD5_MD5ALGORITHM_H
