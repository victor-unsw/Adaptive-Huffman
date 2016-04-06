//
// Created by Demon on 23/03/16.
//

#include <iostream>
#include <fstream>
#include "encoder.h"

// ------------------------------------------------------------
// Core Methods
// ------------------------------------------------------------

/*
 * encodeBuffer(s)
 * - every character in string s represent
 *   either 0 or 1.
 * - encodes each character into byte form.
 * - returns pointer to vector of bytes formed.
 *
 * Memory Allocation    : vector<char>
 * Memory Deallocation  : none
 *
 * Return : pt to vector<char>
 */
std::vector<char>* Encoder::encodeBuffer(std::string& s) {
    std::vector<char>* codes = new std::vector<char>;

    int  l      = 7;
    char BYTE   = 0;

    // iterate through each character in string s
    for (auto c =s.begin(); c !=s.end(); c++){

        std::string* path = new std::string;
        bool isNYT = model.path(*c,path);
        if (isNYT){
            path->append(generateCode(*c));
        }

        // for each binary code in path
        for(auto it=path->begin();it!=path->end();it++) {
            if (l < 0) {
                l = 7;
                codes->push_back(BYTE);                         // push current BYTE
                BYTE = 0;                                       // introduce new BYTE
            }
            if (*it == '1')
                BYTE |= 1 << l;
            --l;
        }
        model.update(*c);
        delete path;
    }

    // invariant :-
    // = 1 BYTE remaining to be pushed
    // = l points to exact location next code would enter
    // = if l < 0 then perfect fit i.e. all code perfectly BYTEfied
    //


    int r = (l+1);                                          // remaining bits in the byte
    if (r > 0){
        // do padding
        //std::cout << "padding bits\n";
        const std::string NYTCode = *model.exitCode();

        for (auto it=NYTCode.begin();it!=NYTCode.end();it++,--l){
            if (l < 0){
                l = 7;
                codes->push_back(BYTE);
                BYTE = 0;
            }
            if (*it == '1')
                BYTE |= 1 << l;
        }

        // still the last BYTE remains
        codes->push_back(BYTE);

    }else{
        // perfect fit
       // std::cout << "perfect fit" << std::endl;
        codes->push_back(BYTE);
    }

    return codes;
}

/*
 * generateCode(c)
 * - generates the binary code of Byte C
 *   in format
 */
std::string Encoder::generateCode(char c){
    std::string code;
    char x = 0;
    for (int i = 7; i >= 0; --i) {
        x |= 1 << i;
        if (c&x)
            code.push_back('1');
        else code.push_back('0');
        x = 0;
    }
    return code;
}


// ------------------------------------------------------------
// Utility Methods
// ------------------------------------------------------------

void Encoder::showBinary(char c, bool show) {
    if (show)
        std::cout<< c << "("<< int(c) <<")"<<" -> ";
    char x = 0;
    for (int i = 7; i >=0; --i) {
        x |= 1 << i;
        if (c&x)
            std::cout << 1;
        else
            std::cout << 0;
        x = 0;
    }
    if (show)
        std::cout << std::endl;
    else
        std::cout << " ";
}

void Encoder::encodeShow() {

    std::string value = "This is a";
    std::cout << "Encoding string : " << value << " [" << value.size() << "]\n";

    std::vector<char>* codes = encodeBuffer(value);
    std::cout << "Encoded version : ";
    for (auto i = codes->begin(); i != codes->end() ; ++i) {
        showBinary(*i,false);
    }
    std::cout << "[" << codes->size() << "]" << std::endl;

    model.display();


}



int main(int args,char** argv){

    std::string     output = "/Users/victorchoudhary/Documents/encoded_file.txt";;
    std::string     input = "/Users/victorchoudhary/Documents/input_file.txt";

    std::ofstream fout(output);
    std::ifstream fin(input);

    Encoder encoder;


    const int MAX = 50000;

    char* buffer = new char[MAX];
    std::vector<char>* codes = nullptr;

    while(!fin.eof()){
        memset(buffer,0,MAX);
        fin.read(buffer,MAX);
        std::string temp(buffer);
        //std::cout << "encoding : " << temp << "\n----- again ----\n" << std::endl;
        codes = encoder.encodeBuffer(temp);
        //std::cout << "Encoded version : ";
        std::string s(codes->begin(),codes->end());
        fout.write(s.c_str(),s.size());
        //std::cout << "writing : " << s << std::endl;
        //std::cout << "[" << codes->size() << "]" << std::endl;
    }

    delete [] buffer;


    return 0;
}