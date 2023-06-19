#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "/home/eduardo_silva/D02/103240/src/homework3/DataPoints.h"
#include "/home/eduardo_silva/D02/103240/src/homework3/Interpolator.h"

int main() {

    /*
    double result = I.InterpolateLagrange(2.5);
    cout << "--" << endl; 
    double res = I.InterpolateLagrange(2.0);
    cout << "--" << endl;
    double res3 = I.InterpolateLagrange(1.0);
    cout << "--" << endl;
    double res4 = I.InterpolateLagrange(3.0);
    cout << result << endl; 
    cout << res << endl;    
    cout << res3 << "\n" << res4 << endl;
    */

    /*
    cout << "NEWTON TIME" << endl;   

    double result = I.InterpolateNewton(2.5);
    cout << "--" << endl; 
    double res = I.InterpolateNewton(2.0);
    cout << "--" << endl;
    double res3 = I.InterpolateNewton(1.0);
    cout << "--" << endl;
    double res4 = I.InterpolateNewton(3.0);
    cout << result << endl; 
    cout << res << endl;    
    cout << res3 << "\n" << res4 << endl;
    */


    Interpolator H({{1,0},{2,1},{3,0},{4,1},{5,0}});
    cout << H << endl;

    H.Draw("spline3");

    H.Draw("newton");


    //double result = H.InterpolateSpline3(3.0);

    //cout << result << endl;

    //double res = H.InterpolateSpline3(2.0);

    //cout << res << endl;


    //H.Draw("newton");

    /*cout << "--" << endl;

    H.Draw("lagrange");

    cout << "--" << endl;

    double rp = H.InterpolateSpline3(0.5); //o que acontece se o ponto for menor que o minimo?
    cout << rp << endl;

    cout << "#" << endl;

    double hg = H.InterpolateSpline3(5.0);
    cout << hg << endl;

    cout << "#" << endl;

    double g = H.InterpolateSpline3(7.0); //o que acontece se o ponto for maior?
    cout << g << endl;*/

    /*for (double i = 1; i < 550; i++) {
        double x = i/100;
        cout << "x= " << x << " spline --> " << H.InterpolateSpline3(x) << endl;
    }*/

    /*    
    double res = H.InterpolateSpline3(1.0);

    cout << res << endl;

    double res2 = H.InterpolateSpline3(2.0);

    cout << res2 << endl;

    double res3 = H.InterpolateSpline3(3.0);

    cout << res3 << endl;
    
    double res4 = H.InterpolateSpline3(4.0);

    cout << res4 << endl;

    double res5 = H.InterpolateSpline3(5.0);

    cout << res5 << endl;*/


}