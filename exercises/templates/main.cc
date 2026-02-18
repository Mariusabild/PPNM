#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include "vec.h"

template<typename T1, typename T2>
static bool approx_universal(T1 a, T2 b, double acc=1e-9, double eps=1e-9) {
    using std::abs;
    // Vi konverterer altid til double sammenligning for at være sikre
    double val_a = abs(a);
    double val_b = abs(static_cast<double>(abs(b)));
    double diff = abs(abs(a) - abs(b));
    
    if(diff < acc) return true;
    if(diff < eps*(val_a + val_b)) return true;
    return false;
}

static void test(bool ok, const std::string& name){
    std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << "\n";
}

int main(){
    // DU KAN FRIT SKIFTE MELLEM DISSE TRE:
    using V = vec<int>;
    //  using V = vec<double>;
    //using V = vec<std::complex<double>>;

    V u(1, 2, 3), v(4, 5, 6);
    std::cout << "Tester vector aritmetik...\n";

    // Test multiplikation (u*2 og 2*u)
    V m1 = u * 2;
    V m2 = 2 * u;
    test(approx(m1, m2), "u*2 == 2*u");

    // Algebra tests
    V ex(1,0,0), ey(0,1,0), ez(0,0,1);
    test( approx_universal(ex.dot(ey), 0), "dot: ex.ey = 0");
    
    V uxv = u.cross(v);
    test( approx_universal(u.dot(uxv), 0), "ortho: u.(u x v) = 0");

    // Norm test
    test( approx_universal(ex.norm(), 1), "norm: |ex| = 1");
    
    std::cout << "\nFærdig! Virker nu med alle typer.\n";
    return 0;
}