#pragma once
#include <cmath>
#include <vector>
#include <functional>
#include <tuple>
#include <cstdint>

//Random uniform generator
struct lcg{
    uint64_t seed;
    uint64_t a;
    uint64_t c;
    uint64_t m;

    lcg(uint64_t seed_, uint64_t a_ = 1664525, uint64_t c_ = 1013904223, uint64_t m_ = (1ULL << 32))
    : seed(seed_), a(a_), c(c_), m(m_) {}

        double next(){
            seed = (a * seed + c) % m;
            return (seed + 1.0) / (m+1.0);
    }
};

//Function for plain MC; input:
//Function f
//a, b is integration limits
//N is number of samples
//lcd generator of random numbers
std::tuple<double,double> plainmc(std::function<double(const std::vector<double>&)> f, std::vector<double> a, std::vector<double> b, int N, lcg& rnd){
    int dim = a.size();
    //Calculate volume V
    double V = 1.0;
    for(int i = 0; i<dim; i++){V *= b[i] - a[i];}
    //sum of function values 
    double sum1 = 0;
    double sum2 = 0;
    //Vector defining a point in the volume of integration
    std::vector<double> x(dim);
    for(int n = 0; n < N; n++){
        for(int i = 0; i < dim; i++){
            x[i] = a[i] +rnd.next() * (b[i] - a[i]);
        }
        double fx = f(x);
        sum1 += fx;
        sum2 += fx*fx;
    }
    double mean = sum1 / N;
    double sigma = std::sqrt(sum2 / N - mean*mean);
        
    return std::tuple<double, double >(mean *V, sigma * V/ std::sqrt(N));
}