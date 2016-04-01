//
// Created by Demon on 01/04/16.
//

#include "ahencode.h"

std::string ahencode::encodeBuffer(std::string s, bool flag) {
    model = new HuffmanTree;
    std::string result;

    for (auto c = s.begin();c != s.end(); c++) {
        std::string* path = new std::string;
        bool isNYT = model->path(*c,path);
        if (isNYT)
            path->append(generateCode(*c));
        result.append(*path);
        if (flag)
            result.append(" ");
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
