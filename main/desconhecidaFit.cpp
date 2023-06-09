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

double energy(double canl) {return 1.701*canl-2.318;}

int main()
{
    double channels[N]; double contagens[N]; double ROIs[N];
    string nome = "GPIRODE.ASC";

    ReadFileMCA(nome, channels, contagens, ROIs);

    double energias[N];
    double er_contagens[N];
    double er_energias[N]; fill_n(er_energias, N, 0.009);
    double er_canais[N]; fill_n(er_canais, N, 1);

    for (int i = 0; i < N; i++)
    {
        energias[i] = energy(channels[i]);
        er_contagens[i] = sqrt(contagens[i]);
    }
    

    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);
    
    // Criar o objeto 
    auto h1 = new TGraphErrors(N, energias, contagens, er_energias, er_contagens);
    h1->SetMarkerStyle(1); h1->SetMarkerSize(1);
    h1->SetTitle("Espetro da fonte desconhecida com ajustes");


    TF1 *f1 = new TF1("f1", "gaus", energy(10), energy(25));
    f1->SetLineColor(3);
    
    TF1 *f6 = new TF1("f6", "gaus", energy(30),energy(57));
    f6 -> SetLineColor(7);
    
    TF1 *f7 = new TF1("f7", "gaus", energy(60), energy(90));
    f7 -> SetLineColor(11);
    
    TF1 *f2 = new TF1("f2", "gaus", energy(100), energy(115));
    f2->SetLineColor(5);
    
    TF1 *f3 = new TF1("f3", "gaus", energy(240), energy(270));
    f3->SetLineColor(2);

    TF1 *f4 = new TF1("f4", "gaus", energy(279), energy(290));
    f4->SetLineColor(4);

    TF1 *f5 = new TF1("f5", "gaus", energy(340), energy(400));
    f5->SetLineColor(6);




    h1->Fit(f1, "0WR");
    auto *f1C = new TF1(*f1);
    f1C->SetRange(0,energy(1023));
    f1C->SetLineStyle(9);f1C->SetLineWidth(2);
    
    h1->Fit(f6, "0WR+");
    auto *f6C = new TF1(*f6);
    f6C->SetRange(0,energy(1023));
    f6C->SetLineStyle(9);f6C->SetLineWidth(2);

    h1->Fit(f7, "0WR+");
    auto *f7C = new TF1(*f7);
    f7C->SetRange(0,energy(1023));
    f7C->SetLineStyle(9);f7C->SetLineWidth(2);

    h1->Fit(f2, "0WR+");
    auto *f2C = new TF1(*f2);
    f2C->SetRange(0,energy(1023));
    f2C->SetLineStyle(9);f2C->SetLineWidth(2);

    
    h1->Fit(f3, "0WR+");
    auto *f3C = new TF1(*f3);
    f3C->SetRange(0,energy(1023));
    f3C->SetLineStyle(9);f3C->SetLineWidth(2);

    h1->Fit(f4, "0WR+");
    auto *f4C = new TF1(*f4);
    f4C->SetRange(0,energy(1023));
    f4C->SetLineStyle(9);f4C->SetLineWidth(2);

    h1->Fit(f5, "0WR+");
    auto *f5C = new TF1(*f5);
    f5C->SetRange(0,energy(1023));
    f5C->SetLineStyle(9);f5C->SetLineWidth(2);

    //eixos
    h1 ->GetXaxis()->SetRangeUser(0,energy(420));
    h1 ->GetXaxis()->SetTitle("Energia (KeV)");
    // h1 ->GetYaxis()->SetRangeUser(10,10e4);
    h1 ->GetYaxis()->SetTitle("Contagens");
    
    // c.SetLogy();
    c.Update();
    h1->Draw("AP");
    f1->Draw("Same");f2->Draw("Same");f3->Draw("Same");f4->Draw("Same");
    f5->Draw("Same");f6->Draw("Same");f7->Draw("Same");
    // f1C->Draw("Same");f2C->Draw("Same");f3C->Draw("Same");
    // f4C->Draw("Same");f5C->Draw("Same");f6C->Draw("Same");f7C->Draw("Same");
    c.SaveAs("FitDes.png");
    c.WaitPrimitive();

    App.Run();
}