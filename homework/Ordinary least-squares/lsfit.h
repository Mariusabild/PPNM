#include "matrix.h"
#include "qr.h"
#include <vector>
#include <functional>


/*
AI use: AI has assisted with tasks such as debugging, helping to translate algorithms and pseudocode from lecture pdf notes into C++ syntax, and help design tests.
Since I made many of the homeworks before it was stated that we should mark the AI-generated code, this is not possible. In general, AI has been used as a tool in all project files.
*/


namespace pp {
    
    //Define the function
    std::tuple<pp::vector, pp::matrix> lsfit(const std::vector<std::function<double(double)>>& fs,
    const pp::vector& x,
    const pp::vector& y,
    const pp::vector& dy)
    {
        //Sizes for A matrix
        int n = x.size();
        int m = fs.size();

        //Define empy matrix and vector
        pp::matrix A(n,m);
        pp::vector b(n);

        //Fill vector b and A according to theroy
        for(int i=0;i<n;i++){
            b[i] = y[i]/dy[i];

        for(int k=0;k<m;k++){
            A(i,k) = fs[k](x[i]) / dy[i];
        }
    }
    //Make QR decomp
    pp::qr decomposition(A);
    pp::vector c = decomposition.solve(b);
    pp::matrix R = decomposition.R;

    pp::qr Rqr(R);             
    pp::matrix Rinv = Rqr.inverse();

    pp::matrix cov = Rinv * Rinv.T();
    return {c, cov};
    }
}