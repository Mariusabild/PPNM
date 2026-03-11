#pragma once
#include "matrix.h"
#include <cmath>
#include <tuple>

namespace pp {

void timesJ(matrix& A, int p, int q, double theta){
    double c = std::cos(theta), s = std::sin(theta);
    for(int i = 0; i < A.size1(); i++) {
        double aip = A(i,p), aiq = A(i,q);
        A(i,p) = c*aip - s*aiq;
        A(i,q) = s*aip + c*aiq;
    }
}

void Jtimes(matrix& A, int p, int q, double theta){
    double c = std::cos(theta), s = std::sin(theta);
    for(int j = 0; j < A.size2(); j++) {
        double apj = A(p,j), aqj = A(q,j);
        A(p,j) = c*apj + s*aqj;
        A(q,j) = -s*apj + c*aqj;
    }
}

std::tuple<vector,matrix> jacobi(matrix A){

    int n = A.size1();
    matrix V(n,n); 
    V.setid();
    vector w(n);

    bool changed;

    do{
        changed = false;

        for(int p = 0; p < n-1; p++){
            for(int q = p+1; q < n; q++){
                

                double apq = A(p,q);
                double app = A(p,p);
                double aqq = A(q,q);
                
                if(fabs(apq) < 1e-12) continue;

                double theta = 0.5*std::atan2(2*apq, aqq-app);

                double c = std::cos(theta);
                double s = std::sin(theta);

                double new_apq = (c*c - s*s)*apq + c*s*(app - aqq);

                if(std::abs(new_apq) < std::abs(apq)){
                    changed = true;

                    timesJ(A,p,q,theta);   // A ← A*J
                    Jtimes(A,p,q,-theta);  // A ← Jᵀ*A
                    timesJ(V,p,q,theta);   // V ← V*J
                }
            }
        }

    }while(changed);

    for(int i=0;i<n;i++)
        w[i] = A(i,i);

    return std::make_tuple(w,V);
}

}