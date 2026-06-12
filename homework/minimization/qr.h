#pragma once
#include <cmath>
#include "matrix.h"

namespace pp {

struct qr {

    matrix Q;
    matrix R;
        
    qr(const matrix& A); //Constructor
    vector solve(const vector& b) const; 
    double det() const;
    matrix inverse() const;

};

inline double dot(const vector& a, const vector& b) {
    double dotproduct = 0;
    for(int i = 0; i < a.size(); i++) {
        dotproduct += a[i] * b[i];
    }
    return dotproduct;
}

inline qr::qr(const matrix& A) {

    Q = A;

    int m = A.size2();

    R = matrix(m,m);

    for(int i=0;i<m;i++){
        R(i,i)=Q[i].norm();
        Q[i]/=R(i,i);
        for(int j=i+1;j<m;j++){
            R(i,j)=dot(Q[i],Q[j]);
            Q[j]-=Q[i]*R(i,j);
        }
    }
}

inline vector qr::solve(const vector& b) const {

    int m = R.size1();

    vector x(m);
    vector c = Q.T() * b;

    for(int i=m-1;i>=0;i--){
        double sum=0;

        for(int k=i+1;k<m;k++)
            sum += R(i,k)*x[k];

        x[i] = (c[i]-sum)/R(i,i);
    }

    return x;
}

inline double qr::det() const {
    double determinant = 1;

    int m = R.size1();

    for(int i = 0; i < m; i++){
        determinant *= R(i,i);
    }
    return determinant;

}
inline matrix qr::inverse() const {
    int n = R.size1();

    matrix inv(n,n);

    
    for(int i = 0; i < n; i++) {
        vector e(n);
        e[i] = 1;

        vector x = solve(e);

        inv[i] = x;
    }
    return inv;

}

}