#pragma once
#include <tuple>
#include <functional>
#include "vec.h"

/*
AI use: AI has assisted with tasks such as debugging, helping to translate algorithms and pseudocode from lecture pdf notes into C++ syntax, and help design tests.
Since I made many of the homeworks before it was stated that we should mark the AI-generated code, this is not possible. In general, AI has been used as a tool in all project files.
*/

namespace pp{

    std::tuple<vector, vector> rkstep12(std::function<vector(double, vector)> f,double x,vector y,double h){
        //Slope in Euler (bad estimate)
        vector k0 = f(x,y);
        //Midpoint slope
        vector k1 = f(x + h/2.0, y + k0*(h/2.0));
        // improved solution using midpoint method
        vector yh = y + k1*h;
        //euler midpoint vs midpoint is estimate of error
        vector dy = (k1 - k0)*h;

        return std::make_tuple(yh,dy);
    }

    std::tuple<std::vector<double>, std::vector<vector>> driver(std::function<vector(double, vector)> f,double a,double b,vector y,double h = 0.125,double acc = 0.01,double eps = 0.01){
    double x = a;

    std::vector<double> xlist;
    std::vector<vector> ylist;

    xlist.push_back(x);
    ylist.push_back(y);

    while(true){

        //End of integrationinterval
        if(x >= b) break;

        if(x + h > b) h = b - x;

        auto [yh, dy] = rkstep12(f, x, y, h);

        double err = dy.norm();

        //Tolerance from theory
        double tol = (acc + eps * yh.norm()) * std::sqrt(h / (b - a));

        //Accept if error is less than tolerance
        if(err <= tol){
            x += h;
            y = yh;

            xlist.push_back(x);
            ylist.push_back(y);
        }

        //Adjust
        if(err > 0){
            double factor = std::pow(tol/err, 0.25) * 0.95;
            if(factor > 2) factor = 2;
            h *= factor;
        }
        else{
            h *= 2;
        }
    }

    return std::make_tuple(xlist, ylist);
}
}