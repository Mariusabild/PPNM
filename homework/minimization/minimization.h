#pragma once

#include <functional>
#include <cmath>
#include <iostream>

#include "matrix.h"
#include "qr.h"

namespace pp {

inline vector gradient(
    std::function<double(const vector&)> phi,
    vector x
){
    double phix = phi(x);

    vector g(x.size());

    for(int i=0;i<x.size();i++){

        double dxi =
            (1.0 + std::abs(x[i]))
            * std::pow(2.0,-26);

        x[i] += dxi;

        g[i] = (phi(x)-phix)/dxi;

        x[i] -= dxi;
    }

    return g;
}

inline matrix hessian(
    std::function<double(const vector&)> phi,
    vector x
){
    int n = x.size();

    matrix H(n,n);

    vector gx = gradient(phi,x);

    for(int j=0;j<n;j++){

        double dxj =
            (1.0 + std::abs(x[j]))
            * std::pow(2.0,-13);

        x[j] += dxj;

        vector dg =
            gradient(phi,x)-gx;

        for(int i=0;i<n;i++)
            H(i,j)=dg[i]/dxj;

        x[j]-=dxj;
    }

    return H;
}

inline vector newton_min(
    std::function<double(const vector&)> phi,
    vector x,
    double acc=1e-3,
    int max_steps=1000
){
    for(int step=0; step<max_steps; step++){

        vector g = gradient(phi,x);

        if(g.norm() < acc){
    std::cout
        << "Steps = "
        << step
        << "\n";
    break;
}

        matrix H = hessian(phi,x);

        for(int i=0;i<x.size();i++)
            H(i,i)+=1e-6;

        qr QRH(H);

        vector dx = QRH.solve(-g);

        double lambda = 1.0;

        while(lambda >= 1.0/1024){

            if(phi(x+lambda*dx) < phi(x))
                break;

            lambda /= 2.0;
        }

        x += lambda*dx;
    }

    return x;
}

//part B
double breit_wigner(
    double E,
    double m,
    double Gamma,
    double A
){
    return
        A/
        (
            (E-m)*(E-m)
            +Gamma*Gamma/4.0
        );
}

}