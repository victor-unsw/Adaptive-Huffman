//
// Created by Demon on 01/04/16.
//

#include <iostream>
#include "ahencode.h"

std::string* ahencode::encodeBuffer(std::string s, bool flag) {
    model = new HuffmanTree;
    std::string* result = new std::string;

    for (auto c = s.begin();c != s.end(); c++) {
        std::string* path = new std::string;
        bool isNYT = model->path(*c,path);
        if (isNYT)
            path->append(generateCode(*c));
        result->append(*path);
        if (flag && ((c+1) != s.end()))
            result->append(" ");
        model->update(*c);
        delete(path);
    }
    delete model;
    return result;
}

std::string ahencode::generateCode(char c){
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


int main(int args,char** argv){

    char*           buffer  = new char[MAX_CHAR];

    bool            FLAG    = (args > 1 && !strcmp(argv[1],"-s"));
    ahencode        encoder;
    std::string*    output  = NULL;

    while (std::cin.getline(buffer,MAX_CHAR)){

        std::string input(buffer);
        output = encoder.encodeBuffer(input,FLAG);
        if (output != NULL) {
            std::cout << *output << std::endl;
            delete output;
        }
    }

    return 0;
}