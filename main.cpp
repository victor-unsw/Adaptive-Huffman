#include <iostream>

using namespace std;

#include "decoder.h"
#include "encoder.h"

int main(int argc,const char** argv) {

    Encoder e;
    e.display();

    Decoder d;
    d.display();


    return 0;
}