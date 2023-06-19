#ifndef DATAPOINTS_H
#define DATAPOINTS_H

#include "TCanvas.h"
#include "TGraph.h"

#include <vector>
#include <iostream>
#include <initializer_list>

using namespace std;


class DataPoints {
    public:

        // constructors, destructor
        DataPoints() = default; //default constructor (nothing to be done?)
        DataPoints(int N, double* x, double* y); // build DataPoints from C-arrays of x and y values
        //DataPoints(const std::vector< std::pair<double,double> >&);
        //DataPoints(const std::vector< double> & x, const std::vector< double> & y);
        
        //DataPoints(initializer_list<std::pair<double,double>> L) : P(L) {;}
        
        ~DataPoints();
        
        // getters
        const std::vector< std::pair<double,double> >& GetPoints() const;
        void GetGraph(TGraph&);
        
        // draw points using ROOT object TGraph
        virtual void Draw();
        
        // friend functions (optional)
        friend std::ostream& operator<< (std::ostream&, const DataPoints&);
    
    protected:
        
        static TCanvas* c;
        std::vector< std::pair<double,double> > P; // points
};

#endif