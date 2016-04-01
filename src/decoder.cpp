//
// Created by Demon on 23/03/16.
//
#include <iostream>
#include "decoder.h"

// ------------------------------------------------------------
// Core Methods
// ------------------------------------------------------------

std::string* Decoder::decodeBuffer(const std::string& code){

    std::string* result = new std::string;


    char out = 0;                                           // output character
    int r = -1;                                             // read character position
    bool exitCode = false;
    HuffmanTree::node* n = model->ROOT;

    for (auto c = code.begin();c!=code.end(); c++){
        // for each character in string ... analyse its bits



        char cc  = *c;                                          // current code

        for (int i = 7; i >= 0; ) {
            // analyse each bit of character

            char x = 0; x |= 1 << i;
            int dir = (cc&x) ? 1 : 0;

            if(exitCode & dir){                                 // i.e. if it's EXIT code & next bit is '1'
                // stop judging the code                        // that signals byte padding
                exitCode = false;
                r = -1;

                out = 0;
                n = model->ROOT;                                //reset

                break;
            }else if(exitCode)
                exitCode = false;

            // build character from stream of bits
            if (r >= 0){
                out |= dir << r;                                // mark dir in 'out' character
                r--;                                            // decrease read count bit
                i--;
                if (r < 0){
                    // last bit read
                    result->push_back(out);                     // add 'out' character to string result
                    model->update(out);                          // update model
                    out = 0;                                    // reset out
                }
            }else{
                // travel through tree
                HuffmanTree::node* t = travel(n, dir);          // target node

                if (t == NULL || t == model->NYT){
                    // target is NYT
                    n = model->ROOT;                             // reset n

                    if (t == NULL){
                        //special case : no nodes in tree
                        r = 7;                                  // read next 8 bits including self
                    } else{
                        r = 7;                                  // read next 8 bits
                        i--;
                        exitCode = true;
                    }
                }else if(t->isLeaf()){
                    // target is leaf
                    n = model->ROOT;                             // reset n

                    out = t->getCode();                         // get code from leaf
                    result->push_back(out);                     // add to result
                    model->update(out);                          // update tree
                    out = 0;                                    // reset 'out'
                    i--;
                }else if(t->isInternal()){
                    // target is internal node
                    n = t;                                      // update n
                    i--;
                }

            }
        }

    }

    model->display();

    return result;
}


/*
 * travel(n,dir).
 * - if dir = 1, then return n->right
 * - if dir = 0, then return n->left
 * - if no child, return null
 */
HuffmanTree::node* Decoder::travel(HuffmanTree::node* n,int dir){
    HuffmanTree::node* t = NULL;
    if (dir)
        t = n->getRight();
    else
        t = n->getLeft();
    return t;
}