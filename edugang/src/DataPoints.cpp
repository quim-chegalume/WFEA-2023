#include "DataPoints.h"
#include <iostream>

#include "TCanvas.h"
#include "TGraph.h"
#include "TApplication.h"
#include "TSystem.h"

using namespace std;

DataPoints::DataPoints(int N, double * x, double * y) {
    for (int i = 0; i < N; i++) {
        P.emplace_back(x[i], y[i]);
    }
}


//DataPoints::DataPoints(const vector<pair<double, double>> &v) : P(v) {;}
/*
DataPoints::DataPoints(const vector<double> &x, const vector<double> &y) {
    if (x.size() == y.size()) {
        for (int i = 0; i < x.size(); i++) {
            P.emplace_back(x[i], y[i]);
        }
    }
}
*/
DataPoints::~DataPoints() {
    P.clear();
}


//getters

const vector<pair<double, double>> & DataPoints::GetPoints() const {
    return P;
}

void DataPoints::GetGraph(TGraph &G) {
    int i = 0;
    for(const auto & e: P) {
        i++;
        G.AddPoint(e.first, e.second);
    }
    G.SetMarkerStyle(25);
    G.SetMarkerColor(kBlue+2);
    G.SetMarkerSize(2.0);
}

void DataPoints::Draw() {
    TGraph G;
    GetGraph(G);
    TApplication A("DataPoints", nullptr, nullptr);
    if (!c) c = new TCanvas("c", "c", 0, 0, 1200, 900);
    G.Draw("AP");
    c -> Update();
    c -> WaitPrimitive();
    gSystem -> ProcessEvents();
}

std::ostream & operator << (std::ostream & s, const DataPoints & A) {
    s << "[";
    for (const auto & e: A.P) {
        s << "(" << e.first << "," << e.second << ")";
    }
    s << "]";
    return s;
}


//TCanvas
TCanvas * DataPoints::c = nullptr;