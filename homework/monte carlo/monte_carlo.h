#pragma once
#include <cmath>
#include <vector>
#include <functional>
#include <tuple>
#include <cstdint>
#include <iostream>
#include <random>

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

// Prime numbers
inline std::vector<int> prime_numbers(int n){
    std::vector<int> primes;

    for(int candidate=2; (int)primes.size()<n; candidate++){
        bool isprime=true;

        for(int p : primes){
            if(p*p > candidate) break;
            if(candidate % p == 0){
                isprime=false;
                break;
            }
        }

        if(isprime) primes.push_back(candidate);
    }

    return primes;
}

inline double corput(int n, int base){
    double q = 0;
    double bk = 1.0/base;

    while(n>0){
        q += (n % base)*bk;
        n /= base;
        bk /= base;
    }

    return q;
}

// Quasi-random lattice sequence
struct lattice{
    std::vector<double> alpha;

    lattice(int dim){
        auto primes = prime_numbers(dim);

        for(int p : primes)
            alpha.push_back(std::fmod(std::sqrt((double)p),1.0));
    }

    std::vector<double> point(int n) const{
        std::vector<double> x(alpha.size());

        for(size_t i=0;i<alpha.size();i++)
            x[i]=std::fmod(n*alpha[i],1.0);

        return x;
    }
};

struct halton{
    std::vector<int> bases;

    halton(int dim){
        bases = prime_numbers(dim);
    }

    std::vector<double> point(int n) const{
        std::vector<double> x(bases.size());

        for(size_t i=0;i<bases.size();i++)
            x[i] = corput(n,bases[i]);

        return x;
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
//Part B

inline std::tuple<double,double> quasimc(
    std::function<double(const std::vector<double>&)> f,
    std::vector<double> a,
    std::vector<double> b,
    int N)
{
    int dim=a.size();

    double V=1.0;
    for(int i=0;i<dim;i++) V*=b[i]-a[i];

    halton seq1(dim);
    lattice seq2(dim);

    double sum1=0;
    double sum2=0;

    for(int n=1;n<=N;n++){

        auto p1=seq1.point(n);
        auto p2=seq2.point(n);

        std::vector<double> x1(dim);
        std::vector<double> x2(dim);

        for(int i=0;i<dim;i++){
            x1[i]=a[i]+p1[i]*(b[i]-a[i]);
            x2[i]=a[i]+p2[i]*(b[i]-a[i]);
        }

        sum1+=f(x1);
        sum2+=f(x2);
    }

    double result1=V*sum1/N;
    double result2=V*sum2/N;

    double error=std::abs(result1-result2);

    return {result1,error};

    
}

inline std::tuple<double,double> plainmc_std(
    std::function<double(const std::vector<double>&)> f,
    std::vector<double> a,
    std::vector<double> b,
    int N)
{
    std::mt19937 gen(1234);
    std::uniform_real_distribution<double> dist(0.0,1.0);

    int dim=a.size();

    double V=1.0;
    for(int i=0;i<dim;i++) V*=b[i]-a[i];

    double sum1=0;
    double sum2=0;

    std::vector<double> x(dim);

    for(int n=0;n<N;n++){
        for(int i=0;i<dim;i++)
            x[i]=a[i]+dist(gen)*(b[i]-a[i]);

        double fx=f(x);

        sum1+=fx;
        sum2+=fx*fx;
    }

    double mean=sum1/N;
    double sigma=std::sqrt(sum2/N-mean*mean);

    return {mean*V,sigma*V/std::sqrt(N)};
}

    inline std::tuple<double,double> stratifiedmc(
    std::function<double(const std::vector<double>&)> f,
    std::vector<double> a,
    std::vector<double> b,
    int N,
    lcg& rnd)
{
    const int nmin = 32;
    int dim = a.size();

    // Base case
    if(N <= nmin){
        return plainmc(f,a,b,N,rnd);
    }

    // Sample nmin points
    std::vector<double> mean_left(dim,0);
    std::vector<double> mean_right(dim,0);

    std::vector<int> count_left(dim,0);
    std::vector<int> count_right(dim,0);

    std::vector<double> x(dim);

    for(int n=0;n<nmin;n++){

        for(int i=0;i<dim;i++)
            x[i]=a[i]+rnd.next()*(b[i]-a[i]);

        double fx=f(x);

        for(int k=0;k<dim;k++){

            double middle=(a[k]+b[k])/2;

            if(x[k]<middle){
                mean_left[k]+=fx;
                count_left[k]++;
            }
            else{
                mean_right[k]+=fx;
                count_right[k]++;
            }
        }
    }

    // Find largest sub-variance
    int kdiv=0;
    double maxvar=0;

    for(int k=0;k<dim;k++){

        if(count_left[k]==0 || count_right[k]==0)
            continue;

        mean_left[k]/=count_left[k];
        mean_right[k]/=count_right[k];

        double var=
            std::abs(mean_left[k]-mean_right[k]);

        if(var>maxvar){
            maxvar=var;
            kdiv=k;
        }
    }

    // Split region
    std::vector<double> a2=a;
    std::vector<double> b2=b;

    double middle=(a[kdiv]+b[kdiv])/2;

    b[kdiv]=middle;
    a2[kdiv]=middle;

    // Divide remaining points
    int Nleft=(N-nmin)/2;
    int Nright=(N-nmin)-Nleft;

    auto [Ileft,Eleft] =
        stratifiedmc(f,a,b,Nleft,rnd);

    auto [Iright,Eright] =
        stratifiedmc(f,a2,b2,Nright,rnd);

    double I = Ileft + Iright;

    double E =
        std::sqrt(Eleft*Eleft + Eright*Eright);

    return {I,E};
}