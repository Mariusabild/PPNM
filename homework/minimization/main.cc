#include <iostream>
#include "minimization.h"
#include <vector>
#include <fstream>

double rosenbrock(const pp::vector& v){

    double x=v[0];
    double y=v[1];

    return
        (1-x)*(1-x)
        +100*(y-x*x)*(y-x*x);
}

double himmelblau(const pp::vector& v){

    double x=v[0];
    double y=v[1];

    return
        (x*x+y-11)*(x*x+y-11)
        +(x+y*y-7)*(x+y*y-7);
}
//Part B

int main(){

    
std::vector<double> energy;
std::vector<double> signal;
std::vector<double> error;


    double E,s,d;

while(std::cin >> E >> s >> d){

    energy.push_back(E);
    signal.push_back(s);
    error.push_back(d);
}

std::ofstream datafile("data.txt");

for(size_t i=0;i<energy.size();i++){

    datafile
        << energy[i] << " "
        << signal[i] << " "
        << error[i] << "\n";
}
auto deviation =
[&](const pp::vector& p)
{
    double m     = p[0];
    double Gamma = p[1];
    double A     = p[2];

    double D = 0;

    for(size_t i=0;i<energy.size();i++){

        double F =
            pp::breit_wigner(
                energy[i],
                m,
                Gamma,
                A
            );

        double term =
            (F-signal[i])
            /error[i];

        D += term*term;
    }

    return D;
};


    pp::vector start(3);

    start[0]=125.0;
    start[1]=5.0;
    start[2]=30.0;

    pp::vector fit=
        pp::newton_min(
            deviation,
            start
        );

    std::cout
    << "Part B: Higgs fit\n"
    << "Mass  = " << fit[0] << "\n"
    << "Gamma = " << std::abs(fit[1]) << "\n"
    << "A     = " << fit[2] << "\n\n";

        std::ofstream fitfile("fit.txt");

for(double E=100; E<=160; E+=0.1){

    fitfile
        << E << " "
        << pp::breit_wigner(
               E,
               fit[0],
               fit[1],
               fit[2]
           )
        << "\n";
}

    pp::vector r0(2);
r0[0] = -1;
r0[1] = 1;

pp::vector r =
    pp::newton_min(
        rosenbrock,
        r0
    );

pp::vector r_c =
    pp::newton_min_central(
        rosenbrock,
        r0
    );

pp::vector h0(2);
h0[0] = 2;
h0[1] = 2;

pp::vector h =
    pp::newton_min(
        himmelblau,
        h0
    );

pp::vector h_c =
    pp::newton_min_central(
        himmelblau,
        h0
    );

std::cout
    << "Part A/C: Comparison\n\n"

    << "Rosenbrock\n"
    << "Forward difference : "
    << r[0] << " "
    << r[1] << "\n"

    << "Central difference : "
    << r_c[0] << " "
    << r_c[1] << "\n\n"

    << "Himmelblau\n"
    << "Forward difference : "
    << h[0] << " "
    << h[1] << "\n"

    << "Central difference : "
    << h_c[0] << " "
    << h_c[1] << "\n\n"

    << "Conclusion: For the Rosenbrock, we see that the central difference is more correct as we expect (1,1), which the central difference method yields, however using 1 more step. The Himmelblau is'nt improved by using the central difference method however.\n";

    return 0;
}