#include "MD5Algorithm.h"

string MD5Algorithm::MD5Encryption(List<char> listMessage) {
    List<int> binaryMessage = messageToBinary(listMessage);
    int messageSize = binaryMessage.length();
    cout << "Message to Binary: " << endl << binaryMessage << endl;
    binaryMessage = bitAddition(binaryMessage);
    cout << "Message with added zeroes: " << endl << binaryMessage << endl;
    binaryMessage = sizeBitsAddition(binaryMessage, decimalToBinary(messageSize));
    cout << "Message with added 64 bit size: " << endl << binaryMessage << endl;
    initializeBuffers();
    string finalEncryptionMessage = transformationProcess(binaryMessage);
    return finalEncryptionMessage;
}

List<int> MD5Algorithm::messageToBinary(List<char> listMessage) {
    List<int> binaryMessage;
    for (int i = 0; i < listMessage.length(); ++i) {
        int asciiCharNum = listMessage[i];
        List<int> binaryChar = decimalToBinary(asciiCharNum);
        for (int j = 0; j < binaryChar.length(); ++j) {
            binaryMessage.push_back(binaryChar[j]);
        }
    }
    return binaryMessage;
}


List<int> MD5Algorithm::bitAddition(List<int> binaryList) {
    int binaryListSize = binaryList.length();
    int additionAmount;
    for (int i = 1; true ; ++i) {
        additionAmount = 448*i - binaryListSize;
        if (additionAmount < 0){
            continue;
        } else{
            break;
        }
    }
    binaryList.push_back(1);
    for (int i = 0; i < additionAmount-1; ++i) {
        binaryList.push_back(0);
    }
    return binaryList;
}

List<int> MD5Algorithm::sizeBitsAddition(List<int> binaryList, List<int> binarySize) {
    for (int i = 0; i < 64; ++i) {
        binaryList.push_back(0);
    }
    for (int i = 1; i < 9; ++i) {
        binaryList[binaryList.length()-i] = binarySize[8-i];
    }
    return binaryList;
}

List<int> MD5Algorithm::decimalToBinary(int num) {
    List<int> binaryList;
    for (int i = 0; i < 8; ++i) {
        binaryList.push_back(0);
    }
    for (int i = 0; i < 8; ++i) {
        if (num == 0){
            break;
        }
        binaryList[7-i] = num % 2;
        num /= 2;
    }
    return binaryList;
}

int32_t MD5Algorithm::binaryToInt32(List<int> listBinary) {
    int32_t intResult = 0;
    for (int i = 0; i < 32; ++i) {
        if (listBinary[31-i] == 1){
            intResult += powerOf(2,i);
        }
    }
    return intResult;
}



void MD5Algorithm::initializeBuffers() {
    A = 1732584193;
    B = -271733879;
    C = -1732584194;
    D = 271733878;
    for (int i = 0; i < 64; ++i) {
        int32_t int32bit = (long long)(bit32 * (double) abs((double)sin(i+1)));
        T.push_back(int32bit);
    }
}

int32_t MD5Algorithm::powerOf(int32_t a, int32_t b){
    int32_t k = 1;
    for (int i = 0; i < b; ++i) {
        k *= a;
    }
    return k;
}

int32_t MD5Algorithm::F(int32_t a, int32_t b, int32_t c) {
    return (int32_t)(((uint32_t)a & (uint32_t)b) | ((~(uint32_t)a) & (uint32_t)c));
}

int32_t MD5Algorithm::FF(int32_t a, int32_t b, int32_t c, int32_t d, int32_t segmentPart, int bitRotation, int TConstant) {
    a = b + circularLeftShift(a + F(b,c,d) + segmentPart + T[TConstant],bitRotation);
    return a;
}

int32_t MD5Algorithm::G(int32_t a, int32_t b, int32_t c) {
    return (int32_t)(((uint32_t)a & (uint32_t)c) | ((uint32_t)b & (~(uint32_t)c)));
}

int32_t MD5Algorithm::GG(int32_t a, int32_t b, int32_t c, int32_t d, int32_t segmentPart, int bitRotation, int TConstant) {
    a = b + circularLeftShift(a + G(b,c,d) + segmentPart + T[TConstant], bitRotation);
    return a;
}

int32_t MD5Algorithm::H(int32_t a, int32_t b, int32_t c) {
    return (int32_t)((uint32_t)a ^ (uint32_t)b ^ (uint32_t)c);
}

int32_t MD5Algorithm::HH(int32_t a, int32_t b, int32_t c, int32_t d, int32_t segmentPart, int bitRotation, int TConstant) {
    a = b + circularLeftShift(a + H(b,c,d) + segmentPart + T[TConstant], bitRotation);
    return a;
}

int32_t MD5Algorithm::I(int32_t a, int32_t b, int32_t c) {
    return (int32_t)((uint32_t)b ^ ((uint32_t)a | ~(uint32_t)c));
}

int32_t MD5Algorithm::II(int32_t a, int32_t b, int32_t c, int32_t d, int32_t segmentPart, int bitRotation, int TConstant) {
    a = b + circularLeftShift(a + I(b,c,d) + segmentPart + T[TConstant], bitRotation);
    return a;
}

int32_t MD5Algorithm::circularLeftShift(int32_t x, int shift) {
    return (x << shift) | (x >> (0x1F & (32 + ~shift + 1))) & ~(-1 << shift);
}

string MD5Algorithm::transformationProcess(List<int> listMessage) {
    int numberOfTransformations = 0;
    long long messageSize = listMessage.length();
    while (true) {
        if (messageSize < bit9){
            break;
        } else{
            numberOfTransformations++;
            messageSize -= bit9;
            continue;
        }
    }
    //Division into multiple 512 chunks
    List<List<int>> listMessageChunks;
    for (int i = 0; i < numberOfTransformations; i++) {
        List<int> listChunk;
        for (int j = 0; j < bit9; ++j) {
            listChunk.push_back(listMessage[(i+1)*j]);
        }
        listMessageChunks.push_back(listChunk);
    }
    //Main transformation Loop
    for (int i = 0; i < numberOfTransformations; ++i) {
        //Chose a chunk
        List<int> mainChunk = listMessageChunks[i];
        //Creating 16 32 bit segments from the chosen 512 bit chunk to apply the
        List<List<int>> chunkSegmentsList;
        for (int j = 0; j < 14; ++j) {
            List<int> listSegment;
            for (int k = 3; k >= 0; --k) {
                for (int l = 0; l < 8; ++l) {
                    listSegment.push_back(mainChunk[(j*32)+(k*8)+l]);
                }
            }
            chunkSegmentsList.push_back(listSegment);
        }
        for (int j = 15; j >= 14; --j) {
            List<int> listSegment;
            for (int k = 0; k < 32; ++k) {
                listSegment.push_back(mainChunk[(j*32)+k]);
            }
            chunkSegmentsList.push_back(listSegment);
        }

        //Saving initial states of Buffers
        int32_t initialA = A;
        int32_t initialB = B;
        int32_t initialC = C;
        int32_t initialD = D;
        //Start of Rounds
        //FF Round:

        A = FF(A,B,C,D,binaryToInt32(chunkSegmentsList[0]),7,0);   // 0
        D = FF(D,A,B,C,binaryToInt32(chunkSegmentsList[1]),12,1);
        C = FF(C,D,A,B,binaryToInt32(chunkSegmentsList[2]),17,2);
        B = FF(B,C,D,A,binaryToInt32(chunkSegmentsList[3]),22,3);
        A = FF(A,B,C,D,binaryToInt32(chunkSegmentsList[4]),7,4);
        D = FF(D,A,B,C,binaryToInt32(chunkSegmentsList[5]),12,5);
        C = FF(C,D,A,B,binaryToInt32(chunkSegmentsList[6]),17,6);
        B = FF(B,C,D,A,binaryToInt32(chunkSegmentsList[7]),22,7);
        A = FF(A,B,C,D,binaryToInt32(chunkSegmentsList[8]),7,8);
        D = FF(D,A,B,C,binaryToInt32(chunkSegmentsList[9]),12,9);
        C = FF(C,D,A,B,binaryToInt32(chunkSegmentsList[10]),17,10);
        B = FF(B,C,D,A,binaryToInt32(chunkSegmentsList[11]),22,11);
        A = FF(A,B,C,D,binaryToInt32(chunkSegmentsList[12]),7,12);
        D = FF(D,A,B,C,binaryToInt32(chunkSegmentsList[13]),12,13);
        C = FF(C,D,A,B,binaryToInt32(chunkSegmentsList[14]),17,14);
        B = FF(B,C,D,A,binaryToInt32(chunkSegmentsList[15]),22,15);// 15

        //GG Round:
        A = GG(A,B,C,D,binaryToInt32(chunkSegmentsList[1]),5,16);  // 16
        D = GG(D,A,B,C,binaryToInt32(chunkSegmentsList[6]),9,17);
        C = GG(C,D,A,B,binaryToInt32(chunkSegmentsList[11]),14,18);
        B = GG(B,C,D,A,binaryToInt32(chunkSegmentsList[0]),20,19);
        A = GG(A,B,C,D,binaryToInt32(chunkSegmentsList[5]),5,20);
        D = GG(D,A,B,C,binaryToInt32(chunkSegmentsList[10]),9,21);
        C = GG(C,D,A,B,binaryToInt32(chunkSegmentsList[15]),14,22);
        B = GG(B,C,D,A,binaryToInt32(chunkSegmentsList[4]),20,23);
        A = GG(A,B,C,D,binaryToInt32(chunkSegmentsList[9]),5,24);
        D = GG(D,A,B,C,binaryToInt32(chunkSegmentsList[14]),9,25);
        C = GG(C,D,A,B,binaryToInt32(chunkSegmentsList[3]),14,26);
        B = GG(B,C,D,A,binaryToInt32(chunkSegmentsList[8]),20,27);
        A = GG(A,B,C,D,binaryToInt32(chunkSegmentsList[13]),5,28);
        D = GG(D,A,B,C,binaryToInt32(chunkSegmentsList[2]),9,29);
        C = GG(C,D,A,B,binaryToInt32(chunkSegmentsList[7]),14,30);
        B = GG(B,C,D,A,binaryToInt32(chunkSegmentsList[12]),20,31);// 31

        //HH Round:
        A = HH(A,B,C,D,binaryToInt32(chunkSegmentsList[5]),4,32);  // 32
        D = HH(D,A,B,C,binaryToInt32(chunkSegmentsList[8]),11,33);
        C = HH(C,D,A,B,binaryToInt32(chunkSegmentsList[11]),16,34);
        B = HH(B,C,D,A,binaryToInt32(chunkSegmentsList[14]),23,35);
        A = HH(A,B,C,D,binaryToInt32(chunkSegmentsList[1]),4,36);
        D = HH(D,A,B,C,binaryToInt32(chunkSegmentsList[4]),11,37);
        C = HH(C,D,A,B,binaryToInt32(chunkSegmentsList[7]),16,38);
        B = HH(B,C,D,A,binaryToInt32(chunkSegmentsList[10]),23,39);
        A = HH(A,B,C,D,binaryToInt32(chunkSegmentsList[13]),4,40);
        D = HH(D,A,B,C,binaryToInt32(chunkSegmentsList[0]),11,41);
        C = HH(C,D,A,B,binaryToInt32(chunkSegmentsList[3]),16,42);
        B = HH(B,C,D,A,binaryToInt32(chunkSegmentsList[6]),23,43);
        A = HH(A,B,C,D,binaryToInt32(chunkSegmentsList[9]),4,44);
        D = HH(D,A,B,C,binaryToInt32(chunkSegmentsList[12]),11,45);
        C = HH(C,D,A,B,binaryToInt32(chunkSegmentsList[15]),16,46);
        B = HH(B,C,D,A,binaryToInt32(chunkSegmentsList[2]),23,47); // 47

        //II Round:
        A = II(A,B,C,D,binaryToInt32(chunkSegmentsList[0]),6,48);  // 32
        D = II(D,A,B,C,binaryToInt32(chunkSegmentsList[7]),10,49);
        C = II(C,D,A,B,binaryToInt32(chunkSegmentsList[14]),15,50);
        B = II(B,C,D,A,binaryToInt32(chunkSegmentsList[5]),21,51);
        A = II(A,B,C,D,binaryToInt32(chunkSegmentsList[12]),6,52);
        D = II(D,A,B,C,binaryToInt32(chunkSegmentsList[3]),10,53);
        C = II(C,D,A,B,binaryToInt32(chunkSegmentsList[10]),15,54);
        B = II(B,C,D,A,binaryToInt32(chunkSegmentsList[1]),21,55);
        A = II(A,B,C,D,binaryToInt32(chunkSegmentsList[8]),6,56);
        D = II(D,A,B,C,binaryToInt32(chunkSegmentsList[15]),10,57);
        C = II(C,D,A,B,binaryToInt32(chunkSegmentsList[6]),15,58);
        B = II(B,C,D,A,binaryToInt32(chunkSegmentsList[13]),21,59);
        A = II(A,B,C,D,binaryToInt32(chunkSegmentsList[4]),6,60);
        D = II(D,A,B,C,binaryToInt32(chunkSegmentsList[11]),10,61);
        C = II(C,D,A,B,binaryToInt32(chunkSegmentsList[2]),15,62);
        B = II(B,C,D,A,binaryToInt32(chunkSegmentsList[9]),21,63); // 47

        A = initialA + A;
        B = initialB + B;
        C = initialC + C;
        D = initialD + D;
    }
    uint32_t AA = A;
    uint32_t BB = B;
    uint32_t CC = C;
    uint32_t DD = D;

    //Conversion from int to binary
    List<int> AAA = decimalTo32BitBinary(AA);
    List<int> BBB = decimalTo32BitBinary(BB);
    List<int> CCC = decimalTo32BitBinary(CC);
    List<int> DDD = decimalTo32BitBinary(DD);

    string finalMessage = hexadecimalValueAllBuffers(AAA,BBB,CCC,DDD);

    cout<< finalMessage << endl;

    return finalMessage;
}

List<int> MD5Algorithm::decimalTo32BitBinary(uint32_t num) {
    List<int> binaryList;
    for (int i = 0; i < 32; ++i) {
        binaryList.push_back(0);
    }
    for (int i = 0; i < 32; ++i) {
        if (num == 0){
            break;
        }
        binaryList[31-i] = num % 2;
        num /= 2;
    }
    return binaryList;
}

string MD5Algorithm::hexadecimalValueAllBuffers(List<int> a, List<int> b, List<int> c, List<int> d) {
    string hexMessage;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            string char2;
            for (int k = 1; k >= 0; --k) {
                char char1;
                int decimal = 0;
                for (int l = 3; l >= 0; --l) {
                    if (i == 0){
                        if (a[31-((j*8)+(k*4)+l)] == 1){
                            decimal += pow(2,l);
                        }
                    } else if (i == 1){
                        if (b[31-((j*8)+(k*4)+l)] == 1){
                            decimal += pow(2,l);
                        }
                    } else if (i == 2){
                        if (c[31-((j*8)+(k*4)+l)] == 1){
                            decimal += pow(2,l);
                        }
                    } else {
                        if (d[31-((j*8)+(k*4)+l)] == 1){
                            decimal += pow(2,l);
                        }
                    }
                }
                char1 = intToHex(decimal);
                char2.push_back(char1);
            }
            hexMessage.append(char2);
        }
    }
    return hexMessage;
}

char MD5Algorithm::intToHex(int num) {
    if (num == 0){
        return '0';
    } else if(num == 1) {
        return '1';
    } else if(num == 2) {
        return '2';
    } else if(num == 3) {
        return '3';
    } else if(num == 4) {
        return '4';
    } else if(num == 5) {
        return '5';
    } else if(num == 6) {
        return '6';
    } else if(num == 7) {
        return '7';
    } else if(num == 8) {
        return '8';
    } else if(num == 9) {
        return '9';
    } else if(num == 10) {
        return 'a';
    } else if(num == 11) {
        return 'b';
    } else if(num == 12) {
        return 'c';
    } else if(num == 13) {
        return 'd';
    } else if(num == 14) {
        return 'e';
    } else{
        return 'f';
    }
}








