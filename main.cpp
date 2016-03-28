#include <iostream>

#include "model.h"

using namespace std;

int main(int argc,const char** argv) {

    HuffmanTree tree;
    tree.update('a');
    tree.update('b');
    tree.update('c');
    tree.update('d');
    return 0;
}