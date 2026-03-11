#include "vec.h"
#include <iostream>

int main() {

    pp::vector v;
    pp::vector w;

    v.push_back(1);
    w.push_back(2);
    v += w;
    pp::vector q(2);
    
    std::cout << v[0] << "\n";
    
    return 0;
}