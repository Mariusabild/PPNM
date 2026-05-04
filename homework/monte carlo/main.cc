#include "monte_carlo.h"
#include <cmath>
#include <functional>
#include <vector>
#include <iostream>
#include <fstream>


int main(){

    auto f_circle = [](const std::vector<double>& x){
    if(x[0]*x[0] + x[1]*x[1] <= 1.0) return 1.0;
    else return 0.0;
    };

    auto f_exp = [](const std::vector<double>& x){
        return std::exp(-(x[0]*x[0] + x[1]*x[1]));
    };

    std::vector<double> a = {0,0};
    std::vector<double> b = {1,1};

    std::ofstream circle_data("circle_data.txt");
    std::ofstream exp_data("exp_data.txt");

    int max_points = 1000000;
    double theoretical_result_circle = M_PI/4;
    double theoretical_result_exp = 0.557746; //Note this is a numerically calcualted value from table

    //Test 1: unit circle
    int N = 100000;
    lcg rnd1(1234);
    auto[result_circle, error_circle] = plainmc(f_circle, a, b, N, rnd1);
    std::cout << "Calculated area circle = " << result_circle << ", using " << N << " sampling points." << "\n";
    std::cout << "Actual area circle = " << theoretical_result_circle << "\n \n";

    //Test 2: exp(-(x^2+y^2))
    lcg rnd2(1234);
    auto[result_exp, error_exp] = plainmc(f_exp, a, b, N, rnd2);
    std::cout << "Calculated area exp(-(x^2+y^2)) x and y from 0 to 1 = " << result_exp << ", using " << N << " sampling points" << "\n";
    std::cout << "Nummerical value of area exp(-(x^2+y^2)) x and y from 0 to 1 by looking at table " <<  theoretical_result_exp << "\n \n";

    //Plot
    for(int N = 10; N <= max_points; N*= 2){
        lcg rnd3(1234);
        auto[result_circle, error_circle] = plainmc(f_circle, a, b, N, rnd3);
        double actual_error_circle = std::abs(result_circle-theoretical_result_circle);
        circle_data << N << " " << actual_error_circle << " " << error_circle << "\n";
    }
    
    circle_data.close();

    for(int N = 10; N <= max_points; N*= 2){
        lcg rnd4(1234);
        auto[result_exp, error_exp] = plainmc(f_exp, a, b, N, rnd4);
        double actual_error_exp = std::abs(result_exp-theoretical_result_exp);
        exp_data << N << " " << actual_error_exp << " " << error_exp << "\n";
    }
    exp_data.close();

    double A = 1.0;
    double B = 2.0;
    double C = 3.0;
    std::vector<double> a_ellipsoid = {-A,-B,-C};
    std::vector<double> b_ellipsoid = {A,B,C};

    double V_ellipsoid = (4.0/3.0)*M_PI*A*B*C;

    auto f_ellipsoid = [A,B,C](const std::vector<double>& x){
        if((x[0]/A)*(x[0]/A)  + (x[1]/B)*(x[1]/B) + (x[2]/C)*(x[2]/C) <= 1.0) return 1.0;
        else return 0.0;
    };

    //Volume of epsiloid
    lcg rnd5(1234);
    auto[result_ellipsoid, error_ellipsoid] = plainmc(f_ellipsoid, a_ellipsoid, b_ellipsoid, N, rnd5);
    std::cout << "Calculated volume ellipsoid = " << result_ellipsoid << ", using " << N << " sampling points" << "\n";
    std::cout << "Theoretical volume of ellipsoid " <<  V_ellipsoid << "\n";

    return 0;
    
}