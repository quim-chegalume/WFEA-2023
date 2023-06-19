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


const int N=5;
const double T=60;
const double Tr=286e-6; const double er_Tr=27e-6;


double dist(int prateleira) {return 0.0254*(0.25+0.375*(prateleira-1));}
double Ncorrect(double N) {return -N*T/(N*Tr-T);}
double er_Ncorrect(double N, double er_N)
{
    return sqrt((N*N*N*N*Tr*Tr+N*N*N*N*er_Tr*er_Tr*T*T+er_N*er_N*T*T*T*T)/
                ((N*Tr-T)*(N*Tr-T)*(N*Tr-T)*(N*Tr-T)));
}

int main()
{
    

    double countsM[N]=
    {
        (3062+3045)/2,
        (1910+1955)/2,
        (1360+1332)/2,
        (959+970)/2,
        (768+772)/2
    };
    double er_countsM[N]=
    {
        (55+55)/2,
        (44+44)/2,
        (37+36)/2,
        (31+31)/2,
        (28+28)/2
    };
    double counts[N]; double er_counts[N];

    double dists[N]; double er_dists[N];
    for (int i = 0; i < 5; i++) 
    {
        dists[i] = dist(i+1); er_dists[i] = 2e-3;
        counts[i] = Ncorrect(countsM[i]); er_counts[i] = er_Ncorrect(countsM[i], er_countsM[i]);
        std::cout << "Contagem " << i+1 << ": " << counts[i] << " \\\pm " << er_counts[i] <<std::endl;
        std::cout << "Distância " << i+1 << ": " << dists[i] << std::endl;
    }
    

    
    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);
    gStyle->SetOptFit();

    auto graf = new TGraphErrors(N, dists, counts, er_dists, er_counts);
    graf->SetMarkerStyle(3);

    graf -> SetMarkerStyle(106);
    graf -> SetTitle("Contagens em funcao da distancia com a placa de aluminio");
    graf -> GetXaxis() -> SetTitle("Distancia (m)");
    graf -> GetXaxis() -> SetRangeUser(0,50e-3);
    graf -> GetYaxis() -> SetTitle("Contagens corrigidas");
    graf -> SetStats(1);
    

    // TF1 *f1 = new TF1("f1", "[0]/(x*x)+[1]", 0, 50e-3);  //para 1ºajuste
    TF1 *f1 = new TF1("f1", "[0]*(1-(x+[1])/sqrt((x+[1])^2+[2]))+[3]", 0, 50e-3); //para 2ºajuste
    f1->SetParLimits(0,0,1000000);
    f1->SetParLimits(1,0,1000000);
    f1->SetParLimits(2,0,1000000); //para 2ºajuste
    f1->SetLineColor(kRed);
    // f1->SetParNames("A","B");  //para 1ºajuste
    f1->SetParNames("A","d","C","B"); //para 2ºajuste


    graf->Fit(f1,"R");
    graf->Draw("AP");
    c.Update();

    // c.SaveAs("GaygerComAl.png");  //para 1ºajuste
    c.SaveAs("GaygerComAlFinal.png"); //para 2ºajuste
    c.WaitPrimitive();
    App.Run();

}
