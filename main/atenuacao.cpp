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
    double densidades[5] =
    {
        0,
        900,
        1800,
        3600,
        7200
    };
    double er_densidades[5]={0,0,0,0,0};
    double logs[5]=
    {
        0,
        -0.154,
        -0.233,
        -0.368,
        -0.843
    };
    double er_logs[5]=
    {
        0.009,
        0.011,
        0.011,
        0.012,
        0.015
    };

    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);

    auto graf = new TGraphErrors(4, densidades, logs, er_densidades, er_logs);

    graf -> SetMarkerStyle(106);
    graf -> SetTitle("Coeficiente Absorcao");
    graf -> GetXaxis() -> SetTitle("Depth [mg/cm^2]");
    graf -> GetYaxis() -> SetTitle("Log(NET_D/NET_0)");
    //graf -> SetStats(1);
    

    TF1 *f1 = new TF1("f1", "pol1", 0, 8000);
    f1->SetLineColor(kRed);

    graf->Fit(f1, "WR");
    graf->Draw("AP");
    c.Update();
    c.SaveAs("betagrafico.png");
    c.WaitPrimitive();
    App.Run();

}
 