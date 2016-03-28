//
// Created by Demon on 23/03/16.
//

#ifndef ADAPTIVE_HUFFMAN_MODEL_H
#define ADAPTIVE_HUFFMAN_MODEL_H

#include <list>
#include <unordered_map>
#include <algorithm>

class HuffmanTree{

    class node;

    class node{
        friend class HuffmanTree;
        node            * p,                                // parent node
                        * l,                                // left node
                        * r;                                // right node

        unsigned char   code;                               // leaf node code
        unsigned        wt;                                 // weight of node
        bool            is_internal;                        // Leaf / Internal Node
        bool            NYT;                                // is 'not yet transferred' Node

        // ------------------------------------------------------------
        // Copy Constructor -- hidden
        // ------------------------------------------------------------
        node(node& n){}

    public:
        // ------------------------------------------------------------
        // Constructor & Destructor
        // ------------------------------------------------------------

        node(node* parent = NULL,node* left = NULL,node* right = NULL, bool isNYT = false, unsigned char c = 0)
                :p(parent),l(left),r(right),NYT(isNYT),wt(0),is_internal(false),code(isNYT?(char)0:c) {}

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

        unsigned char getCode(){
            return code;
        }
        void setCode(unsigned char c);

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


        void showNode(){
            std::cout << "Self : " << this << ":" << this->code
            << " , P : " << p  << ":" << (p!=NULL? char(p->code) :'0')
            << " , L : " << l  << ":" << (l!=NULL? char(l->code) :'0')
            << " , R : " << r  << ":" << (r!=NULL? char(r->code) :'0')
            << std::endl;
        }

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
                for (auto it=L.begin(); it!=L.end() ;it++)
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


        void showBlockNodes(){
            std::cout << "BLOCK :-\n";
            for(auto it=L.begin();it!=L.end();it++){
                (*it)->showNode();
            }
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

        /*
         * remove(..)
         * - removes node n pointer from list
         * - returns true if such node pointer existed
         */
        bool remove(node* n);

        /*
         * getList(..)
         * - returns the L as reference pointer
         * - copy of list isn't made to save time.
         */
        std::list<node*>& getList();

    };


    // ------------------------------------------------------------
    // Instance Variables
    // ------------------------------------------------------------

    node*       ROOT;                                                       // pointer to Root node
    node*       NYT;                                                        // pointer to NYT node
    node*       P;                                                          // POINTER TO SYMBOL NODE
    node*       LI;                                                         // LEAF TO INCREMENT
    unsigned    size;                                                       // total nodes in tree
    unsigned    internal_nodes;                                             // total internal nodes
    unsigned    leaf_nodes;                                                 // total leaf nodes

    std::unordered_map<int,block*> internal_block;                          // hash map for internal_node->internal_block
    std::unordered_map<int,block*> leaf_block;                              // hash map for leaf_node->leaf_block


    // ------------------------------------------------------------
    // CORE Functions
    // ------------------------------------------------------------

    /*
     * insert(..)
     * - inserts new node at NYT node.
     *
     * Memory Allocation    :   Right Node
     *                          Left Node
     * Memory Deallocation  :   None
     *
     * Returns : internal node created instead of NYT
     */
    node* insert(unsigned char c);

    /*
     * swap(n1,n2).
     * - swaps n1 with n2
     * - fixes parent child relationship
     */
    void swap(node* n1,node* n2);

    /*
     * slide(n,b)
     * - slides n node through b block
     *   by swapping n with each node in
     *   b block.
     */
    void slide(node* n1,block* b);

    // ------------------------------------------------------------
    // BLOCK Management
    // ------------------------------------------------------------

    /*
     * addNodeToBlock(..)
     * - adds node to the block
     *   as per the configuration
     *   of the node.
     */
    void addNodeToBlock(node* n);

    /*
     * removeNodeFromBlock(..)
     * - removes node from block if
     *   it exists in there.
     */
    bool removeNodeFromBlock(node* n);

    // ------------------------------------------------------------
    // Utility Methods
    // ------------------------------------------------------------


    /*
     * replace(n1,n2)
     * - replaces n1 in place of n2.
     * - fixes parent child relation
     */
    void replace(node* n1,node* n2);

    /*
     * getNodeBlock(..)
     * - returns block of given node from either
     *   internal_block / leaf_block as per config.
     *
     * NOTE : blocks are returned acc. to current state
     *        of node.
     */
    block* getNodeBlock(node* n);

    /*
     * addBlock(..)
     * - adds a new block at given [wt] in the map.
     *
     * Memory Allocated     : temp (new block)
     * Memory Deallocated   : none
     *
     * return : new block
     */
    block* addBlock(std::unordered_map<int,block*>& blocks,int wt);

    /*
     * getOrAddBlock(..)
     * - it returns the block if it exists
     *   or adds a new block and returns it
     */
    block* getOrAddBlock(std::unordered_map<int,block*>& blocks,int wt);

    /*
     * CheckNYT()
     * - checks whether the node pointed by
     *   NYT variable is actually an NYT node.
     */
    bool checkNYT(){
        return NYT->isNYT();
    }


public:

    HuffmanTree():ROOT(NULL),NYT(NULL),size(0),internal_nodes(0),leaf_nodes(0),internal_block(),leaf_block(),P(NULL),LI(NULL){
        // initial state of huffman tree consist of 1 single NYT node
        // NYT itself is the ROOT initially
        ROOT    = new node(NULL,NULL,NULL, true);
        NYT     = ROOT;
        size++;
    }




};





#endif //ADAPTIVE_HUFFMAN_MODEL_H
