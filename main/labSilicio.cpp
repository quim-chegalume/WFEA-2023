#include "TStyle.h"
#include "TAxis.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
using namespace std;

const int N = 5;

void ReadFile(string fname, double (&t)[N], double (&A)[N])
    {
        fstream DataFile;
        DataFile.open(fname, ios::in);

        double time, amplitude;
        int ind = 0;
        while (DataFile >> time >> amplitude) {
            t[ind] = time;
            A[ind] = amplitude;
            ind++;
        }
        DataFile.close();
    }

int main()
{
    double channels[N]; double energies[N];
    string nome = "semicondutor_calibr.txt";

    ReadFile(nome, channels, energies);

    TApplication App("A", nullptr, nullptr);


    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);
    
    // Criar o objeto 
    TGraph *gr = new TGraph(N, channels, energies);
    //TGraph gr(nstep, x, y);

    // Colocar as informações sobre o FIT
    gStyle->SetOptFit(kTRUE);

    // Definir titulo e labels dos eixos
    gr->SetTitle("1ex TGraph");
    gr->GetXaxis()->SetTitle("Canais");
    gr->GetYaxis()->SetTitle("Energias"); 

    // Definições Estéticas!
    gr->SetMarkerColor(kRed);
    gr->SetMarkerSize(0.7);
    gr->SetMarkerStyle(8);

    c.Update();
    gr->Draw("ACP");
    c.SaveAs("ex1.png");
    c.WaitPrimitive();

    App.Run();

}