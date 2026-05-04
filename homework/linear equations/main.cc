#include "matrix.h"
#include "qr.h"
#include <iostream>
#include <random>

int main() {

    std::mt19937 rng(42); // random generator
    std::uniform_real_distribution<double> dist(0.0,1.0);

    int n = 6;
    int m = 3;

    pp::matrix A(n,m);

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            A(i,j) = dist(rng);
        }
    }

    //print testmatrice
    std::cout << "Generatin a test matrix: " << "\n";
    A.print("\n Test matrix: ");

    //print qr-decomponerede matrice
    pp::qr decomp(A);
    decomp.R.print("\n R matrix: ");
    //Check QQ^T = 1

    pp::matrix B = decomp.Q.T()*decomp.Q;
    B.print("\n Q*Q^T: ");

    //check QR = A
    pp::matrix C = decomp.Q * decomp.R;
    C.print("\n Check that Q*R = A: ");

    /* TEST FOR SOLVE */

    int k = 3;
    pp::matrix D(k,k);

    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            D(i,j) = dist(rng);
        }
    }

    D.print("\n Random matrix D:");

    pp::vector v(k);
    for(int i=0;i<k;i++){
        v[i] = dist(rng);
    }

    v.print("\n Vector b:");

    pp::qr decomp2(D);

    pp::vector x = decomp2.solve(v);

    x.print("\n Solution x:");

    (D*x).print("\n Check Dx:");

    v.print("\n Original b:");


    /* Test determinant
    */

    std::cout << "\nDeterminant: " << decomp.det() << "\n";

    /* Test inverse
    */

    pp::matrix invD = decomp2.inverse();
    (D * invD).print("\nD*D^{-1}:");
    }