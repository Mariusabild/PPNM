#include "ode.h"
#include <iostream>
#include <cmath>
#include <fstream>

int main(){

    // -------------------------------
    // PART A TESTS
    // -------------------------------

    // Test 1: u'' = -u
    {
        auto f = [](double x, pp::vector y){
            return pp::vector{ y[1], -y[0] };
        };

        pp::vector y0 = {1.0, 0.0};

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

    // Damped oscillator (SciPy-style)
    {
        double gamma = 0.25;

        auto f = [gamma](double t, pp::vector y){
            return pp::vector{
                y[1],
                -y[0] - gamma*y[1]
            };
        };

        pp::vector y0 = {1.0, 0.0};

        auto [ts, ys] = pp::driver(f, 0.0, 20.0, y0);

        std::cout << "Damped oscillator final amplitude ≈ "
                  << std::abs(ys.back()[0]) << "\n\n";
    }

    // -------------------------------
    // PART B: ORBITS
    // -------------------------------

    // Case 1: Circular orbit (ε = 0)
    {
        double eps = 0.0;

        auto f = [eps](double phi, pp::vector y){
            return pp::vector{
                y[1],
                1 - y[0] + eps*y[0]*y[0]
            };
        };

        //small pertubation
        pp::vector y0 = {1.0, 1e-6};

        auto [phis, ys] = pp::driver(f, 0.0, 20.0, y0, 0.125, 1e-10, 1e-10);

        std::ofstream file("orbit_circle.txt");

        for(int i = 0; i < phis.size(); i++){
            file << phis[i] << " " << ys[i][0] << "\n";
        }

        std::cout << "Saved orbit_circle.txt\n";
    }

    // Case 2: Elliptical orbit (ε = 0)
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

        std::cout << "Saved orbit_ellipse.txt\n";
    }

    // Case 3: Relativistic precession (ε ≈ 0.01)
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

        std::cout << "Saved orbit_precession.txt\n";
    }

    return 0;
}