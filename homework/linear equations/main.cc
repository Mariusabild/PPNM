#include "matrix.h"
#include "qr.h"
#include <iostream>
#include <random>

/*
AI use: AI has assisted with tasks such as debugging, helping to translate algorithms and pseudocode from lecture pdf notes into C++ syntax, and help design tests.

Since I made many of the homeworks before it was stated that we should mark the AI-generated code, this is not possible. In general, AI has been used as a tool in all project files.
*/

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

    //print testmatrix
    std::cout << "\n\n" << "Out.txt, testing implimentation..." << "\n\n";
    std::cout << "Testing QR-decomp:" << "\n";

    std::cout << "Generate a random test matrix A (n should be greater than m, here n = 6, m = 3): " << "\n";
    A.print("\n The generated test matrix A: ");

    pp::qr decomp(A);
    decomp.R.print("\n R matrix: ");
    //Check QQ^T = 1
    std::cout << "\nR should be upper triangular. This seems to be the case after multiple runs, since all elements under the diagonal is zero. Please inspect R as well." << "\n";

    pp::matrix B = decomp.Q.T()*decomp.Q;
    B.print("\n Q^T*Q: ");
    std::cout << "\nQ^T*Q Should be equal to the identity matrix, which it seems to be after multiple runs. Please inspect this as well. The off diagonal terms is zero, seen as machine epsilon." << "\n";

    //check QR = A
    pp::matrix C = decomp.Q * decomp.R;
    C.print("\n Check that Q*R = A: ");

    std::cout << "\nThe reconstructed matrix should match the original matrix A. Looking at the first print of A, this seems to be the case. Inspect the result as well." << "\n";

    /* TEST FOR SOLVE */

    std::cout << "\nTest for solve:" << "\n";
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

    std::cout << "\nDx should match the original vector b. Inspect the result." << "\n";

    // Test determinant

    std::cout << "\nDeterminant of D: " << decomp2.det() << "\n";
    std::cout << "\nThe determinant is calculated as the product of the diagonal elements of R.\n";

    //Test inverse
    std::cout << "\nTesting inverse" << "\n";

    pp::matrix invD = decomp2.inverse();
    (D * invD).print("\nD*D^{-1}:");
    std::cout << "The result should equal the identity matrix up to machine precision, which it seems to be. Please inspect the result." << "\n";

    std::cout << "For part C, check 'timing.png'. The fit is performed to a function proportional tio N^3. This is to ensure that execution time of QR-decomp of a N times N matrix is O(N^3). The fit nicely matches the points. Please insepct " << "\n";
    return 0;
}