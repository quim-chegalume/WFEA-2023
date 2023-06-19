#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include "DataPoints.h"
#include "TF1.h"
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


class Interpolator : public DataPoints {
    public:
    // constructors, destructor
        
        Interpolator() = default; //default constructor (nothing to be done?)
        Interpolator(int N, double* x, double* y); // build DataPoints from C-arrays of x and y values
        Interpolator(const std::vector< std::pair<double,double> >&);
        Interpolator(const std::vector< double>& x, const std::vector< double>& y);
        Interpolator(initializer_list<pair<double,double>>);
        
        ~Interpolator();
        
    // interpolation methods
        
        void Init(); // calculations need at init time (a coeffs, map)
        
        double InterpolateLagrange(double); // Lagrange interpolation
        double InterpolateNewton(double); // Newton interpolation
        double InterpolateSpline3(double); // spline3
        
        // draw points and function
        void Draw(std::string s); // s="lagrange", "newton", "spline3"

        const TF1& GetFunction(std::string s); 

    private:
        std::vector<double> x,y; // data points x,y
        std::map<std::string,TF1*> MI; // key="lagrange", "newton", "spline3"
        
        // Newton interpolation
        //std::vector<double> a; // coefficients
};

#endif