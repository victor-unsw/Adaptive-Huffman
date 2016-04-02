#include <iostream>

using namespace std;

#include "ahencode.h"
#include "ahdecode.h"

/*
int main(){

    ahencode e;
    ahdecode d;

    string input("aa bbb cccc dddd aaa");
    bool flag = true;

    string encode;
    string decode;

    encode = e.encodeBuffer(input, flag);
    cout << "Coding ["<<encode<<"]"<<endl;
    decode = d.decodeBuffer(encode, flag);
    cout << "Decode ["<<decode<<"]"<<endl;
    if (!strcmp(input.c_str(),decode.c_str()))
        cout << "MATCH !" << endl;
    else
        cout << "PROBLEM :(" << endl;
}

*/