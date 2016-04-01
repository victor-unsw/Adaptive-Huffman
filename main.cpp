#include <iostream>

using namespace std;


#include "ahencode.h"
#include "ahdecode.h"


int main(int argc,const char** argv) {


    ahencode e;
    ahdecode d;

    char * input = new char[1001];
    string encode;

    while (cin.getline(input,1001)){
        string s(input);
        //encode = e.encodeBuffer(s, true);
        encode = d.decodeBuffer(s,false);
        cout << encode << endl;
    }

    return 0;
}