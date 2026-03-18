#include <iostream>
#include <vector>
#include "splines.h"
#include <cmath>
#include <fstream>

int main(){

    // ---------- TESTS (for opgave B) ----------
    std::vector<double> x_test = {1,2,3,4,5};

    // Test 1: y = 1
    std::vector<double> y_test = {1,1,1,1,1};
    qspline s_test(x_test,y_test);

    std::cout << "Test y=1:\n";
    for(int i=0;i<s_test.n-1;i++){
        std::cout << "i=" << i 
                  << " b=" << s_test.b[i] 
                  << " c=" << s_test.c[i] << "\n";
    }

    // Test 2: y = x
    y_test = {1,2,3,4,5};
    qspline s_lin(x_test,y_test);

    std::cout << "\nTest y=x:\n";
    for(int i=0;i<s_lin.n-1;i++){
        std::cout << "i=" << i 
                  << " b=" << s_lin.b[i] 
                  << " c=" << s_lin.c[i] << "\n";
    }

    // Test 3: y = x^2
    y_test = {1,4,9,16,25};
    qspline s_quad(x_test,y_test);

    std::cout << "\nTest y=x^2:\n";
    for(int i=0;i<s_quad.n-1;i++){
        std::cout << "i=" << i 
                  << " b=" << s_quad.b[i] 
                  << " c=" << s_quad.c[i] << "\n";
    }

    // ---------- DATA (cos(x)) ----------
    std::vector<double> x;
    std::vector<double> y;

    for(double xi = 0; xi <= 9; xi += 0.5){
        x.push_back(xi);
        y.push_back(std::cos(xi));
    }

    // ---------- LINEAR SPLINE (del A) ----------
    std::ofstream file("data.txt");

    for(double z = 0; z <= 9; z += 0.01){
        file << z << " "
             << cos(z) << " "
             << linterp(x,y,z) << " "
             << linterpInteg(x,y,z) << "\n";
    }

    file.close();

    // ---------- QUADRATIC SPLINE (del B) ----------
    qspline s(x,y);

    std::ofstream file2("data_qspline.txt");

    for(double z = 0; z <= 9; z += 0.01){
        file2 << z << " "
              << cos(z) << " "
              << s.eval(z) << " "
              << s.integ(z) << "\n";
    }

    file2.close();

    auto f = make_qspline(x,y);

    std::ofstream file3("data_func.txt");

    for(double z=0; z<=9; z+=0.01){
        file3 << z << " "
          << cos(z) << " "
          << f(z) << "\n";
    }

    file3.close();
    return 0;
}