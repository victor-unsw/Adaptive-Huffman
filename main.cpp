#include <iostream>
#include <string>

#include "model.h"
#include "encoder.h"

using namespace std;

int main(int argc,const char** argv) {


    Encoder e;
    e.display();

    /*
    HuffmanTree tree;

    string s("e eae de eabe eae dcf");
    for (auto it=s.begin();it!=s.end();it++) {
        tree.update(*it);
    }

    tree.display();

    const string* path = tree.path('x');
    cout << "path : " << *path << endl;
    */
    return 0;
}