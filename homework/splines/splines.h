#pragma once
#include <cassert>
#include <vector>
#include <functional>

/*
AI use: AI has assisted with tasks such as debugging, helping to translate algorithms and pseudocode from lecture pdf notes into C++ syntax, and help design tests.
Since I made many of the homeworks before it was stated that we should mark the AI-generated code, this is not possible. In general, AI has been used as a tool in all project files.
*/

int binsearch(const std::vector<double>& x, double z){
    assert(z >= x[0] && z <= x[x.size()-1]); //Tjekker z faktisk ligger i intervallet, returnerer fejl hvis ikke
    
    //Start og slutpunkt i interval
    int i = 0;
    int j = x.size() - 1;

    while(j - i > 1){
        int mid = (i+j)/2;
        if(z > x[mid]) i = mid;
        else j = mid;
    }
    return i;
}

double linterp(std::vector<double> x, std::vector<double> y, double z){
    int i = binsearch(x,z);

    double dx = x[i+1] - x[i];
    assert(dx > 0);

    double dy = y[i+1] - y[i];

    return y[i] + dy/dx * (z - x[i]);
}


double linterpInteg(std::vector<double> x, std::vector<double> y, double z){
    assert(z >= x[0] && z <= x[x.size()-1]);

    double sum = 0;
    int i = binsearch(x, z);

    for(int k = 0; k < i; k++){
        double dx = x[k+1] - x[k];
        double dy = y[k+1] - y[k];
        double p = dy/dx;

        sum += y[k]*dx + 0.5*p*dx*dx;
    }

    double dx = z - x[i];
    double dy = y[i+1] - y[i];
    double p = dy/(x[i+1] - x[i]);

    sum += y[i]*dx + 0.5*p*dx*dx;
    
    return sum;
}

std::function<double(double)> make_qspline(std::vector<double> x, std::vector<double> y){

    int n = x.size();
    std::vector<double> b(n-1), c(n-1);
    std::vector<double> h(n-1), p(n-1);

    for(int i=0;i<n-1;i++){
        h[i] = x[i+1] - x[i];
        p[i] = (y[i+1] - y[i]) / h[i];
    }

    c[0] = 0;
    for(int i=0;i<n-2;i++){
        c[i+1] = (p[i+1] - p[i] - c[i]*h[i]) / h[i+1];
    }

    c[n-2] /= 2;
    for(int i=n-3;i>=0;i--){
        c[i] = (p[i+1] - p[i] - c[i+1]*h[i+1]) / h[i];
    }

    for(int i=0;i<n-1;i++){
        b[i] = p[i] - c[i]*h[i];
    }

    return [x = std::move(x), y = std::move(y), 
            b = std::move(b), c = std::move(c)]
           (double z){

        int i = 0, j = x.size()-1;

        while(j-i>1){
            int m = (i+j)/2;
            if(z > x[m]) i = m;
            else j = m;
        }

        double dx = z - x[i];
        return y[i] + b[i]*dx + c[i]*dx*dx;
    };
}

struct qspline {
    int n;
    std::vector<double> x, y, b, c;
    
    qspline(const std::vector<double>& x, const std::vector<double>& y);

    double eval(double z);
    double deriv(double z);
    double integ(double z);
};

qspline::qspline(const std::vector<double>& x_, const std::vector<double>& y_){
    x = x_;
    y = y_;
    n = x.size();

    b.resize(n-1);
    c.resize(n-1);

    std::vector<double> h(n-1), p(n-1);

    for(int i=0;i<n-1;i++){
        h[i] = x[i+1] - x[i];
        assert(h[i] > 0);
        p[i] = (y[i+1] - y[i]) / h[i]; // FIXED
    }

    // forward
    c[0] = 0;
    for(int i=0;i<n-2;i++){
        c[i+1] = (p[i+1] - p[i] - c[i]*h[i]) / h[i+1];
    }

    // backward
    c[n-2] /= 2;
    for(int i=n-3;i>=0;i--){
        c[i] = (p[i+1] - p[i] - c[i+1]*h[i+1]) / h[i];
    }

    // b
    for(int i=0;i<n-1;i++){
        b[i] = p[i] - c[i]*h[i];
    }
}

double qspline::eval(double z){
    int i = binsearch(x,z);
    double dx = z - x[i];
    return y[i] + b[i]*dx + c[i]*dx*dx;
}

double qspline::deriv(double z){
    int i = binsearch(x,z);
    double dx = z - x[i];
    return b[i] + 2*c[i]*dx;
}

double qspline::integ(double z){
    int i = binsearch(x,z);
    double sum = 0;

    for(int k=0;k<i;k++){
        double dx = x[k+1] - x[k];
        sum += y[k]*dx + b[k]*dx*dx/2 + c[k]*dx*dx*dx/3;
    }

    double dx = z - x[i];
    sum += y[i]*dx + b[i]*dx*dx/2 + c[i]*dx*dx*dx/3;

    return sum;
}
