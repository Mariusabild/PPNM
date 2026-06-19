#include "qr.h"
#include "matrix.h"
#include "lsfit.h"

#include <cmath>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>

/*
AI use: AI has assisted with tasks such as debugging, helping to translate algorithms and pseudocode from lecture pdf notes into C++ syntax, and help design tests.
Since I made many of the homeworks before it was stated that we should mark the AI-generated code, this is not possible. In general, AI has been used as a tool in all project files.
*/


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

    std::cout << "Please see decay_uncertainties.png, which shows a fit matching nicely with the data points, plus/minus the uncertanties, for part A/C." << "\n\n";

    //Print aprameters
    std::cout << "The fitted parameters are: " << "\n";
    std::cout << "a = " << a << "\n";
    std::cout << "lambda = " << lambda << "\n";
    std::cout << "Half life = " << T_half << " days\n" << "±" << dT << "\n\n";

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
    //Part C
    std::ofstream fit_plus("fit_plus.txt");
    std::ofstream fit_minus("fit_minus.txt");

    double a_plus     = exp(c[0] + dc0);
    double lambda_plus  = -(c[1] + dc1);

    double a_minus    = exp(c[0] - dc0);
    double lambda_minus = -(c[1] - dc1);

    for(double tt=0; tt<=16; tt+=0.1){

        fit_plus << tt << " " << a_plus*exp(-lambda_plus*tt) << "\n";

        fit_minus << tt << " " << a_minus*exp(-lambda_minus*tt) << "\n";
}

    //Modern value
    double modern = 3.66;

    //Calculate difference
    double diff = T_half - modern;
    double rel_error = diff / modern;

    //Print difference
    std::cout << "Modern value = " << modern << " days\n";
    std::cout << "Difference = " << diff << " days\n";
    std::cout << "Relative error = " << rel_error*100 << " %\n\n";
    cov.print("Covariance matrix:");

    std::cout << "\nParameter uncertainties:\n";
    std::cout << "d(ln(a)) = " << dc0 << "\n";
    std::cout << "d(lambda) = " << dc1 << "\n";

    double sigma = diff/dT;

    std::cout << "The discrepancy is " << diff << " days, corresponding to about " << sigma << " sigma.\n" << "This is more than 1 sigma, so no, it does not agree with the modern day value." << "\n";
    return 0;
}