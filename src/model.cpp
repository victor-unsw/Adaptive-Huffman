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


bool HuffmanTree::block::remove(node *n) {
    std::list<node*>::iterator target = std::find(L.begin(),L.end(),n);
    if (target != L.end()) {
        L.erase(target);
        return true;
    }
    return false;
}




// ==============================================================================
// HuffmanTree
// ==============================================================================

HuffmanTree::node* HuffmanTree::insert(unsigned char c){
    node* R = new node(NYT,NULL,NULL, false,c);
    node* L = new node(NYT,NULL,NULL,true);
    NYT->makeInternal();                                                // make it internal
    NYT->setLeft(L);                                                    // set left child
    NYT->setRight(R);                                                   // set right child
    NYT = L;                                                            // new NYT is left child

    // block management remaining

    return R->getParent();
}

HuffmanTree::block* HuffmanTree::getNodeBlock(node *n) {
    std::unordered_map<int,block*>::iterator it;
    if (n->isLeaf()){
        // search in leaf_block
        it = leaf_block.find(n->getWeight());
        return it == leaf_block.end() ? NULL : it->second;              // return NULL or value i.e. block*
    } else if(n->isInternal()){
        // search in internal_block
        it = internal_block.find(n->getWeight());
        return it == leaf_block.end() ? NULL : it->second;              // " "
    }
    return NULL;
}

HuffmanTree::block* HuffmanTree::addBlock(std::unordered_map<int,block*>& blocks,int wt){
    block* temp = new block;
    blocks[wt] = temp;
    return temp;
}