#include <iostream>
#include <fstream>
#include <cmath>

#include "ann.h"

using namespace pp;

double g(double x){
    return
        std::cos(5*x-1)
        *std::exp(-x*x);
}

int main(){

    int N = 30;

    vector xs(N);
    vector ys(N);

    for(int i=0;i<N;i++){

        double x =
            -1.0
            +2.0*i/(N-1.0);

        xs[i]=x;
        ys[i]=g(x);
    }

    ann network(12);

    std::cout
        << "Training...\n";

    network.train(xs,ys);

    std::cout
    << "F(0)   = "
    << network.response(0)
    << "\n";

std::cout
    << "F'(0)  = "
    << network.derivative(0)
    << "\n";

std::cout
    << "F''(0) = "
    << network.second_derivative(0)
    << "\n";

std::cout
    << "A(0)   = "
    << network.antiderivative(0)
    << "\n";

    std::cout
        << " Interpolation done\n";

    std::ofstream datafile("data.txt");

    for(int i=0;i<N;i++){
        datafile
            << xs[i]
            << " "
            << ys[i]
            << "\n";
    }

    std::ofstream fitfile("fit.txt");

    std::ofstream dfile("derivative.txt");
std::ofstream ddfile("second_derivative.txt");
std::ofstream afile("antiderivative.txt");

for(double x=-1;x<=1;x+=0.005){

    dfile
        << x
        << " "
        << network.derivative(x)
        << "\n";

    ddfile
        << x
        << " "
        << network.second_derivative(x)
        << "\n";

    afile
        << x
        << " "
        << network.antiderivative(x)
        << "\n";
}

    for(double x=-1;x<=1;x+=0.005){

        fitfile
            << x
            << " "
            << network.response(x)
            << "\n";
    }

    //Part C

    ann ode(12);

ode.train_ode(

    [](double ypp,
       double yp,
       double y,
       double x)
    {
        return ypp+y;
    },

    -1,
    1,

    0,
    0,
    1
);

std::ofstream odefile("ode_fit.txt");
std::ofstream exactfile("ode_exact.txt");

for(double x=-1;x<=1;x+=0.005){

    odefile
        << x
        << " "
        << ode.response(x)
        << "\n";

    exactfile
        << x
        << " "
        << std::sin(x)
        << "\n";
}

    return 0;
}