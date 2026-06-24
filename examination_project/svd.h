#pragma once
#include "matrix.h"

namespace pp{

    //From homework "eigenvalues" 
    void timesJ(matrix& A, int p, int q, double theta){
        double c = std::cos(theta), s = std::sin(theta);
        for(int i = 0; i < A.size1(); i++) {
            double aip = A(i,p), aiq = A(i,q);
            A(i,p) = c*aip - s*aiq;
            A(i,q) = s*aip + c*aiq;
        }
    }

    //Adapted from a old homework. ChatGPT has been used to help implement some parts of the new theory
    std::tuple<matrix,matrix, matrix> jacobi_svd(matrix A){

        double epsilon = 1e-12;

        int n = A.size1();
        matrix V(n,n); 
        V.setid();

        matrix U(n,n);
        matrix D(n,n);

        bool changed;

        do{
            changed = false;
            for(int p=0; p<n-1; p++){
                for(int q = p+1; q < n; q++){
                    
                    double apq = 0;
                    double app = 0;
                    double aqq = 0;

                    for(int i = 0; i < n; i++){
                        apq += A(i,p)*A(i,q);
                        app += A(i,p)*A(i,p);
                        aqq += A(i,q)*A(i,q);
                    }
                
                    if(fabs(apq) < epsilon) 
                        continue;

                    changed = true;

                        //From "eigen.pdf"
                        double theta = 0.5*std::atan2(2*apq, aqq-app);

                    timesJ(A,p,q,theta);   
                    timesJ(V,p,q,theta);
                }
            }

        }while(changed);

        for(int j = 0; j < n; j++){
            double sigma = 0; 
                for(int i = 0; i < n; i++) {
                    sigma += A(i,j)*A(i,j);
                }
            sigma = std::sqrt(sigma);    
            D(j,j) = sigma;
            
            if(sigma > epsilon){
                for(int i = 0; i < n; i++){
                U(i,j) = A(i,j)/sigma;
                }
            }
        
        }

    return std::make_tuple(U, D, V);
    }
}