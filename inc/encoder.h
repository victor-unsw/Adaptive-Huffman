//
// Created by Demon on 23/03/16.
//

#ifndef ADAPTIVE_HUFFMAN_ENCODER_H
#define ADAPTIVE_HUFFMAN_ENCODER_H

#include <vector>
#include <string>
#include <algorithm>

#include "model.h"

class Encoder{

private:

    HuffmanTree model;

    // ------------------------------------------------------------
    // Core Methods
    // ------------------------------------------------------------


    std::string generateCode(char c);

    // ------------------------------------------------------------
    // Utility Methods
    // ------------------------------------------------------------

    void encodeShow();

public:

    Encoder():model(){}

    void showBinary(char c, bool show);

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
    std::vector<char>* encodeBuffer(std::string& s);

    void display(){

        encodeShow();

    }

};

#endif //ADAPTIVE_HUFFMAN_ENCODER_H
