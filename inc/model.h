//
// Created by Demon on 23/03/16.
//

#ifndef ADAPTIVE_HUFFMAN_MODEL_H
#define ADAPTIVE_HUFFMAN_MODEL_H

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
        /*
         * setParent(..)
         * - sets new parent 'p'
         * - returns previous parent
         */
        node* setParent(node* p){
            node* previous = this->p;
            this->p = p;
            return previous;
        }

        node* getLeft(){
            return l;
        }
        /*
         * setLeft(..)
         * - sets new left child
         * - returns previous left child
         */
        node* setLeft(node* l){
            node* previous = this->l;
            this->l = l;
            return previous;
        }

        node* getRight(){
            return r;
        }
        /*
         * setRight(..)
         * - sets new right child 'r'
         * - returns previous right child
         */
        node* setRight(node* r){
            node* previous = this->r;
            this->r = r;
            return previous;
        }

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
         * Make node as 'internal node'.
         */
        void makeInternal(){
            is_internal = true;
            NYT         = false;
        }

        /*
         * Make node as 'NYT node'.
         */
        void makeNYT(){
            is_internal = false;
            NYT         = true;
        }

        // ------------------------------------------------------------
        // Node Weight Functions
        // ------------------------------------------------------------

        unsigned getWeight(){
            return wt;
        }

        void incrementWeight(){
            wt++;
        }

    };


};





#endif //ADAPTIVE_HUFFMAN_MODEL_H
