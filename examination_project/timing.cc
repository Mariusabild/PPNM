#include "matrix.h"
#include "svd.h"
#include <random>
#include <string>

//This is adapted from a old homework.
int main(int argc, char** argv){

    int N = 100;

    for(int i=1;i<argc;i++){
        std::string arg = argv[i];
        if(arg == "-size") {
            N = std::stoi(argv[i+1]);
        }
    }

    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0,1);

    pp::matrix A(N,N);

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            double x = dist(rng);
            A(i,j)=x;
        }
    }

    auto [U, D, V] = pp::jacobi_svd(A);

    return 0;
}