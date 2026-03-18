#include "qr.h"
#include "matrix.h"
#include "lsfit.h"

#include <cmath>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>

int main() {

    //Data
    pp::vector t = {1, 2, 3, 4, 6, 9, 10, 13, 15};
    pp::vector y = {117,100,88,72,53,29.5,25.2,15.2,11.1};
    pp::vector dy = {6,5,4,4,4,3,3,2,2};

    //Calculate log of data
    pp::vector logy = y.map([](double v){
        return log(v);
    });

    pp::vector logdy(y.size());
    for(int i=0;i<y.size();i++){
        logdy[i] = dy[i]/y[i];
    }

    auto fs = std::vector<std::function<double(double)>>{
        [](double t){ return 1.0; },
        [](double t){ return t; }
    };

    //Get coefficients and covariance matrix
    auto [c, cov] = pp::lsfit(fs,t,logy,logdy);

    //Parameters from fit
    double a = exp(c[0]);
    double lambda = -c[1];
    double T_half = log(2)/lambda;

    //Uncertainites from fit
    double dc0 = sqrt(cov(0,0));
    double dc1 = sqrt(cov(1,1));
    double dlambda = dc1;
    double dT = log(2)/(lambda*lambda) * dlambda;

    //Print aprameters
    std::cout << "a = " << a << "\n";
    std::cout << "lambda = " << lambda << "\n";
    std::cout << "Half life = " << T_half << " days\n" << "±" << dT << "\n";

    //Write to .txt files for plotting
    std::ofstream data("data.txt");
    std::ofstream fit("fit.txt");

    for(int i = 0; i< t.size(); i++) {
        data << t[i] << " " << y[i] << " " << dy[i] << "\n";
    }

    for(double tt=0; tt<=16; tt+=0.1){
        double yy = a*exp(-lambda*tt);
        fit << tt << " " << yy << "\n";
    }

    //Modern value
    double modern = 3.66;

    //Calculate difference
    double diff = T_half - modern;
    double rel_error = diff / modern;

    //Print difference
    std::cout << "Modern value = " << modern << " days\n";
    std::cout << "Difference = " << diff << " days\n";
    std::cout << "Relative error = " << rel_error*100 << " %\n";
    cov.print("Covariance matrix:");

    return 0;
}