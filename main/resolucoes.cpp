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
    double resolucoes[4]=
    {
        0.1046875,
        0.0363293,
        0.02647059,
        0.0250938
    };
    double er_resolucoes[4]=
    {
        3.44e-4,
        9.06e-5,
        3.84e-4,
        3.6e-4
    };

    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);

    auto graf = new TGraphErrors(4, energias, resolucoes, er_energias, er_resolucoes);
    graf->SetMarkerStyle(3);

    graf -> SetMarkerStyle(106);
    graf -> SetTitle("Resolucao em funcao da energia");
    graf -> GetXaxis() -> SetTitle("Energias (KeV)");
    graf -> GetYaxis() -> SetTitle("Resolucoes");
    graf -> SetStats(1);
    

    TF1 *f1 = new TF1("f1", "[0]/sqrt(x)+[1]", 0, 1400);
    f1->SetLineColor(kRed);

    graf->Fit(f1, "R");
    graf->Draw("AP");
    c.Update();
    c.SaveAs("resolucoesgrafico.png");
    c.WaitPrimitive();
    App.Run();

}
