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
    std::cout << "Testing QR-decomp" << "\n";

    std::cout << "Generate a random test matrix (n should be greater than m, here n = 6, m = 3): " << "\n";
    A.print("\n The generated test matrix: ");

    //print qr-decomponerede matrice
    pp::qr decomp(A);
    decomp.R.print("\n R matrix: ");
    //Check QQ^T = 1
    std::cout << "R should be upper triangular. Inspect R." << "\n";

    pp::matrix B = decomp.Q.T()*decomp.Q;
    B.print("\n Q^T*Q: ");
    std::cout << "Should be equal to the identity matrix. The off-diagonal terms upto machine precision 0. Inspect this." << "\n";

    //check QR = A
    pp::matrix C = decomp.Q * decomp.R;
    C.print("\n Check that Q*R = A: ");

    std::cout << "The reconstructed matrix should match the original matrix A. Inspect the result." << "\n";

    /* TEST FOR SOLVE */

    std::cout << "Test for solve" << "\n";
    int k = 3;
    pp::matrix D(k,k);

    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            D(i,j) = dist(rng);
        }
    }

    D.print("\n Random generated matrix D, which needs to be a sqaure matrix:");

    pp::vector v(k);
    for(int i=0;i<k;i++){
        v[i] = dist(rng);
    }

    v.print("\n Random generated vector b:");

    pp::qr decomp2(D);

    pp::vector x = decomp2.solve(v);

    x.print("\n Solution x, to Dx = b:");

    (D*x).print("\n Check Dx:");

    v.print("\n Original b:");

    std::cout << "Dx should match the original vector b. Inspect the result." << "\n";


    /* Test determinant
    */

    std::cout << "\nDeterminant of D: " << decomp2.det() << "\n";
    std::cout
<< "The determinant is calculated as the product of the diagonal elements of R.\n";

    /* Test inverse
    */
    std::cout << "Testing inverse" << "\n";

    pp::matrix invD = decomp2.inverse();
    (D * invD).print("\nD*D^{-1}:");
    std::cout << "The result should equal the identity matrix up to machine precision. Inspect the result." << "\n";

    std::cout << "For part C, check 'timing.png'. The fit is performed to a function proportional tio N^3. This is to ensure that execution time of QR-decomp of a N times N matrix is O(N^3). Please insepct " << "\n";
}