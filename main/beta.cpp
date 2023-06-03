#include "TStyle.h"
#include "TAxis.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TF1.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int N = 1024;

void ReadFileMCA(string fname, double (&Chnl)[N], double (&Cnt)[N], double (&ROI)[N])
    {
        //abre ficheiro e vê se existe
        fstream DataFile;
        DataFile.open(fname, ios::in);

        if(!DataFile) 
        {
            cout << "ERROR OPENING FILE!!! EXITING.." << endl;
        }

        //caga nas primeiras linhas de palha
        string s;
        for (int i = 0; i < 5; i++) { getline(DataFile, s);}
        
        //le o ficheiro
        string linha;
        int ind=0;
        
        while (getline(DataFile, linha)) 
        {
            istringstream iss(linha);

            string valor;
            vector<string> valores;
            while (getline(iss, valor, ','))
            {
                valores.push_back(valor);
            }
            double canal=stod(valores[0]);
            double contagem=stod(valores[1]);
            double nrROI=stod(valores[2]);
            Chnl[ind]=canal;
            Cnt[ind]=contagem;
            ROI[ind]=nrROI;
            
            ind++;
        }
        DataFile.close();
    }

int main()
{
    double channels[N]; double contagens[N]; double ROIs[N];
    string nome = "PIROBI.ASC";

    ReadFileMCA(nome, channels, contagens, ROIs);

    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);
    
    // Criar o objeto 
    TH1F *h1 = new TH1F("h1", "histograma", 1024, 0, 1023);

    for (int i = 1; i < N; i++)
    {
        cout << channels[i] << contagens[i] << endl;
        h1->Fill(channels[i], contagens[i]);
    }
    h1->SetLineWidth(0);
    h1->SetMarkerStyle(5);

    /**
    TF1 *f1 = new TF1("f1", "gaus", 420, 440);
    f1->SetLineColor(kRed);
    
    TF1 *f2 = new TF1("f2", "gaus", 450, 470);
    f2->SetLineColor(kBlue);

    TF1 *f3 = new TF1("f3", "gaus", 470, 510);
    f3->SetLineColor(kPink);

    TF1 *total = new TF1("total", "gaus(0) + gaus(3) + gaus(6)", 410, 510);
    total->SetLineColor(kBlack);

    h1->Fit(f1, "WR");
    h1->Fit(f2, "WR+");
    h1->Fit(f3, "WR+");
    double par[9];
    f1->GetParameters(&par[0]);
    f2->GetParameters(&par[3]);
    f3->GetParameters(&par[6]);
    total->SetParameters(par);

    h1->Fit(total, "WR+");
    */

    c.Update();
    h1->Draw();
    c.SaveAs("bi.png");
    c.WaitPrimitive();

    App.Run();
}