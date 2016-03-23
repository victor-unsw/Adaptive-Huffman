//
// Created by Demon on 23/03/16.
//

#ifndef ADAPTIVE_HUFFMAN_MODEL_H
#define ADAPTIVE_HUFFMAN_MODEL_H

#include <list>

class HuffmanTree{

    class node;

    class node{
        node        * p,                                // parent node
                    * l,                                // left node
                    * r;                                // right node

        unsigned    wt;                                 // weight of node
        bool        is_internal;                        // Leaf / Internal Node
        bool        NYT;                                // is 'not yet transferred' Node

        // ------------------------------------------------------------
        // Copy Constructor -- hidden
        // ------------------------------------------------------------
        node(node& n){}

    public:
        // ------------------------------------------------------------
        // Constructor & Destructor
        // ------------------------------------------------------------

        node(node* parent = NULL,node* left = NULL,node* right = NULL, bool isNYT = false)
                :p(parent),l(left),r(right),NYT(isNYT),wt(0),is_internal(false) {}

        ~node(){
            p = l = r = NULL;
            // further can be improved by removing node reference from p,l,r explicitly
        }

        // ------------------------------------------------------------
        // Node Accessibility functions
        // ------------------------------------------------------------

        node* getParent(){
            return p;
        }
        node* setParent(node* p);

        node* getLeft(){
            return l;
        }
        node* setLeft(node* l);

        node* getRight(){
            return r;
        }
        node* setRight(node* r);

        // ------------------------------------------------------------
        // Node State Functions
        // ------------------------------------------------------------

        bool isInternal(){
            return is_internal & !NYT;
        }

        bool isLeaf(){
            return !is_internal & !NYT;
        }

        bool isNYT(){
            return !is_internal & NYT;
        }

        /*
         * Converts current node into Internal Node.
         */
        void makeInternal();

        /*
         * Converts current node into NYT Node.
         */
        void makeNYT();

        // ------------------------------------------------------------
        // Node Weight Functions
        // ------------------------------------------------------------

        unsigned getWeight(){
            return wt;
        }

        /*
         * incrementWeight(..)
         * - Increases the weight of current node by 1.
         */
        void incrementWeight();

    };

    class block{
    private:
        std::list<node*> L;

    public:
        // ------------------------------------------------------------
        // Constructor & Destructor
        // ------------------------------------------------------------
        block():L(){}

        ~block(){
            // remove references
            if (!L.empty())
                for (auto it=L.begin();it<L.end();it++)
                    *it = NULL;
        }

        // ------------------------------------------------------------
        // Block Utility Functions
        // ------------------------------------------------------------

        /*
         * getBlockSize()
         * - returns size of list L i.e. block
         */
        size_t size(){
            return L.size();
        }

        /*
         * isEmpty()
         * - returns whether block is empty or not.
         */
        bool empty(){
            return L.empty();
        }


        // ------------------------------------------------------------
        // Block Core Functions
        // ------------------------------------------------------------

        /*
         * push(..)
         * - pushes the pt to node in front
         * - fresh node in block is at front
         * - leader node in block is at back
         */
        void push(node* n);

    };


public:


};





#endif //ADAPTIVE_HUFFMAN_MODEL_H
