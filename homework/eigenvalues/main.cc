#include<iostream>
#include<fstream>
#include"matrix.h"
#include"jacobi.h"
#include<random>
#include<cstring>
#include<cmath>

int main(int argc, char** argv){

    double rmax = 10;
    double dr = 0.3;

    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-rmax") == 0) rmax = atof(argv[++i]);
        if(strcmp(argv[i], "-dr") == 0) dr = atof(argv[++i]);
    }

    int npoints = (int)(rmax/dr)-1;

    pp::vector r(npoints);
    for(int i = 0;i<npoints;i++)
        r[i] = dr*(i+1);

    pp::matrix H(npoints, npoints);

    // kinetic term
    for(int i=0;i<npoints-1;i++){
        H(i,i)  = -2*(-0.5/dr/dr);
        H(i,i+1)=  1*(-0.5/dr/dr);
        H(i+1,i)=  1*(-0.5/dr/dr);
    }

    H(npoints-1,npoints-1)=-2*(-0.5/dr/dr);

    // potential
    for(int i=0;i<npoints;i++)
        H(i,i)+=-1/r[i];

    // diagonalize hydrogen Hamiltonian
    auto [e,Vhyd] = pp::jacobi(H);

    std::cout<<"Lowest hydrogen eigenvalues:\n";
    for(int i=0;i<5;i++)
        std::cout<<e[i]<<"\n";

    // -------- write wavefunctions to file --------
    std::ofstream wave("wave.dat");
    wave << "# r f0 f1 f2\n";

    for(int i=0;i<npoints;i++){
        wave << r[i] << " "
             << Vhyd(i,0)/sqrt(dr) << " "
             << Vhyd(i,1)/sqrt(dr) << " "
             << Vhyd(i,2)/sqrt(dr) << "\n";
    }

    wave.close();

    // --------------------------------------------------
    // Jacobi test
    // --------------------------------------------------

    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0.0,1.0);

    int n = 4;

    pp::matrix A(n,n);

    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            double x = dist(rng);
            A(i,j) = x;
            A(j,i) = x;
        }
    }

    A.print("\nTest matrix:");

    auto [w,V] = pp::jacobi(A);

    V.print("\nEigenvectors:");

    std::cout<<"\nEigenvalues:\n";
    for(int i=0;i<w.size();i++)
        std::cout<<w[i]<<"\n";

    pp::matrix D(n,n);
    for(int i=0;i<n;i++)
        D(i,i) = w[i];

    pp::matrix VT = V.T();

    pp::matrix VTAV = VT*A*V;
    pp::matrix VDVT = V*D*VT;
    pp::matrix VTV  = VT*V;
    pp::matrix VVT  = V*VT;

    VTAV.print("\nVTAV (should be diagonal):");
    D.print("\nD (eigenvalues on diagonal):");

    VDVT.print("\nVDVT (should equal original A):");
    A.print("\nOriginal A:");

    VTV.print("\nVTV (should be identity):");
    VVT.print("\nVVT (should be identity):");

    return 0;
}