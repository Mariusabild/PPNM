#include "svd.h"
#include "matrix.h"
#include <iostream>
#include <random>

int main(){

    //Generate a random sqaure matrix. Adapted from my main.cc from my homework "eigenvalues"
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0.0,1.0);

    int n=5;
    pp::matrix A(n,n);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            double x = dist(rng);
            A(i,j)=x;
        }
    }

    std::cout << "\nPerfoming tests... " << "\n";

    A.print("\nRandom symmetric test matrix A:\n");

    auto [U, D, V] = pp::jacobi_svd(A);

    pp::matrix UDVT = U*D*V.T();

    std::cout << "\nReconstructing A as UDV^T: " << "\n";
    UDVT.print();
    std::cout << "According to theory, this matrix product is equal to the original matrix A. Here we can see A is succesfully reconstructed." << "\n";

    std::cout << "\nThis can also be seen as UDV^T-A is equal to: \n";

    pp::matrix test = UDVT-A;
    test.print();
    std::cout << "\n All elements is approximately equal to zero." << "\n";

    std::cout << "\n D should be diagonal, and contain no negative elements:" << "\n";
    D.print();
    std::cout << "\nD apperas diagonal as expected, and contain no negative elements" << "\n";

    pp::matrix UTU = U.T()*U;
    pp::matrix VTV = V.T()*V;

    std::cout << "\nU and V should be orthogonal according to theory" << "\n";
    UTU.print("U^TU");
    VTV.print("V^TV");

    std::cout << "\nAs we can see, both products equal the identity matrix. The off diagonal elements is equal to zero upto machine epsilon." << "\n";


    return 0;
}