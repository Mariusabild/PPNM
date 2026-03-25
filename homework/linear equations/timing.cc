#include "matrix.h"
#include "qr.h"
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
        for(int j=0;j<N;j++){
            A(i,j) = dist(rng);
        }
    }

    // DET VI MÅLER
    pp::qr decomp(A);

    return 0;
}