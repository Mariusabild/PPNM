#include "svd.h"
#include "matrix.h"
#include <iostream>
#include <random>

//main.cc is written by myself, using adapted parts from old homeworks
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

    std::cout << "\n================================================================================" << "\n";
    std::cout << "\nPerfoming verification tests " << "\n";

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

    //
    std::cout << "\n================================================================================" << "\n";
    std::cout << "Solving a homogeneous linear system using SVD" << "\n";

    pp::matrix B(3,3);

    B(0,0) = 1;
    B(1,0) = 2;
    B(2,0) = 3;

    B(0,1) = 2*B(0,0);
    B(1,1) = 2*B(1,0);
    B(2,1) = 2*B(2,0);

    B(0,2) = 3*B(0,0);
    B(1,2) = 3*B(1,0);
    B(2,2) = 3*B(2,0);

    auto[U2, D2, V2] = pp::jacobi_svd(B);

    int index_lowest = 0;
    double value_lowest = D(index_lowest,index_lowest);

    for(int i = 0; i < D2.size1(); i++){
        double value = D2(i,i);

        if(value < value_lowest){
            index_lowest = i;
            value_lowest = value;
        }
    }

    pp::vector x(B.size1());

    for(int i = 0; i < D.size1(); i++){
        x[i] = V2(i, index_lowest);
    }

    pp::vector b = B*x;

    B.print("\nMatrix B with rank 1, since collumn 2 and 3 linear dependent of collumn 1, set to 2*col1 and 3*col1 respectively");

    D2.print("\nMatrix D obtained when performing SVD on B");

    std::cout << "\nSmallest identified singular value: " << value_lowest << "\n";

    x.print("\nCandidate vector x in nullspace solving Bx = 0: \n");

    b.print("\nB*x: ");

    std::cout << "\nThus x belongs to the nullspace of B." << "\n";

    return 0;
}