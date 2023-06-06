#include "TStyle.h"
#include "TAxis.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TF1.h"
#include "TAxis.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int N = 1024;

void ReadFileMCA(string fname, double (&Chnl)[N], double (&Cnt)[1024], double (&ROI)[N])
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

double energy(double canl) {return 1.74992*canl+4637.77;}

int main()
{
    double channels[N]; double contagens[N]; double ROIs[N];
    string nome = "PIRO2AM5.ASC";

    ReadFileMCA(nome, channels, contagens, ROIs);


    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);
    
    // Criar o objeto 
    TH1F *h1 = new TH1F("Parametros", "Espetro de emissao alfa do americio", round(energy(1024)), 0, round(energy(1023)));

    for (int i = 1; i < N; i++)
    {
        h1->Fill(energy(i), contagens[i]);
    }
    h1->SetLineWidth(0);
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(1);
    h1->SetMarkerColor(13);

    //tres gaussianas dos picos
    TF1 *f1 = new TF1("f1", "gaus", 0, round(energy(1023)));
    f1->SetLineColor(kRed);
    
    TF1 *f2 = new TF1("f2", "gaus", 0, round(energy(1023)));
    f2->SetLineColor(kBlue);

    TF1 *f3 = new TF1("f3", "gaus", 0, round(energy(1023)));
    f3->SetLineColor(kGreen);

    //soma das tres
    TF1 *total = new TF1("total", "gaus(0) + gaus(3) + gaus(6)", 0, round(energy(1023)));
    total->SetLineColor(kBlack);
    total->SetLineWidth(4);
    total->SetLineStyle(9);
    total->SetParNames("1Const", "1Media", "1Sigma",
                       "2Const", "2Media", "2Sigma",
                       "3Const", "3Media", "3Sigma");

    //fits dos 3 picos
    h1->Fit(f1, "0W", "", round(energy(410)), round(energy(440)));
    h1->Fit(f2, "0W", "", round(energy(450)), round(energy(470)));
    h1->Fit(f3, "0W", "", round(energy(470)), round(energy(510)));
    
    //fit dos 3 picos somados
    double par[9];
    f1->GetParameters(&par[0]);
    f2->GetParameters(&par[3]);
    f3->GetParameters(&par[6]);
    total->SetParameters(par);
    h1->Fit(total, "0W", "", round(energy(410)), round(energy(510)));


    //eixos
    h1 ->GetXaxis()->SetRange(round(energy(410)),round(energy(510)));
    h1 ->GetXaxis()->SetTitle("Energia (KeV)");
    h1 ->GetYaxis()->SetRangeUser(0,1300);
    h1 ->GetYaxis()->SetTitle("Eventos");
    c.Update();
    h1->Draw("E1");
    f1->Draw("SAME"); f2->Draw("SAME"); f3->Draw("SAME"); total->Draw("SAME");
    c.SaveAs("alfaFinal.png");
    c.WaitPrimitive();

    App.Run();
}