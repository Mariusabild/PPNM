#include <iostream>
#include <vector>
#include "splines.h"
#include <cmath>
#include <fstream>

/*
AI use: AI has assisted with tasks such as debugging, helping to translate algorithms and pseudocode from lecture pdf notes into C++ syntax, and help design tests.
Since I made many of the homeworks before it was stated that we should mark the AI-generated code, this is not possible. In general, AI has been used as a tool in all project files.
*/

int main(){

    std::cout << "For part A, please inspect linear_spline.png. Here we see the expected behaviour, the spline intercepts the points exactly linearly." << "\n\n";

    // TESTS
    std::vector<double> x_test = {1,2,3,4,5};

    // Test 1: y = 1
    std::vector<double> y_test = {1,1,1,1,1};
    qspline s_test(x_test,y_test);

    std::cout << "Test y=1:\n";
    for(int i=0;i<s_test.n-1;i++){
        std::cout << "i=" << i  << " b=" << s_test.b[i]  << " c=" << s_test.c[i] << "\n";
    }

    // Test 2: y = x
    y_test = {1,2,3,4,5};
    qspline s_lin(x_test,y_test);

    std::cout << "\nTest y=x:\n";
    for(int i=0;i<s_lin.n-1;i++){
        std::cout << "i=" << i  << " b=" << s_lin.b[i]  << " c=" << s_lin.c[i] << "\n";
    }

    // Test 3: y = x^2
    y_test = {1,4,9,16,25};
    qspline s_quad(x_test,y_test);

    std::cout << "\nTest y=x^2:\n";
    for(int i=0;i<s_quad.n-1;i++){
        std::cout << "i=" << i  << " b=" << s_quad.b[i]  << " c=" << s_quad.c[i] << "\n";
    }
    std::cout << "\nThe obtained coefficients match the analytical ones." << "\n";
    //DATA (cos(x))
    std::vector<double> x;
    std::vector<double> y;

    for(double xi = 0; xi <= 9; xi += 0.5){
        x.push_back(xi);
        y.push_back(std::cos(xi));
    }

    //LINEAR SPLINE
    std::ofstream file("data.txt");

    for(double z = 0; z <= 9; z += 0.01){
        file << z << " " << cos(z) << " " << linterp(x,y,z) << " " << linterpInteg(x,y,z) << "\n";
    }

    file.close();

    // QUADRATIC SPLINE
    qspline s(x,y);

    std::ofstream file2("data_qspline.txt");

    for(double z = 0; z <= 9; z += 0.01){
    file2 << z << " " << cos(z) << " " << s.eval(z) << " " << s.integ(z) << " " << s.deriv(z) << " " << -sin(z) << "\n";
}
    file2.close();

    auto f = make_qspline(x,y);

    std::ofstream file3("data_func.txt");

    for(double z=0; z<=9; z+=0.01){
        file3 << z << " " << cos(z) << " " << f(z) << "\n";
    }

    file3.close();

    std::cout << "For part B, please inspect, qspline.png and derivative.png." << "\n";
    std::cout << "For part C, please inspect cubic_compare.png, and functional.png." << "\n";
    return 0;
}