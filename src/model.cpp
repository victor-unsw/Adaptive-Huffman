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


/*
 * getList(..)
 * - returns the L as reference pointer
 * - copy of list isn't made to save time.
 */
std::list<HuffmanTree::node*>& HuffmanTree::block::getList(){
    return L;
}







// ==============================================================================
// HuffmanTree
// ==============================================================================

// ------------------------------------------------------------------------------
// Core functions

void HuffmanTree::update(unsigned char c) {
    std::cout << "\nupdating...." << std::endl;

    P   = getSymbolNode(c);
    LI  = NULL;

    // Step 1
    // P is NYT i.e. symbol doesn't
    // exists before.
    if (P == NYT){
        insert(c);
    }
    // Step 2
    // P is Symbol node i.e. symbol
    // already in tree
    else{

    }


    // Step 3
    // Slide And Increment until root
    while (P != NULL)
        slideAndIncrement();

    // Step 4
    // Slide And Increment Leaf_To_Increment
    if (LI != NULL){
        P = LI;
        slideAndIncrement();
    }

    display();
    P   = NULL;
    LI  = NULL;
    std::cin.get();
}

/*
 * slideAndIncrement()
 * - slides the P node according
 *   to algorithm.
 */
void HuffmanTree::slideAndIncrement(){
    unsigned wt         = P->getWeight();
    node* parent        = P->getParent();
    block* target_block = getNextBlock(P);

    if (target_block!=NULL)
        slide(P,target_block);

    // remove from current block
    bool removed = removeNodeFromBlock(P);
    if (!removed) {
        P->printInfo();
        std::cout << "didn't existed in any block" << std::endl;
    }

    // increment weight
    P->incrementWeight();

    // insert into new block
    addNodeToBlock(P);

    if (P->isInternal())
        P = parent;
    else
        P = P->getParent();
}

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
 * - add R to symbol_map[c]
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
    symbol_map[c] = R;

    size+=2;
    return P;
}

/*
 * slide(n,b)
 * - slides n node through b block
 *   by swapping n with each node in
 *   b block.
 */
void HuffmanTree::slide(node* n1,block* b){
    if (n1 == NULL || b == NULL)
        return;
    std::list<node*> L = b->getList();
    for (auto it=L.begin();it!=L.end();it++)
        swap(n1,*it);
}

/*
 * swap(n1,n2).
 * - swaps n1 with n2
 * - fixes parent child relationship
 *
 * - doesn't work while swapping parent with its child
 */
void HuffmanTree::swap(node* n1,node* n2){
    // can't swap parent with child
    if (n1->getParent() == n2 || n2->getParent() == n1)
        return;

    node temp;                                  // local variable; memory deallocated automatically
    replace(&temp,n2);
    replace(n2,n1);
    replace(n1,&temp);
}




// ------------------------------------------------------------------------------
// Block Management functions

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

/*
 * getNextBlock()
 * - returns the next block in the
 *   block hierarchy. i.e. LILILILI
 * - returns NULL if no such block
 *   exists.

 * NOTE : next block is searched in the
 *        opposite blocks i.e. L for I
 *        and I for L.
 */
HuffmanTree::block* HuffmanTree::getNextBlock(node* n){
    if (n->isInternal()){
        // search next block in leaf_blocks
        // target block weight = n->wt + 1
        return getBlock(leaf_block,n->getWeight()+1);
    }else if(n->isLeaf()){
        // search next block in internal_blocks
        // target block weight = n->wt
        return getBlock(internal_block,n->getWeight());
    }
}


// ------------------------------------------------------------------------------
// Utility function


/*
 * replace(n1,n2)
 * - replaces n1 in place of n2.
 * - fixes parent child relation
 */
void HuffmanTree::replace(node* n1,node* n2){
    // in no scenario we replace with root
    // of the tree
    if (ROOT == n2 || n2->getParent() == NULL) {
        std::cout << "trying to replace with root" << std::endl;
        return;
    }

    bool left = n2->getParent()->getLeft() == n2;           // is n2 left child of parent

    n1->setParent(n2->getParent());
    if (left)
        n2->getParent()->setLeft(n1);
    else
        n2->getParent()->setRight(n1);
}

/*
 * getSymbolNode(..)
 * - returns the leaf node from
 *   symbol_map for particular c
 *   character if exists.
 *   else return NYT.
 */
HuffmanTree::node* HuffmanTree::getSymbolNode(unsigned char c) {
    std::unordered_map<unsigned char,node*>::iterator it = symbol_map.find(c);
    if (it == symbol_map.end())
        return NYT;
    return it->second;
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
 * getBlock(..)
 * - returns blocks[wt] value;
 * - returns null if no such value exist.
 */
HuffmanTree::block* HuffmanTree::getBlock(std::unordered_map<int,block*>& blocks,int wt){
    std::unordered_map<int,block*>::iterator it = blocks.find(wt);
    return it == blocks.end() ? NULL : it->second;
}

/*
 * addBlock(..)
 * - adds a new block at given [wt] in the map.
 *
 * Memory Allocated     : temp (new block)
 * Memory Deallocated   : none
 *
 * return : new block
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



void HuffmanTree::drawSpaces(int d) {
    for(int i=0;i<2*d;i++)
        std::cout << " ";
}

void HuffmanTree::drawTree(node *n, int d) {
    drawSpaces(d);
    n->printInfo();
    std::cout << std::endl;
    if (n->hasLeft())
        drawTree(n->getLeft(),d+1);
    if (n->hasRight())
        drawTree(n->getRight(),d+1);
}

void HuffmanTree::display(){
    std::cout << "HUFFMAN :- \n";
    drawTree(ROOT,0);
    std::cout << "\n\n";
}










