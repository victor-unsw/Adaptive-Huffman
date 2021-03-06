//
// Created by Demon on 01/04/16.
//

#ifndef ADAPTIVE_HUFFMAN_AHDECODE_H
#define ADAPTIVE_HUFFMAN_AHDECODE_H

#include<string>
#include<iostream>
#include<algorithm>

#include "model.h"

#define MAX_CHAR 8001

class ahdecode{

private:

    HuffmanTree* model;

    // ------------------------------------------------------------
    // Core Methods
    // ------------------------------------------------------------

    HuffmanTree::node* travel(HuffmanTree::node* n,int dir);

public:

    ahdecode():model(NULL){ }
    std::string* decodeBuffer(std::string code,bool flag);

};


#endif //ADAPTIVE_HUFFMAN_AHDECODE_H
