//
// Created by Demon on 01/04/16.
//

#include "ahdecode.h"

// ------------------------------------------------------------
// Core Methods
// ------------------------------------------------------------

std::string ahdecode::decodeBuffer(std::string code,bool flag){
    std::string result;

    HuffmanTree::node* n = model->ROOT;
    int read = -1;
    char cc = 0;

    for (auto c = code.begin();c != code.end();) {

        int dir = (*c == '1') ? 1 : 0;
        std::cout << "-> " << dir << std::endl;
        //travel
        HuffmanTree::node* t = travel(n,dir);
        if (read >=0 ){
            std::cout << "reading : " << read << std::endl;
            cc |= dir << read;
            if (!read) {
                result.push_back(cc);
                std::cout << "pusing : " << cc;
                model->update(cc);
                cc = 0;
            }
            read--;
            c++;
            continue;
        }
        if (t == NULL || t == model->NYT){
            // target is NYT
            n = model->ROOT;                        // reset to ROOT

            if (t == NULL){
                // special case : no nodes in tree
                read = 7;
            } else{
                read = 7;
                c++;
            }
        }else if (t->isLeaf()){
            // target is leaf
            n = model->ROOT;                        // reset to ROOT

            result.push_back(t->getCode());
            model->update(t->getCode());
            c++;
        }else if(t->isInternal()){
            // target is internal node
            n = t;
            c++;
        }
    }

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