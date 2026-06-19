#pragma once

#include <functional>
#include <cmath>
#include <iostream>

#include "matrix.h"
#include "minimization.h"

/*
AI use: AI has assisted with tasks such as debugging, helping to translate algorithms and pseudocode from lecture pdf notes into C++ syntax, and help design tests.
Since I made many of the homeworks before it was stated that we should mark the AI-generated code, this is not possible. In general, AI has been used as a tool in all project files.
In this particular project, AI has been used in all project parts, so everything is marked as such.
*/

namespace pp {

struct ann {

    int n;
    std::function<double(double)> f;
    vector p;

    ann(int n_);

    double response(double x) const;
    double derivative(double x) const;

    double second_derivative(double x) const;

    double antiderivative(double x) const;

    double cost(const vector& xs,const vector& ys) const;

    void train(const vector& xs,const vector& ys);
    //Part C
    void train_ode(
    std::function<double(double,double,double,double)> phi,double a,double b,double c,double yc,double ypc,double alpha = 10,double beta = 10);
};

inline ann::ann(int n_)
    : n(n_),
      f([](double x){
            return x*std::exp(-x*x);
        }),
      p(3*n_)
{
    for(int i=0;i<n;i++){

        p[3*i+0] = -1.0 + 2.0*i/(n-1.0);

        p[3*i+1] = 0.5;

        p[3*i+2] = 1.0;
    }
}

inline double ann::response(double x) const {

    double sum = 0;

    for(int i=0;i<n;i++){

        double a = p[3*i+0];

        double b = std::abs(p[3*i+1]) + 1e-3;

        double w = p[3*i+2];

        sum += w * f((x-a)/b);
    }

    return sum;
}

inline double ann::derivative(double x) const {

    double sum = 0;

    for(int i=0;i<n;i++){

        double a = p[3*i+0];

        double b = std::abs(p[3*i+1]) + 1e-3;

        double w = p[3*i+2];

        double z = (x-a)/b;

        double fp = std::exp(-z*z)*(1-2*z*z);

        sum += w*fp/b;
    }

    return sum;
}

inline double ann::second_derivative(
    double x
) const {

    double sum = 0;

    for(int i=0;i<n;i++){

        double a = p[3*i+0];

        double b = std::abs(p[3*i+1]) + 1e-3;

        double w = p[3*i+2];

        double z = (x-a)/b;

        double fpp = std::exp(-z*z)*(4*z*z*z - 6*z);

        sum += w*fpp/(b*b);
    }

    return sum;
}

inline double ann::antiderivative(
    double x
) const {

    double sum = 0;

    for(int i=0;i<n;i++){

        double a = p[3*i+0];

        double b = std::abs(p[3*i+1]) + 1e-3;

        double w = p[3*i+2];

        double z = (x-a)/b;

        sum +=-0.5*w*b*std::exp(-z*z);
    }

    return sum;
}

inline double ann::cost(const vector& xs,const vector& ys) const {

    double sum = 0;

    for(int k=0;k<xs.size();k++){

        double diff =response(xs[k])- ys[k];

        sum += diff*diff;
    }

    return sum;
}

inline void ann::train(const vector& xs,const vector& ys){

    auto objective =[&](const vector& params){p = params;return cost(xs,ys);};

    std::cout<< "Initial cost = " << cost(xs,ys) << "\n";

    p = newton_min(objective,p,1e-5,5000);

    std::cout<< "Final cost = "<< cost(xs,ys)<< "\n";
}

inline void ann::train_ode(

    std::function<double(double,double,double,double)> phi,double a, double b,double c,double yc,double ypc,double alpha,double beta){

    auto objective =
    [&](const vector& params){

        p = params;

        double sum = 0;

        int Nint = 100;

        double dx =(b-a)/(Nint-1);

        for(int i=0;i<Nint;i++){

            double x =a+i*dx;

            double residual =phi(second_derivative(x),derivative(x),response(x),x);

            sum +=residual*residual*dx;
        }

        sum +=alpha*std::pow(response(c)-yc,2);

        sum +=beta*std::pow(derivative(c)-ypc,2);

        return sum;
    };

    std::cout<< "Initial ODE cost = "<< objective(p)<< "\n";

    p =newton_min(objective,p,1e-5,5000);

        std::cout<< "Final ODE cost = "<< objective(p)<< "\n";
}

} // namespace pp