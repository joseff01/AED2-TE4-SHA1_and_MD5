#include <iostream>
#include "../LinkedList/List.h"
#include "MD5Algorithm.h"


using namespace std;

int main() {
    MD5Algorithm md5Algorithm = MD5Algorithm();
    List<char> list = {'h','e','l','l','o'};
    cout << list << endl;
    md5Algorithm.MD5Encryption(list);
    List<char> listError = {'h','e','l','l','0'};
    md5Algorithm.MD5Encryption(listError);
}
