#include <iostream>
#include "roots.h"
#include <fstream>

pp::vector f_test1(const pp::vector& x){
    return {x[0]*x[0]-2};
}
pp::vector f_test2(const pp::vector& v){

    double x=v[0];
    double y=v[1];

    return {
        x+y-2,
        x-y
    };
}

pp::vector rosen_grad(const pp::vector& v){
    double x=v[0];
    double y=v[1];

    return {
        -2*(1-x)-400*x*(y-x*x),
        200*(y-x*x)
    };
}

pp::vector himmelblau_grad(const pp::vector& v){

    double x = v[0];
    double y = v[1];

    return {
        4*x*(x*x+y-11) + 2*(x+y*y-7),
        2*(x*x+y-11) + 4*y*(x+y*y-7)
    };
}

//Part B
pp::vector hydrogen_ode(double r,
                        const pp::vector& y,
                        double E)
{
    return {
        y[1],
        -2.0*(E + 1.0/r)*y[0]
    };
}

double M(double E,
         double rmin = 1e-3,
         double rmax = 8.0,
         double acc = 0.01,
         double eps = 0.01){

    pp::vector y0 = {
        rmin-rmin*rmin,
        1-2*rmin
    };

    auto ode = [E](double r, pp::vector y){
        return hydrogen_ode(r,y,E);
    };

    auto [rlist,ylist] =
        pp::driver(ode,rmin,rmax,y0,0.125,acc,eps);

    return ylist.back()[0];
}

pp::vector hydrogen_root_param(const pp::vector& x,
                         double rmin,
                         double rmax,
                         double acc,
                         double eps){

    return {M(x[0],rmin,rmax,acc,eps)};
}

pp::vector hydrogen_root(const pp::vector& x){
    double E = x[0];
    return {M(E)};
}

void hydrogen_wavefunction(double E){

    double rmin = 1e-3;
    double rmax = 8.0;

    pp::vector y0 = {
        rmin-rmin*rmin,
        1-2*rmin
    };

    auto ode = [E](double r, pp::vector y){
        return hydrogen_ode(r,y,E);
    };

    auto [rlist,ylist] =
        pp::driver(ode,rmin,rmax,y0);

    std::ofstream out("hydrogen.data");

    for(int i=0;i<rlist.size();i++){

        double r = rlist[i];

        double numerical = ylist[i][0];

        double exact = r*std::exp(-r);

        out
            << r << " "
            << numerical << " "
            << exact << "\n";
    }
}

int main(){
    pp::vector start_1 = {1.0};
    pp::vector root_test1 = pp::newton(f_test1,start_1);

    pp::vector start_2 = {3,4};
    pp::vector root_test2 = pp::newton(f_test2, start_2);

    pp::vector start_rosen = {1.5,1.5};
    //we need more iterations, otherwise it stops too early
    pp::vector root_rosen = pp::newton(rosen_grad,start_rosen, 1e-2,1e-3,10000);

    pp::vector start_himmel = {3,2};
    pp::vector root_himmel = pp::newton(himmelblau_grad, start_himmel, 1e-2,1e-3,10000);
    pp::vector start_himmel2 = {-3,3};
    pp::vector root_himmel2 = pp::newton(himmelblau_grad,start_himmel2, 1e-2,1e-3, 10000);

    root_test1.print("root for x^2-2 = 0, is: ");
    std::cout << "expected root: (1.41421356)\n\n";
    root_test2.print("root for x+y-2 = 0 & x-y = 0 is: ");
    std::cout << "expected root: (1,1)\n\n";
    root_rosen.print("root for the rosenbock function is: ");
    std::cout << "expected root: (1,1)\n\n";
    root_himmel.print("root for Himmelblau gradient is: ");
    std::cout << "expected root: (3,2)\n\n";
    root_himmel2.print("root for Himmelblau gradient from (-3,3) is: ");
    std::cout << "expected root: (-2.805118,3.131312)\n\n";

    //part B
    /*
    std::cout << "\nHydrogen shooting test:\n";

    std::cout << "M(-0.4) = "
          << M(-0.4)
          << "\n";

    std::cout << "M(-0.5) = "
          << M(-0.5)
          << "\n";

    std::cout << "M(-0.6) = "
          << M(-0.6)
          << "\n";
    */
    pp::vector Estart = {-0.4};
    pp::vector Eroot = pp::newton(hydrogen_root,Estart,1e-6,1e-3,100);

    Eroot.print("Ground state energy: ");
    std::cout << "expected energy: (-0.5)\n";

    double E0 = Eroot[0];

    hydrogen_wavefunction(E0);

    std::cout
    << "wavefunction written to hydrogen.data\n";

    std::cout << "\nConvergence in rmax:\n";

    for(double rmax : {4.0,6.0,8.0,10.0,12.0}){

    auto rootfun =
        [rmax](const pp::vector& x){
            return hydrogen_root_param(
                x,
                1e-3,
                rmax,
                0.01,
                0.01
            );
        };

    pp::vector E0 =
    pp::newton(rootfun,{-0.5});

    std::cout
        << "rmax = "
        << rmax
        << "   E0 = "
        << E0[0]
        << "\n";
}
std::cout << "\nConvergence in rmin:\n";

for(double rmin : {1e-1,1e-2,1e-3,1e-4,1e-5}){

    auto rootfun =
        [rmin](const pp::vector& x){
            return hydrogen_root_param(
                x,
                rmin,
                8.0,
                0.01,
                0.01
            );
        };

    pp::vector E0 =
        pp::newton(rootfun,{-0.5});

    std::cout
        << "rmin = "
        << rmin
        << "   E0 = "
        << E0[0]
        << "\n";
}
std::cout << "\nConvergence in acc:\n";

for(double acc : {1e-1,1e-2,1e-3,1e-4}){

    auto rootfun =
        [acc](const pp::vector& x){
            return hydrogen_root_param(
                x,
                1e-3,
                8.0,
                acc,
                0.01
            );
        };

    pp::vector E0 =
        pp::newton(rootfun,{-0.5});

    std::cout
        << "acc = "
        << acc
        << "   E0 = "
        << E0[0]
        << "\n";
}
std::cout << "\nConvergence in eps:\n";

for(double eps : {1e-1,1e-2,1e-3,1e-4}){

    auto rootfun =
        [eps](const pp::vector& x){
            return hydrogen_root_param(
                x,
                1e-3,
                8.0,
                0.01,
                eps
            );
        };

    pp::vector E0 =
        pp::newton(rootfun,{-0.5});

    std::cout
        << "eps = "
        << eps
        << "   E0 = "
        << E0[0]
        << "\n";
}
    
    return 0;
}