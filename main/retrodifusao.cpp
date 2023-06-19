#include "TStyle.h"
#include "TAxis.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TF1.h"
#include "TAxis.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;


int main()
{
    double bs[8] =
    {
        1,
        1.175,
        1.241,
        1.301,
        1.440,
        1.457,
        1.512,
        1.728
    };
    double er_bs[8] =
    {
        0.12,
        0.13,
        0.14,
        0.14,
        0.16,
        0.16,
        0.16,
        0.18
    };
    
    double sat[8]=
    {
        0,
        1.555,
        2.343,
        2.597,
        3.533,
        3.700,
        5.494,
        5.731
    };
    double er_sat[8]=
    {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    };

    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);

    auto graf = new TGraphErrors(8, sat, bs, er_sat, er_bs);

    graf -> SetMarkerStyle(106);
    graf -> SetTitle("Relacao entre fatores");
    graf -> GetXaxis() -> SetTitle("f(sat) [u.m.a]^(-1/2)");
    graf -> GetYaxis() -> SetTitle("f(bs)");
    //graf -> SetStats(1);
    

    TF1 *f1 = new TF1("f1", "pol1", 0, 6);
    f1->SetLineColor(kRed);

    graf->Fit(f1, "WR");
    graf->Draw("AP");
    c.Update();
    c.SaveAs("retrobetagrafico.png");
    c.WaitPrimitive();
    App.Run();

}
 
