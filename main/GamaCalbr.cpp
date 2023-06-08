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
    double energias[4] =
    {
        32,
        662,
        1173,
        1333
    };
    double er_energias[4]={0,0,0,0};
    double Centroides[4]=
    {
        18.29,
        394.26,
        690.84,
        783.24
    };
    double er_Centroides[4]=
    {
        0.01,
        0.03,
        0.19,
        0.22
    };

    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);

    auto graf = new TGraphErrors(4, Centroides, energias, er_Centroides, er_energias);

    graf -> SetMarkerStyle(106);
    graf -> SetTitle("Reta de calibracao");
    graf -> GetXaxis() -> SetTitle("Centroides (Chn)");
    graf -> GetYaxis() -> SetTitle("Energias (KeV)");
    graf -> SetStats(1);
    

    TF1 *f1 = new TF1("f1", "pol1", 0, 1000);
    f1->SetLineColor(kRed);

    graf->Fit(f1, "WR");
    graf->Draw("AP");
    c.Update();
    c.SaveAs("gamacalibr.png");
    c.WaitPrimitive();
    App.Run();

}
