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
    std::vector<char>* encodeBuffer(const std::string& s);

    std::string generateCode(char c);

    // ------------------------------------------------------------
    // Utility Methods
    // ------------------------------------------------------------

    void encodeShow();

    void showBinary(char c, bool show);

public:

    Encoder():model(){}

    void display(){

        encodeShow();

    }

};

#endif //ADAPTIVE_HUFFMAN_ENCODER_H
