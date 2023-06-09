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

int main()
{
    double energias[9] =
    {
        333.36,
        389.16,
        444.96,
        500.76,
        556.56,
        612.36,
        668.16,
        723.96,
        779.76
    };
    double er_energias[9]=
    {
        16.74,
        11.16,
        11.16,
        11.16,
        5.58,
        5.58,
        11.16,
        5.58,
        5.58,
    };
    double PHD[9]=
    {
        3.26,
        2.89,
        2.59,
        2.02,
        1.58,
        1.05,
        0.72,
        0.33,
        0.20
    };
    double er_PHD[9]=
    {
        0.16,
        0.12,
        0.10,
        0.07,
        0.05,
        0.03,
        0.03,
        0.01,
        0.01
    };

    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);

    auto graf = new TGraphErrors(9, energias, PHD, er_energias, er_PHD);

    TF1 *f1 = new TF1("f1", "pol1", 0, 800);
    f1->SetLineColor(kRed);

    
    graf -> SetTitle("Limite Cinematico - Kurie Plot");
    graf -> GetXaxis() ->SetTitle("Energia [keV]");
    graf -> GetYaxis() -> SetTitle("PHD(N,W,G)"); 
    graf->Fit(f1, "W","",300,800);
    graf->Draw("AP");
    c.Update();
    c.SaveAs("betagrafico.png");
    c.WaitPrimitive();
<<<<<<< HEAD

    App.Run();
=======
    _App.Run();

>>>>>>> 4f6c27d3d2588354e26976dd1c1a20d820482e0d
}
