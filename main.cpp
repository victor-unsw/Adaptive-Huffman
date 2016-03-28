#include <iostream>
#include <string>

#include "model.h"

using namespace std;

int main(int argc,const char** argv) {

    HuffmanTree tree;

    string s("e eae de eabe eae dcf");
    for (auto it=s.begin();it!=s.end();it++) {
        tree.update(*it);
    }
    tree.display();
    return 0;
}