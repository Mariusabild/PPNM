#include<iostream>
#include<limits>
#include<cmath>
#include<iomanip>
#include"approx.h"
/*

bool approx(double a, double b, double acc = 1e-9, double eps = 1e-9) {
    double diff = std::abs(a - b);
    if (diff <= acc) return true;  // absolute tolerance
    double max_ab = std::max(std::abs(a), std::abs(b));
    return diff <= eps * max_ab;   // relative tolerance
}
*/

int main(){
    //part 1
    float f = 1.0f;
    while((float)(1.0f + f) != 1.0f){
        f/=2.0f;
    }
    f*=2.0f;

    double d = 1.0d;
    while((double)(1.0d + d) != 1.0d){
        d/=2.0d;
    }
    d*=2.0d;
    long double l = 1.0L; while((long double)(1.0L+l) != 1.0L){
        l/=2.0l;
    }
    l*=2.0l;
    std::cout << "float epsilon = " << f << "\n";
    std::cout << "double epsilon = " << d << "\n";
    std::cout << "long float epsilon = " << l << "\n";
 
    std::cout << "limit epsilon float " << std::numeric_limits<float>::epsilon() << "\n";
    std::cout << "limit epsilon double " << std::numeric_limits<double>::epsilon() << "\n";
    std::cout << "limit epsilon long double " << std::numeric_limits<long double>::epsilon() << "\n \n";
    std::cout << "We see that compuation manually match the one by limits." << "\n \n";

    std::cout << "approximate epsilon double " << std::pow(2,-52) << "\n";
    std::cout << "approximate epsilon float " << std::pow(2,-23) << "\n";
    std::cout << "Indeed the results match again using this method." << "\n \n";

    //part 2
    double epsilon = std::pow(2,-52);
    double tiny = epsilon/2;
    double a = 1+tiny+tiny;
    double b = tiny+tiny+1;
    std::cout << "a==b ? " << (a==b ? "true":"false") << "\n";
    std::cout << "a>1  ? " << (a>1  ? "true":"false") << "\n";
    std::cout << "b>1  ? " << (b>1  ? "true":"false") << "\n";
    std::cout << "The computation is done from the left, so a>1 is false since the epsilons is added after 1, the opposite is true in b>1." << "\n";

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "tiny=" << tiny << "\n";
    std::cout << "1+tiny+tiny=" << a << "\n";
    std::cout << "tiny+tiny+1=" << b << "\n";
    std::cout << "Indeed this confirms my theory." << "\n";

    //part 3
    double d1 = 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1;
    double d2 = 8*0.1;
    std::cout << "d1==d2? " << (d1==d2 ? "true":"false") << "\n"; 

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "d1=" << d1 << "\n";
    std::cout << "d2=" << d2 << "\n";
    std::cout << "d1 is equal to d2: "<< (approx(d1,d2)==1 ?"true":"false")<< "\n";
}


