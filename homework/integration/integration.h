#pragma once
#include<cmath>
#include<functional>
#include<iostream>
#include<utility>

/*
AI use: AI has assisted with tasks such as debugging, helping to translate algorithms and pseudocode from lecture pdf notes into C++ syntax, and help design tests.
Since I made many of the homeworks before it was stated that we should mark the AI-generated code, this is not possible. In general, AI has been used as a tool in all project files.
*/

double integrate(std::function<double(double)> f, double a, double b, double acc = 1e-3, double eps = 1e-3, double f2 = NAN, double f3 = NAN){
    double h = b-a;

    if(std::isnan(f2)){
        f2 = f(a + 2*h/6);
        f3 = f(a + 4*h/6);
    }

    double f1 = f(a + h/6);
    double f4 = f(a + 5*h/6);

    //higher order
    double Q = (2*f1 + f2 + f3 + 2*f4) / 6 * h;

    //lower order
    double q = (f1 + f2 + f3 + f4) / 4 * h;

    double err = std::abs(Q - q); 
    double tol = acc + eps*std::abs(Q);

    if(err < tol){
        return Q;
    } else {
        double mid = (a+b)/2;

        double left = integrate(f, a, mid, acc/std::sqrt(2.0), eps, f1, f2);
        double right = integrate(f, mid, b, acc/std::sqrt(2.0), eps, f3, f4);

        return left + right;
    }
}

//For part C. Made by ChatGPT
std::pair<double,double> integrate_error( std::function<double(double)> f,double a,double b,double acc = 1e-3,double eps = 1e-3,double f2 = NAN,double f3 = NAN){
    double h = b-a;

    if(std::isnan(f2)){
        f2 = f(a + 2*h/6);
        f3 = f(a + 4*h/6);
    }

    double f1 = f(a + h/6);
    double f4 = f(a + 5*h/6);

    double Q = (2*f1 + f2 + f3 + 2*f4)/6*h;
    double q = (f1 + f2 + f3 + f4)/4*h;

    double err = std::abs(Q-q);
    double tol = acc + eps*std::abs(Q);

    if(err < tol){
        return {Q,err};
    }

    double mid = (a+b)/2;

    auto left =integrate_error(f,a,mid,acc/std::sqrt(2.0),eps,f1,f2);

    auto right =integrate_error(f,mid,b,acc/std::sqrt(2.0),eps,f3,f4);

    double result = left.first + right.first;

    double total_error =std::sqrt(left.second*left.second +right.second*right.second);

    return {result,total_error};
}

//CC-integrator
double integrate_CC(std::function<double(double)> f, double a, double b, double acc = 1e-6, double eps = 1e-6){
    auto g = [f, a, b](double theta){
        double x = (a+b)/2 + (b-a)/2 * std::cos(theta);
        double dx_theta = (b-a)/2 * std::sin(theta);
        return f(x) * dx_theta;
    };
    return integrate(g, 0, M_PI, acc, eps);
}

//Infinite integrals

double integrate_general(std::function<double(double)> f, double a, double b, double acc = 1e-6, double eps = 1e-6){

    if(!std::isinf(a) && !std::isinf(b)){
        return integrate_CC(f, a, b, acc ,eps);
    }

    else if(std::isinf(a) && std::isinf(b)){

        auto g = [f, a, b](double t) {
            double x = t/(1-std::pow(t, 2));
            double dx = (1+std::pow(t, 2))/std::pow((1-std::pow(t, 2)),2);
            return f(x)*dx;
        };
        return integrate_CC(g, -1, 1, acc, eps);
    }

    else if(!std::isinf(a) && std::isinf(b)){

        auto g = [f, a, b](double t) {
            double x = a+t/(1-t);
            double dx = 1/std::pow((1-t),2);
            return f(x)*dx;
        };
        return integrate_CC(g, 0, 1, acc, eps);
    }

    else if(std::isinf(a) && !std::isinf(b)){

        auto g = [f, a, b](double t) {
            double x = b+t/(1+t);
            double dx = 1/std::pow((1+t),2);
            return f(x)*dx;
        };
        return integrate_CC(g, -1, 0, acc, eps);
    }
    return 0;
}

