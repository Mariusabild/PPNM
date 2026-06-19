#include<iostream>
#include<cmath>
#include <fstream>
#include "integration.h"

/*
AI use: AI has assisted with tasks such as debugging, helping to translate algorithms and pseudocode from lecture pdf notes into C++ syntax, and help design tests.
Since I made many of the homeworks before it was stated that we should mark the AI-generated code, this is not possible. In general, AI has been used as a tool in all project files.
*/


/*/
PART A:
*/
//Errorfunction
double errorfunction(double z, double acc = 1e-6, double eps = 1e-6){
    if(z < 0) return -errorfunction(-z, acc, eps);

    if(z <= 1) {
        auto f =[](double x){
            return std::exp(-x*x);
        };
        return 2/std::sqrt(M_PI) * integrate(f, 0, z, acc, eps);
    }
    auto f = [z](double t){
        double x = z + (1 - t)/t;
        return std::exp(-x*x)/(t*t);
    };

    return 1 - 2/std::sqrt(M_PI) * integrate(f, 0, 1, acc, eps);
}

int main(){
    //Test functions for verification of numerical integrator
    auto func1 = [](double x) {return std::sqrt(x);};
    auto func2 = [](double x) {return 1/std::sqrt(x);};
    auto func3 = [](double x) {return std::sqrt(1-x*x);};
    auto func4 = [](double x) {return std::log(x)/std::sqrt(x);};

    std::cout << "Analytic: ∫dx √(x) = 2/3 from 0 to 1 |" << "Numerical integrator " << integrate(func1, 0,1) << "\n";
    std::cout << "Analytic: ∫dx 1/√(x) = 2 from 0 to 1 |" << "Numerical integrator " << integrate(func2, 0,1) << "\n";
    std::cout << "Analytic: ∫dx √(1-x²) = π/4 from 0 to 1 |" << "Numerical integrator " << integrate(func3, 0,1) << "\n";
    std::cout << "Analytic: ∫dx ln(x)/√(x) = -4 from 0 to1 |" << "Numerical integrator " << integrate(func4, 0,1) << "\n";

    double acc_test = 1e-6;
    double eps_test = 1e-6;

    double r1 = integrate(func1,0,1,acc_test,eps_test);
    double r2 = integrate(func2,0,1,acc_test,eps_test);
    double r3 = integrate(func3,0,1,acc_test,eps_test);
    double r4 = integrate(func4,0,1,acc_test,eps_test);

    std::cout << "\n=== Accuracy check ===\n";

    std::cout << "sqrt(x): error = " << std::abs(r1 - 2.0/3.0) << "\n";

    std::cout << "1/sqrt(x): error = " << std::abs(r2 - 2.0) << "\n";

    std::cout << "sqrt(1-x^2): error = " << std::abs(r3 - M_PI/4.0) << "\n";

    std::cout << "log(x)/sqrt(x): error = " << std::abs(r4 + 4.0) << "\n\n";

    double known = 0.84270079294971486934;
    double calc = errorfunction(1.0);

    std::cout << "Known value erf(1) = " << known << "\n";
    std::cout << "Calculated value erf(1) = " << calc << "\n";
    std::cout << "Thus the error is = " << std::abs(known - calc) << "\n";

    std::ofstream erfplot("erf_curve.txt");

    for(double z=-3; z<=3; z+=0.1){
        erfplot << z << " " << errorfunction(z) << "\n";
    }

    std::ofstream out("erf_data.txt");

    for(int i = 1; i<= 10; i++){
        double acc = std::pow(10, -i);

        double val = errorfunction(1.0, acc, 0);
        double err = std::abs(val - known);

        out << acc << " " << err << "\n";
    } 
    
    out.close();
    std::cout << "Please check erf_curve.png for a plot of the error function. Also see erf_plot.png" << "\n";

    /*
    PART B: 
    */
    
    int ncalls = 0;

    auto lnf_sqrt = [&ncalls](double x){
        ncalls++;
        if(x < 1e-14) return 0.0;
        return std::log(x)/std::sqrt(x);
    };
    
    auto f_sqrt = [&ncalls](double x) {
        ncalls++;
        return 1/std::sqrt(x);
    };

    std::cout << "======== 1/sqrt(x)========" << "\n";

    ncalls = 0;
    double res1 = integrate(f_sqrt, 0, 1);
    std::cout << "\n Normal integrator: \n";
    std::cout << "Result: " << res1 << " calls: " << ncalls << "\n";

    ncalls = 0;
    double res2 = integrate_CC(f_sqrt, 0, 1);
    std::cout << "\n Clenshaw-Curtis: \n";
    std::cout << "Result: " << res2 << " calls: " << ncalls << "\n" << "\n";

    std::cout << "======== log(x)/sqrt(x)========" << "\n";
    ncalls = 0;
    double res3 = integrate(lnf_sqrt, 0, 1);
    std::cout << "\n Normal integrator: \n";
    std::cout << "Result: " << res3 << " calls: " << ncalls << "\n";

    ncalls = 0;
    double res4 = integrate_CC(lnf_sqrt, 0, 1);
    std::cout << "\n Clenshaw-Curtis: \n";
    std::cout << "Result: " << res4 << " calls: " << ncalls << "\n";

    //Test vs python
    std::cout << "A test vs scipy.quad has been run on the function f(x)=log(x)/sqrt(x), which yielded: " << "\n";
    std::cout << "Result: -4.000000000000085, Calls: 315" << "\n";
    std::cout << "Thus we can see, that for some cases, the CC integrator is best, for others the normal one is. However, the scipy.quad outperformed both, in calls and result." << "\n";

    std::cout << "\n" << "Test with infinite integrals rewritten: " << "\n";
    //Integrate infinity tests
    ncalls = 0;
    auto func1inf = [&ncalls](double x){
        ncalls++;
        return std::exp(-x*x);};
    std::cout << "∫dx e^(-x)^2 from -infinity to infinity = " << integrate_general(func1inf, -INFINITY, INFINITY) << " with calls: " << ncalls << "\n";

    ncalls = 0;
    auto func2inf = [&ncalls](double x){ 
        ncalls++;
        return std::exp(-x);};
    std::cout << "∫dx e^(-x) from 0 to infinity = " << integrate_general(func2inf, 0, INFINITY) << " with calls: " << ncalls << "\n";

    ncalls = 0;
    auto func3inf = [&ncalls](double x){  
        ncalls++;
        return std::exp(x);};
        std::cout << "∫dx e^(x) from -infinity to 0 = " << integrate_general(func3inf, -INFINITY, 0) << " with calls: " << ncalls << "\n";

    std::cout << "\n" <<  "===Comparison with sicpy integrate: " << "\n";
    std::cout << "exp(-x^2): Result: 1.7724538509055159 Calls: 270" << "\n";
    std::cout << "exp(-x):Result: 1.0000000000000002 Calls: 135" << "\n";
    std::cout << "exp(x): Result: 1.0000000000000002 Calls: 135" << "\n";
    std::cout << "Thus scipy integrate outperform the one implemented here." << "\n";

    //Part C. Made by ChatGPT
    std::cout << "\nPart C: Error estimate investigation\n";

auto test = [](std::function<double(double)> f,
               double exact,
               const char* name)
{
    auto res = integrate_error(f,0,1);

    double actual_error = std::abs(res.first-exact);

    std::cout << "\n" << name << "\n";
    std::cout << "Result          = " << res.first << "\n";
    std::cout << "Exact           = " << exact << "\n";
    std::cout << "Estimated error = " << res.second << "\n";
    std::cout << "Actual error    = " << actual_error << "\n";
    std::cout << "Ratio est/act   = "
              << res.second/actual_error << "\n";
};

test(
    [](double x){ return std::sqrt(x); },
    2.0/3.0,
    "Integral of sqrt(x)"
);

test(
    [](double x){ return 1/std::sqrt(x); },
    2.0,
    "Integral of 1/sqrt(x)"
);

test(
    [](double x){ return std::log(x)/std::sqrt(x); },
    -4.0,
    "Integral of log(x)/sqrt(x)"
);
    return 0;
}