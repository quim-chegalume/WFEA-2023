#include "TStyle.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"

int main()
{
    double step = 0.005;
    int nstep = int(7 / step);
    
    double_t x[nstep];
    double_t y[nstep];

    // Criar pontos (x, y) para o exemplo :)
    for (int i = 1; i < nstep; i++)
    {
        x[i] = i * step;
        y[i] = 2 * sin(x[i]) * tanh(x[i]) * log(x[i]);
    }

    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);
    
    // Criar o objeto 
    TGraph *gr = new TGraph(nstep, x, y);
    //TGraph gr(nstep, x, y);

    // Colocar as informações sobre o FIT
    gStyle->SetOptFit(kTRUE);

    // Definir titulo e labels dos eixos
    gr->SetTitle("1ex TGraph");
    gr->GetXaxis()->SetTitle("Eixo X");
    gr->GetYaxis()->SetTitle("podemos escrever em LaTeX: #gamma #sum #hat{o}"); 

    // Definições Estéticas!
    gr->SetMarkerColor(kRed);
    gr->SetMarkerSize(0.7);
    gr->SetMarkerStyle(8);

    c.Update();
    gr->Draw("ACP");
    c.SaveAs("ex1.png");
    c.WaitPrimitive();

    
    return 0;
}