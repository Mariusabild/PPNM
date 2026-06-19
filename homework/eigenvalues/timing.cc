#include "matrix.h"
#include "jacobi.h"
#include <random>
#include <string>

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
        for(int j=i;j<N;j++){
            double x = dist(rng);
            A(i,j)=x;
            A(j,i)=x;
        }
    }

    auto [w,V] = pp::jacobi(A);

    return 0;
}