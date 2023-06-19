#include "Interpolator.h"
#include "DataPoints.h"
#include "/home/eduardo_silva/D02/103240/src/homework2/FCmatrixAlgo.h"
#include "/home/eduardo_silva/D02/103240/src/homework2/EqSolver.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <map>

#include "TCanvas.h"
#include "TApplication.h"
#include "TGraph.h"
#include "TSystem.h"
#include "TMultiGraph.h"
#include "TH1D.h"
#include "TF1.h"

using namespace std;

//constructors, destructor

Interpolator::~Interpolator(){
    delete[] MI["lagrange"];
    delete[] MI["newton"];
    delete[] MI["spline3"];
}

Interpolator::Interpolator(int N, double* x, double* y) : DataPoints(N,x,y) {;}

Interpolator::Interpolator(const std::vector<std::pair<double,double>> & v): DataPoints(v) {;}

Interpolator::Interpolator(const std::vector<double> &x, const std::vector<double> &y) : DataPoints(x,y) {;}

Interpolator::Interpolator(initializer_list<pair<double,double>> L) : DataPoints(L){
    Init();
}

void Interpolator::Init(){
    for(const auto&e : P){
        x.push_back(e.first);
        y.push_back(e.second);
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//interpolation methods
double Interpolator::InterpolateLagrange(double x) { //instead of second loop to calculate sum, uses inner product
    
    int n = P.size() - 1; //degree of polynomial, n+1 datapoints
    vector<double> li_x(n + 1); //store li's (products)
    vector<double> yi(n+1); // vector for yi's

    for (int i = 0; i < n + 1; i ++) { //product
        double res = 1.0; //1, not 0
        
        for (int j = 0; j < n+1; j++) {
            if (j != i) {
                res *= (x - P[j].first) / (P[i].first - P[j].first);
            }
        }
        li_x.push_back(res);
        yi.push_back(P[i].second); //hijacking this loop to create a vector with yi's

    }
    double Pn_x = inner_product(li_x.begin(), li_x.end(), yi.begin(), 0.0);
    return Pn_x;
}

double Interpolator::InterpolateNewton(double x) {

    int n = P.size() - 1;
    vector<double> a; //store coefficients
    
    for (int i = 0; i < n + 1; i++) { // iteration 0
        a.push_back(P[i].second);
    }

    for (int k = 1; k < n + 1; k++){ //coefficients
        for (int i = k; i < n + 1; i++){
            double sum = (a[i] - a[k-1]) / (P[i].first - P[k-1].first);
            a[i] = sum;
        }

    }

    double Pn_x = a[n];
    for (int k = 1; k <n+1; k++) {
        Pn_x = a[n-k] + (x - P[n-k].first)*Pn_x;
    }

    return Pn_x;
}

double Interpolator::InterpolateSpline3(double x) {

    int n = P.size() - 1;
    Eigen::Matrix<double,Eigen::Dynamic,1> b(n-1); //vector os Ks

    std::sort(P.begin(), P.end()); //sort dos xx

    Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> A(n-1, n-1); //matriz coeffs
    for (int i = 0; i < A.rows(); i++) {
        for (int j = 0; j < A.rows(); j++) {
            A(i, j) = 0.0;
        }
    }

    for (int i = 1; i < n; i++) {
        if (i == n - 1) {
            A(i-1, i-1) = 2*(P[i-1].first - P[i+1].first);
            b(i-1, 0) = 6 * (((P[i-1].second - P[i].second)/(P[i-1].first - P[i].first)) - ((P[i].second - P[i+1].second)/(P[i].first - P[i+1].first)));
        }
        else {
            A(i-1, i-1) = 2*(P[i-1].first - P[i+1].first);
            double conta = P[i].first - P[i+1].first;
            A(i, i-1) = conta;
            A(i-1, i) = conta;
            b(i-1, 0) = 6 * (((P[i-1].second - P[i].second)/(P[i-1].first - P[i].first)) - ((P[i].second - P[i+1].second)/(P[i].first - P[i+1].first)));
        }
    }


    FCmatrixAlgo M1;
    M1.GaussElimination(A, b);


    EqSolver MT(A, b);
    Eigen::Matrix<double,Eigen::Dynamic,1> v;
    v = MT.GaussSolver(); //podemos usar isto porque o mesmo x nunca vai ter 2 y's senao nao era funcao

    //acrescentar o valor K0 = 0 e K_last = 0, por definicao simples do spline
    //o vetor v so tinha K1, K2, K3 entao pomos K0 e K_last antes desses  

    
    bool existencia = false;
    for (int i = 1; i < P.size(); i++) { //o i é +1 valor do que nas outras sitauções ou seja P[i] = xi+1

        if (x <= P[i].first) { //so that it accepts the last value of P 

            existencia = true;

            if (i == 1) {
                double res = 0 - //because K0 is 0.0 by definition
                            (v(i-1, 0)/6.0) * ((pow(x-P[i-1].first, 3) / (P[i-1].first - P[i].first)) - ((x - P[i-1].first) * (P[i-1].first - P[i].first))) +
                            ((P[i-1].second * (x - P[i].first)) - (P[i].second * (x - P[i-1].first))) / (P[i-1].first - P[i].first);
                return res;
            }
            
            if (i == P.size() - 1) { //K_last will be zero by definition
                double res = (v(i-2,0)/6.0) * ((pow(x-P[i].first, 3) / (P[i-1].first - P[i].first)) - ((x - P[i].first) * (P[i-1].first - P[i].first))) -
                            0 +
                            ((P[i-1].second * (x - P[i].first)) - (P[i].second * (x - P[i-1].first))) / (P[i-1].first - P[i].first);
                return res;
            }

            else {
                double res = (v(i-2,0)/6.0) * ((pow(x-P[i].first, 3) / (P[i-1].first - P[i].first)) - ((x - P[i].first) * (P[i-1].first - P[i].first))) -
                            (v(i-1, 0)/6.0) * ((pow(x-P[i-1].first, 3) / (P[i-1].first - P[i].first)) - ((x - P[i-1].first) * (P[i-1].first - P[i].first))) +
                            ((P[i-1].second * (x - P[i].first)) - (P[i].second * (x - P[i-1].first))) / (P[i-1].first - P[i].first);
                return res;
            }
        }
    }




    


    if (!existencia) {
        cout << "Esse valor não pertence ao intervalo" << endl;
        return 0.0;
    }

    return 0.0;

}

const TF1& Interpolator::GetFunction(std::string s) {

    if (MI.find(s) != MI.end()) { //found the key
        return *MI[s];
    }

    else {
        if (s == "lagrange") {
            auto frec = [this](double *x, double * par) {
                return InterpolateLagrange(x[0]);
            };
            auto F1 = new TF1("lagrange", frec, P[0].first, P[P.size()-1].first, 0);
            MI["lagrange"] = F1;
            return *MI[s];
        }

        if (s == "newton") {
            auto frec = [this](double *x, double * par) {
                return InterpolateNewton(x[0]);
            };
            auto F1 = new TF1("newton", frec, P[0].first, P[P.size()-1].first, 0);           
            MI["newton"] = F1;
            return *MI[s];            
        }

        if (s == "spline3") {
            auto frec = [this](double *x, double * par) {
                return InterpolateSpline3(x[0]);
            };
            auto F1 = new TF1("spline3", frec, P[0].first, P[P.size()-1].first, 0);           
            MI["spline3"] = F1;
            return *MI[s];                      
        }
    }
    exit(-1);
}



//para ser possivel fazer mais que um grafico no main
//será que existe outra forma mais eficiente?

TApplication app("GRAPHIC", nullptr, nullptr);
TCanvas  * canvas = new TCanvas("canvas", "", 1200, 800);
    


void Interpolator::Draw(string s) {
    
 
    //TApplication app("GRAPHIC", nullptr, nullptr);
    //TCanvas  * canvas = new TCanvas("canvas", "", 1200, 800);
    

    TF1 * func = new TF1;
    TGraph grafico;


    *func = Interpolator::GetFunction(s); //obter o valor das funções
    DataPoints::GetGraph(grafico); //obter os valores dos pontos

    grafico.Draw("A*");

    func -> Draw("same");

    canvas -> Update();
    canvas -> WaitPrimitive();
    gSystem -> ProcessEvents();

}






/*



//TO:DO getters
void Interpolator::GetPoints() const : DataPoints::GetPoints(){
}

void Interpolator::GetGraph(TGraph &G){
    int i = 0;
    for(const auto & e: P){
        i++;
        G.SetPoint(i,e.first,e.second);
    
    }
    G.SetMarkerStyle(25);
    G.SetMarkerColor(kPink + 2);
    G.SetMarkerSize(2.);
}

//Draw
//fazer TF1 com lambda function
void Interpolator::Draw() {
    TGraph G;
    GetGraph(G);
    //faltam coisas no draw



        if (s == "lagrange") {
        auto frec = [this](double *x, double * par) {
            return InterpolateLagrange(x[0]);
        };

        auto F1 = new TF1("lagrange", frec, 0.0, 5.0, 0);

        F1 -> SetLineColor(kRed+2);
        F1 -> SetLineWidth(4);
        F1 -> Draw("APL");
        canvas.Update();
        canvas.WaitPrimitive();
        gSystem -> ProcessEvents();



    }
    if (s == "newton") {
        auto frec = [this](double *x, double * par) {
            return InterpolateNewton(x[0]);
        };

        auto F1 = new TF1("newton", frec, 0.0, 5.0, 0);

        F1 -> SetLineColor(kRed+2);
        F1 -> SetLineWidth(4);
        F1 -> Draw("APL");
        canvas.Update();
        canvas.WaitPrimitive();
        gSystem -> ProcessEvents();

    }
    if (s =="spline3") {
        auto frec = [this](double *x, double * par) {
            return InterpolateSpline3(x[0]);
        };


        auto F1 = new TF1("spline3", frec, 1.0, 5.0, 0);

        F1 -> SetLineColor(kRed+2);
        F1 -> SetLineWidth(4);
        F1 -> Draw("APL");
        canvas.Update();
        canvas.WaitPrimitive();
        gSystem -> ProcessEvents();

    }

}

*/
