//
// Created by Demon on 23/03/16.
//

#ifndef ADAPTIVE_HUFFMAN_DECODER_H
#define ADAPTIVE_HUFFMAN_DECODER_H

#include<string>
#include<vector>
#include<algorithm>

#include "model.h"

class Decoder{

private:

    HuffmanTree *model;
    char out = 0;
    int r = -1;
    bool exitCode = false;
    HuffmanTree::node* n = NULL;
    // ------------------------------------------------------------
    // Core Methods
    // ------------------------------------------------------------

    /*
     * travel(n,dir).
     * - if dir = 1, then return n->right
     * - if dir = 0, then return n->left
     * - if no child, return null
     */
    HuffmanTree::node* travel(HuffmanTree::node* n,int dir);


    // ------------------------------------------------------------
    // Utility Methods
    // ------------------------------------------------------------

public:

    Decoder():model(NULL){
        model = new HuffmanTree;
        n = model->ROOT;
    }

    std::string* decodeBuffer(const std::string& code);

    void display(){
        std::string x = "";
        x.push_back(0x54);
        x.push_back(0x34);
        x.push_back(0x4D);
        x.push_back(0x23);
        x.push_back(0x92);

        x.push_back(0x20);
        x.push_back(0xF8);
        x.push_back(0xF3);
        x.push_back(0x0E);
        x.push_back(0x40);

        std::string input = "e eae de eabe eae dcf";
        std::string* result = decodeBuffer(x);
        std::cout << "result : " << *result << std::endl;
        if (input == *result){
            std::cout << "result equal !!!\n";
        } else
            std::cout << "not equal ! fuck \n";
    }

};

#endif //ADAPTIVE_HUFFMAN_DECODER_H
