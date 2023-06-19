#include "TStyle.h"
#include "TAxis.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TF1.h"
#include "TLine.h"
#include "TMath.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int N = 1024;


int main() {

    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);
    
    // Criar o objeto 
    TH1F *h1 = new TH1F("h1", "Espetro Energia Talio", 12, 748.25, 946.25);


    double x_bins[10] = {
        770,
        790,
        810,
        820,
        840,
        860,
        870,
        890,
        900,
        920
    };

    double y_bins[10] = {
        2,
        3,
        6,
        10,
        12,
        5,
        6,
        3,
        2,
        1
    };


    



   

    
    
    for (int i = 0; i < 10; i++)
    {
        h1->Fill(x_bins[i], y_bins[i]);
    }
    h1->SetLineWidth(0);
    

    
    //h1 -> GetYaxis() -> SetRange(0, 3000);
    
    
    TF1 *f1 = new TF1("f1", "gaus", 755, 940);
    f1->SetLineColor(1);
    


    TF1 *f2 = new TF1("f2", "TMath::Poisson(x,[0])", 755, 940);
    f2->SetLineColor(2);

    h1->Fit(f1, "WR");
    h1->Fit(f2, "WR+");
    
    double par[6];
    f1->GetParameters(&par[0]);
    f2->GetParameters(&par[3]);
  
    h1 ->SetMarkerStyle(5);
    h1 -> SetMarkerColor(4);

    h1 -> GetXaxis() -> SetTitle("Numero Contagens Corrigidas");
    h1 -> GetYaxis() -> SetTitle("Frequencia Absoluta");

    c.Update();
    h1->Draw();
    f1 -> Draw("same");
    f2 -> Draw("same");
    c.SaveAs("bins.png");
    c.WaitPrimitive();
    
    App.Run();
    
}