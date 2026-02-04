#include <iostream>
#include <cmath>
#include <numbers>
#include "sfuns.h"

int main(){
    //part 1
    double pi = std::acos(-1.0); // pi
    double e = std::exp(1.0); // e
    double sqrt2 = std::sqrt(2.0);
    double power = std::pow(2, 0.2);
    double exppi = std::exp(pi); // e^pi
    double piexp = std::pow(pi, e);
    std::cout << "sqrt(2) = " << sqrt2 << "\n";
    std::cout << "pow(2, 1/5) = " << power << "\n";
    std::cout << "exp(pi) = " << exppi << "\n";
    std::cout << "pow(pi, e) = " << piexp << "\n";
    
    //part 3
    for(size_t i=1; i <= 10; i++){
        std::cout << "fgamma(" << i << ") = " << sfuns::fgamma(i) << "\n";
    }
    for(size_t i=1; i <= 10; i++){
        std::cout << "lngamma(" << i << ") = " << sfuns::lngamma(i) << "\n";
    }
    return 0;
}
