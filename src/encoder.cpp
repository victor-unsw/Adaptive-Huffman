//
// Created by Demon on 23/03/16.
//

#include <iostream>
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
std::vector<char>* Encoder::encodeBuffer(const std::string& s) {
    std::vector<char>* codes = new std::vector<char>;

    int  l      = 7;
    char BYTE   = 0;

    // iterate through each character in string s
    for (auto it=s.begin();it!=s.end();it++,--l){
        if (l < 0){
            l = 7;
            codes->push_back(BYTE);                         // push current BYTE
            BYTE = 0;                                       // introduce new BYTE
        }
        if (*it == '1')
            BYTE |= 1 << l;
    }

    // invariant :-
    // = 1 BYTE remaining to be pushed
    // = l points to exact location next code would enter
    // = if l < 0 then perfect fit i.e. all code perfectly BYTEfied
    //


    int r = (l+1);                                          // remaining bits in the byte
    if (r > 0){
        // do padding
        std::cout << "padding bits\n";
        std::string NYTCode = getNYTCode();
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
        std::cout << "perfect fit" << std::endl;
        codes->push_back(BYTE);
    }

    return codes;
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
    std::cout << "padding string  : " << getNYTCode() << std::endl;
    std::string value = "0110000111111111111111111111111111111111";
    std::cout << "Encoding string : " << value << " [" << value.size() << "]\n";

    std::vector<char>* codes = encodeBuffer(value);
    std::cout << "Encoded version : ";
    for (auto i = codes->begin(); i != codes->end() ; ++i) {
        showBinary(*i,false);
    }
    std::cout << "[" << codes->size() << "]" << std::endl;
}

/*
 * getNYTCode()
 * - returns code for NYT node + '1' mark
 *   to represent [1000000] sign bit
 */
std::string Encoder::getNYTCode(){
    return "0011101";               // 001110 + 1
}