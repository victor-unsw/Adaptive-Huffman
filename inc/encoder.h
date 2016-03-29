//
// Created by Demon on 23/03/16.
//

#ifndef ADAPTIVE_HUFFMAN_ENCODER_H
#define ADAPTIVE_HUFFMAN_ENCODER_H

#include <vector>
#include <string>
#include <algorithm>

class Encoder{

private:

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


    // ------------------------------------------------------------
    // Utility Methods
    // ------------------------------------------------------------

    /*
     * getNYTCode()
     * - returns code for NYT node + '1' mark
     *   to represent [1000000] sign bit
     */
    std::string getNYTCode();

    void encodeShow();

    void showBinary(char c, bool show);

public:

    void display(){

        encodeShow();

    }

};

#endif //ADAPTIVE_HUFFMAN_ENCODER_H
