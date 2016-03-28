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

/*
 * remove(..)
 * - removes node n pointer from list
 * - returns true if such node pointer existed
 */
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

/*
 * insert(node n) :-
 * - create left child (as NYT node)
 * - create right child (as character node)
 * - convert the NYT to internal node
 * - create parent child relationships
 * - P is NYT i.e. the new internal node
 * - LI is right child i.e. the character node
 * - point NYT to left child
 * - add R to it's block
 * - add P to it's block
 *
 * Memory Allocation    :   Right Node
 *                          Left Node
 * Memory Deallocation  :   None
 *
 * Returns : P
 */
HuffmanTree::node* HuffmanTree::insert(unsigned char c){
    node* R = new node(NYT,NULL,NULL, false,c);
    node* L = new node(NYT,NULL,NULL,true);
    NYT->makeInternal();                                                // make it internal
    NYT->setLeft(L);                                                    // set left child
    NYT->setRight(R);                                                   // set right child
    P   = NYT;                                                          // the new internal node
    LI  = R;                                                            // leaf to increment is Right child
    NYT = L;                                                            // new NYT is left child

    // block management
    addNodeToBlock(R);
    addNodeToBlock(P);

    return P;
}


/*
 * getNodeBlock(..)
 * - returns block of given node from either
 *   internal_block / leaf_block as per config.
 *
 * NOTE : blocks are returned acc. to current state
 *        of node.
 */
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


/*
 * addBlock(..)
 * - adds a new block at given [wt] in the map.
 */
HuffmanTree::block* HuffmanTree::addBlock(std::unordered_map<int,block*>& blocks,int wt){
    block* temp = new block;
    blocks[wt] = temp;
    return temp;
}


/*
 * getOrAddBlock(..)
 * - it returns the block if it exists
 *   or adds a new block and returns it
 */
HuffmanTree::block* HuffmanTree::getOrAddBlock(std::unordered_map<int,block*>& blocks,int wt){
    std::unordered_map<int,block*>::iterator it = blocks.find(wt);
    return it == blocks.end() ? addBlock(blocks,wt) : it->second;
}


/*
 * addNodeToBlock(..)
 * - adds node to the block
 *   as per the configuration
 *   of the node.
 */
void HuffmanTree::addNodeToBlock(node* n){
    block* temp = n->isInternal() ? getOrAddBlock(internal_block,n->getWeight()) : n->isLeaf() ?
                                                                                   getOrAddBlock(leaf_block,n->getWeight()) : NULL;
    if (temp != NULL)
        temp->push(n);
}


/*
 * removeNodeFromBlock(..)
 * - removes node from block if
 *   it exists in there.
 * - returns false if node didn't
 *   existed in blocks yet.
 */
bool HuffmanTree::removeNodeFromBlock(node* n){
    block* current_block = getNodeBlock(n);
    if (current_block == NULL)
        return false;
    return current_block->remove(n);
}