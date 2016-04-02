//
// Created by Demon on 01/04/16.
//

#include <iostream>
#include "ahdecode.h"

// ------------------------------------------------------------
// Core Methods
// ------------------------------------------------------------

std::string* ahdecode::decodeBuffer(std::string code,bool flag){
    std::string* result = new std::string;

    // form a new model each time a new line is evaluated;
    model = new HuffmanTree;
    HuffmanTree::node* n = model->ROOT;

    int read = -1;
    char cc = 0;

    for (auto c = code.begin();c != code.end();) {
        if (*c == ' ' && flag) {
            c++;
            continue;
        }

        int dir = (*c == '1') ? 1 : 0;



        if (read >= 0){
            // read character from following digits

            cc |= dir << read;
            if (!read) {
                result->push_back(cc);
                model->update(cc);

                cc = 0;                                         // RESET
                n = model->ROOT;
            }
            read--;
            c++;

        }else{
            // start travelling along the tree

            HuffmanTree::node* t = travel(n,dir);

            // Case 1 : node is NYT
            if (t == NULL || t == model->NYT){
                // target is NYT
                n = model->ROOT;                                // reset to ROOT

                if (t == NULL){
                    // special case : no nodes in tree
                    read = 7;
                    // encode character from current digit
                } else{
                    read = 7;
                    c++;
                }
            }
            // Case 2 : node is LEAF
            else if (t->isLeaf()){
                // target is leaf
                n = model->ROOT;                        // reset to ROOT

                result->push_back(t->getCode());
                model->update(t->getCode());
                c++;
            }else if(t->isInternal()){
                // target is internal node
                n = t;
                c++;
            }
        }

        }

    delete model;
    return result;
}


HuffmanTree::node* ahdecode::travel(HuffmanTree::node* n,int dir){
    HuffmanTree::node* t = NULL;

    if (dir)
        t = n->getRight();
    else
        t = n->getLeft();
    return t;
}


int main(int args,char** argv){

    char*           buffer  = new char[MAX_CHAR];

    bool            FLAG    = (args > 1 && !strcmp(argv[1],"-s"));
    ahdecode        decoder;
    std::string*    output  = NULL;

    while (std::cin.getline(buffer,MAX_CHAR)){

        std::string input(buffer);
        output = decoder.decodeBuffer(input,FLAG);

        if (output != NULL) {
            std::cout << *output << std::endl ;
            delete output;
        }
    }

    return 0;
}