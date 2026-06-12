#pragma once

#include <functional>
#include <cmath>

#include "matrix.h"
#include "qr.h"
#include "ode.h"

namespace pp {

inline matrix jacobian(
    std::function<vector(const vector&)> f,
    vector x,
    const vector& fx
){
    int n = x.size();

    matrix J(n,n);

    for(int j=0;j<n;j++){

        double dx =
            std::max(std::abs(x[j]),1.0)
            * std::pow(2.0,-26);

        x[j] += dx;

        vector df = f(x) - fx;

        for(int i=0;i<n;i++)
            J(i,j) = df[i]/dx;

        x[j] -= dx;
    }

    return J;
}

inline vector newton(
    std::function<vector(const vector&)> f,
    vector x,
    double acc = 1e-2,
    double alpha_min = 1e-3,
    int max_iter = 100
){
    vector fx = f(x);

    for(int iter=0; iter<max_iter; iter++){

        if(fx.norm() < acc)
            break;

        matrix J = jacobian(f,x,fx);

        qr QRJ(J);

        vector Dx = QRJ.solve(-fx);

        bool small_step = true;

    for(int i=0;i<x.size();i++){

        double dx =
            std::max(std::abs(x[i]),1.0)
            * std::pow(2.0,-26);

        if(std::abs(Dx[i]) > dx)
            small_step = false;
    }

if(small_step)
    break;

        double alpha = 1.0;

        vector z;
        vector fz;

        while(true){

            z = x + alpha*Dx;
            fz = f(z);

            if(fz.norm() < fx.norm())
                break;

            if(alpha < alpha_min)
                break;

            alpha /= 2.0;
        }

        x = z;
        fx = fz;
    }

    return x;
}

}