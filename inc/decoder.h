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

    // ------------------------------------------------------------
    // Core Methods
    // ------------------------------------------------------------

    std::string* decodeBuffer(const std::string& code);

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
    }

    void display(){
        std::string x = "";
        x.push_back(0x65);
        x.push_back(0x10);
        x.push_back(0x06);
        x.push_back(0x11);
        x.push_back(0x19);

        x.push_back(0x12);
        x.push_back(0x63);
        x.push_back(0x12);
        x.push_back(0x65);
        x.push_back(0x9C);

        x.push_back(0x63);
        x.push_back(0xF9);
        x.push_back(0x98);
        x.push_back(0x20);

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
