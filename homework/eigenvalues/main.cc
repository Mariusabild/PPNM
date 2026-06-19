#include<iostream>
#include<fstream>
#include"matrix.h"
#include"jacobi.h"
#include<cstring>
#include<cmath>
#include<random>

int main(int argc, char** argv){

    double rmax = 10;
    double dr = 0.05;

    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-rmax")==0) rmax = atof(argv[++i]);
        if(strcmp(argv[i],"-dr")==0) dr = atof(argv[++i]);
    }

    int npoints = (int)(rmax/dr)-1;

    pp::vector r(npoints);
    for(int i=0;i<npoints;i++)
        r[i] = dr*(i+1);

    pp::matrix H(npoints,npoints);

    //kinetic term
    for(int i=0;i<npoints-1;i++){
        H(i,i)   = -2*(-0.5/dr/dr);
        H(i,i+1) =  1*(-0.5/dr/dr);
        H(i+1,i) =  1*(-0.5/dr/dr);
    }

    H(npoints-1,npoints-1) = -2*(-0.5/dr/dr);

    //potential
    for(int i=0;i<npoints;i++)
        H(i,i) += -1/r[i];

    //diagonalize hydrogen Hamiltonian
    auto [e,Vhyd] = pp::jacobi(H);

    //find ground state
    int k0 = 0;
    for(int k=1;k<e.size();k++)
        if(e[k] < e[k0]) k0 = k;

    // -----------------------------
    // write wavefunction to file
    // -----------------------------

    std::ofstream wave("wave.dat");

    wave<<"# r f(r)\n";

    wave<<"# r f0 f1 f2\n";

    for(int i=0;i<npoints;i++){
        wave
        << r[i] << " "
        << Vhyd(i,k0)/sqrt(dr) << " "
        << Vhyd(i,k0+1)/sqrt(dr) << " "
        << Vhyd(i,k0+2)/sqrt(dr)
        << "\n";
    }

    wave.close();
    
    // --------------------------------------------------
    // Jacobi test 
    // --------------------------------------------------

    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0.0,1.0);

    int n=4;
    pp::matrix A(n,n);

    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            double x = dist(rng);
            A(i,j)=x;
            A(j,i)=x;
        }
    }
    std::cout << "\n\nRunning tests... " << "\n";

    A.print("\nRandom symmetric test matrix A:");

    auto [w,V] = pp::jacobi(A);

    V.print("\nDetermined eigenvectors:");

    pp::matrix D(n,n);
    for(int i=0;i<n;i++)
        D(i,i)=w[i];

    pp::matrix VT = V.T();

    pp::matrix VTAV = VT*A*V;
    pp::matrix VDVT = V*D*VT;
    pp::matrix VTV  = VT*V;
    pp::matrix VVT  = V*VT;

    VTAV.print("\nV^TAV (should be diagonal):");
    std::cout << "\nThis appears diagonal after multiple runs. Please inspect as well.\n";
    std::cout<<"\nEigenvalues:\n";
    for(int i=0;i<w.size();i++)
        std::cout<<w[i]<<"\n";
    D.print("\nD (eigenvalues on diagonal):");

    VDVT.print("\nVDV^T (should equal original A):");
    A.print("\nOriginal A:");
    std::cout << "\nThese seem to match, as expected. Please insepct as well.";

    VTV.print("\nV^TV (should be identity matrix):");
    VVT.print("\nVV^T (should be identity matrix):");
    std::cout << "\nNotice the off-diagonal elements is zero within machine precision, as expected, thus we obtain the identity matrix." << "\n";
    std::cout << "\nFor part B, check wave.png to see the numerically calculated eigenstates of the s-wave states, and the two excited states";
    std::cout << "\nAlso notice that the numercial ground state and exact ground state match in form, but does not lie on top of each other exactly.";

    std::cout<<"\nLowest hydrogen eigenvalues:\n";
    for(int i=0;i<5;i++)
        std::cout<<e[i]<<"\n";

    std::cout << "\nComparison with exact hydrogen energies:\n";
    std::cout << "n=1: numerical = " << e[0]
          << ", exact = -0.5\n";
    std::cout << "n=2: numerical = " << e[1]
          << ", exact = -0.125\n";
    std::cout << "As seen, these seem to match decently well." << "\n";

    std::cout<<"Ground state energy "<<e[k0]<<"\n";

    std::cout << "Please see dr_convergence.png and rmax_convergence.png for the convergence part of part B. It can be seen that as dr decreases, the numerical solution approaches the exact energy E_0 = -0.5, and as r_max increases, the numerical solution aproaches -0,5 as well. However, the biggest difference occour between r_max = 5 and r_max = 7." << "\n";
    return 0;
}
