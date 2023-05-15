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


const int N = 50;

void ReadFile(string fname, double (&A)[N])
    {
        fstream DataFile;
        DataFile.open(fname, ios::in);
        double amplitude;
        int ind = 0;
        for (int i = 1; i < N; i++)
        {
        DataFile >> amplitude;
        A[i] = amplitude;
        }
        DataFile.close();
    }

int main()
{

    double amps[N];
    string file="LAB2_dados.txt";

    ReadFile(file, amps);

    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);
    
    // Criar o objeto 
    TH1F *h1 = new TH1F("h1", "histograma", 20, 0, 10);

    for (int i = 1; i < N; i++)
    {
        h1->Fill(amps[i]);
    }

    c.Update();
    h1->Draw();
    c.SaveAs("ex1.png");
    c.WaitPrimitive();

    App.Run();

}