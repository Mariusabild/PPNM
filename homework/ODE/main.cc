#include "ode.h"
#include <iostream>
#include <cmath>
#include <fstream>

int main(){

    // -------------------------------
    // PART A TESTS
    // -------------------------------

    std::cout << "Tests... " << "\n\n";

    // Test 1: u'' = -u
    {
        auto f = [](double x, pp::vector y){
            return pp::vector{ y[1], -y[0] };
        };

        pp::vector y0 = {1.0, 0};

        auto [xs, ys] = pp::driver(f, 0.0, 10.0, y0);

        double max_error = 0.0;

        for(int i = 0; i < xs.size(); i++){
            double exact = std::cos(xs[i]);
            double error = std::abs(ys[i][0] - exact);
            if(error > max_error) max_error = error;
        }

        std::cout << "Test: u'' = -u\n";
        std::cout << "Max error = " << max_error << "\n\n";
    }

    // Test 2: y' = y
    {
        auto f = [](double x, pp::vector y){
            return y;
        };

        pp::vector y0 = {1.0};

        auto [xs, ys] = pp::driver(f, 0.0, 5.0, y0);

        double max_error = 0.0;

        for(int i = 0; i < xs.size(); i++){
            double exact = std::exp(xs[i]);
            double error = std::abs(ys[i][0] - exact);
            if(error > max_error) max_error = error;
        }

        std::cout << "Test: y' = y\n";
        std::cout << "Max error = " << max_error << "\n\n";
    }

    std::cout << "SciPy odeint example can be seen in damped_oscillator.png" << "\n";
// SciPy odeint example
{
    double b = 0.25;
    double c = 5.0;

    auto f = [b,c](double t, pp::vector y){
        return pp::vector{
            y[1],
            -b*y[1] - c*std::sin(y[0])
        };
    };

    pp::vector y0 = {M_PI-0.1,0.0};

    auto [ts,ys] = pp::driver(f,0.0,10.0,y0);

    std::ofstream file("damped_oscillator.txt");

    for(size_t i=0;i<ts.size();i++){
        file << ts[i] << " "
             << ys[i][0] << " "
             << ys[i][1] << "\n";
    }

}

    // -------------------------------
    // PART B: ORBITS
    // -------------------------------

    // Case 1
    {
        //Notice we have set a small pertubation here
        double eps = 10e-6;

        auto f = [eps](double phi, pp::vector y){
            return pp::vector{
                y[1],
                1 - y[0] + eps*y[0]*y[0]
            };
        };

        //small pertubation
        pp::vector y0 = {1.0, 0};

        auto [phis, ys] = pp::driver(f, 0.0, 100.0, y0, 0.125, 1e-10, 1e-10);

        std::ofstream file("orbit_circle.txt");

        for(int i = 0; i < phis.size(); i++){
            file << phis[i] << " " << ys[i][0] << "\n";
        }

    }

    // Case 2
    {
        double eps = 0.0;

        auto f = [eps](double phi, pp::vector y){
            return pp::vector{
                y[1],
                1 - y[0] + eps*y[0]*y[0]
            };
        };

        pp::vector y0 = {1.0, -0.5};

        auto [phis, ys] = pp::driver(f, 0.0, 20.0, y0, 0.125, 1e-6, 1e-6);

        std::ofstream file("orbit_ellipse.txt");

        for(int i = 0; i < phis.size(); i++){
            file << phis[i] << " " << ys[i][0] << "\n";
        }

    }

    // Case 3
    {
        double eps = 0.01;

        auto f = [eps](double phi, pp::vector y){
            return pp::vector{
                y[1],
                1 - y[0] + eps*y[0]*y[0]
            };
        };

        pp::vector y0 = {1.0, -0.5};

        auto [phis, ys] = pp::driver(f, 0.0, 20.0, y0, 0.125, 1e-6, 1e-6);

        std::ofstream file("orbit_precession.txt");

        for(int i = 0; i < phis.size(); i++){
            file << phis[i] << " " << ys[i][0] << "\n";
        }

    }


    // -------------------------------
// PART C: THREE-BODY FIGURE-8
// -------------------------------
{
    auto f = [](double t, pp::vector z){

        pp::vector dz(12);

        // positions
        double x1=z[6],  y1=z[7];
        double x2=z[8],  y2=z[9];
        double x3=z[10], y3=z[11];

        // velocities
        double vx1=z[0], vy1=z[1];
        double vx2=z[2], vy2=z[3];
        double vx3=z[4], vy3=z[5];

        // helper: gravitational acceleration
        auto acc = [](double xi,double yi,double xj,double yj){
            double dx = xj - xi;
            double dy = yj - yi;
            double r  = std::sqrt(dx*dx + dy*dy);
            double r3 = r*r*r;
            return std::pair<double,double>{dx/r3, dy/r3};
        };

        // accelerations
        auto [a12x,a12y]=acc(x1,y1,x2,y2);
        auto [a13x,a13y]=acc(x1,y1,x3,y3);

        auto [a21x,a21y]=acc(x2,y2,x1,y1);
        auto [a23x,a23y]=acc(x2,y2,x3,y3);

        auto [a31x,a31y]=acc(x3,y3,x1,y1);
        auto [a32x,a32y]=acc(x3,y3,x2,y2);

        // dv/dt
        dz[0]=a12x+a13x;
        dz[1]=a12y+a13y;

        dz[2]=a21x+a23x;
        dz[3]=a21y+a23y;

        dz[4]=a31x+a32x;
        dz[5]=a31y+a32y;

        // dx/dt
        dz[6]=vx1; dz[7]=vy1;
        dz[8]=vx2; dz[9]=vy2;
        dz[10]=vx3; dz[11]=vy3;

        return dz;
    };

    pp::vector z0 = {
         0.4662036850,  0.4323657300,
         0.4662036850,  0.4323657300,
        -0.93240737,   -0.86473146,

        -0.97000436,    0.24308753,
         0.97000436,   -0.24308753,
         0.0,           0.0
    };

    auto [ts, zs] = pp::driver(f, 0.0, 10.0, z0, 0.01, 1e-6, 1e-6);

    std::ofstream file("threebody.txt");

    for(int i=0;i<ts.size();i++){
        file << zs[i][6]  << " " << zs[i][7]  << " "
             << zs[i][8]  << " " << zs[i][9]  << " "
             << zs[i][10] << " " << zs[i][11] << "\n";
    }

    file.close();

}

    std::cout << "Please check orbit.png, and threebody.png for part B and C" << "\n";

    return 0;
}