//
// Created by Demon on 01/04/16.
//

#ifndef ADAPTIVE_HUFFMAN_AHENCODE_H
#define ADAPTIVE_HUFFMAN_AHENCODE_H

#include "string"
#include "model.h"

#define MAX_CHAR 1001

class ahencode{

private:

    HuffmanTree*  model;

    // ------------------------------------------------------------
    // Core Methods
    // ------------------------------------------------------------


    /*
     * generateCode(c)
     * - generates the binary code for
     *   character c.
     */
    std::string generateCode(char c);

public:

    ahencode():model(NULL){};

    /*
     * encodeBuffer(s)
     *
     * Memory Allocation    :
     * Memory Deallocation  :
     *
     * Return :
     */
    std::string* encodeBuffer(std::string s, bool flag);

};

#endif //ADAPTIVE_HUFFMAN_AHENCODE_H
