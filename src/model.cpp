//
// Created by Demon on 23/03/16.
//

#include <iostream>
#include "model.h"


// ==============================================================================
// HuffmanTree::node
// ==============================================================================


// ------------------------------------------------------------------------------
// Node Accessibility functions

/*
 * setParent(..)
 * - Sets the new parent as parameter 'p'
 * - returns previous parent
 */
HuffmanTree::node* HuffmanTree::node::setParent(HuffmanTree::node* p){
    HuffmanTree::node* previous = this->p;
    this->p = p;
    return previous;
}

/*
 * setLeft(..)
 * - sets the left child as parameter 'l'
 * - returns previous left child
 */
HuffmanTree::node* HuffmanTree::node::setLeft(HuffmanTree::node* l){
    HuffmanTree::node* previous = this->l;
    this->l = l;
    return previous;
}

/*
 * setRight(..)
 * - sets the right child as parameter 'r'
 * - returns previous right child
 */
HuffmanTree::node* HuffmanTree::node::setRight(HuffmanTree::node* r){
    HuffmanTree::node* previous = this->r;
    this->r = r;
    return previous;
}

/*
 * setCode(..)
 * - sets the code of leaf node as parameter 'c'.
 */
void HuffmanTree::node::setCode(unsigned char c) {
    this->code = c;
}


// ------------------------------------------------------------------------------
// Node State Functions

/*
 * Converts current node into Internal Node.
 */
void HuffmanTree::node::makeInternal(){
    is_internal = true;
    NYT         = false;
    code        = 0;
}

/*
 * Converts current node into NYT Node.
 */
void HuffmanTree::node::makeNYT(){
    is_internal = false;
    NYT         = true;
    code        = 0;
}



// ------------------------------------------------------------------------------
// Node Weight Functions

/*
 * incrementWeight(..)
 * - Increases the weight of current node by 1.
 */
void HuffmanTree::node::incrementWeight(){
    wt++;
}






// ==============================================================================
// HuffmanTree::block
// ==============================================================================


// ------------------------------------------------------------------------------
// Block Core functions

/*
 * push(..)
 * - pushes the pt to node in front
 * - fresh node in block is at front
 * - leader node in block is at back
 */
void HuffmanTree::block::push(node *n) {
    L.push_front(n);
}


