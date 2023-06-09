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
    auto h1 = new TGraphErrors(N, channels, contagens, er_canais, er_contagens);
    h1->SetMarkerStyle(1); h1->SetMarkerSize(0.1);
    h1->SetTitle("Espetro MCA da fonte desconhecida");


    // TF1 *f1 = new TF1("f1", "gaus", 0, round(energy(1023)));
    // f1->SetLineColor(kRed);f1->SetLineWidth(3);
    
    // TF1 *f2 = new TF1("f2", "gaus", 0, round(energy(1023)));
    // f2->SetLineColor(kBlue);f2->SetLineWidth(3);



    // h1->Fit(f1, "W", "", 179, 217);
    // auto *f1C = new TF1(*f1);
    // f1C->SetLineStyle(9);f1C->SetLineWidth(2);

    // h1->Fit(f2, "W+", "", 440, 500);
    // auto *f2C = new TF1(*f2);
    // f2C->SetLineStyle(9);f2C->SetLineWidth(2);

    //eixos
    h1 ->GetXaxis()->SetRangeUser(0,420);
    h1 ->GetXaxis()->SetTitle("Canal");
    h1 ->GetYaxis()->SetRangeUser(10,10e4);
    h1 ->GetYaxis()->SetTitle("Contagens");
    
    c.SetLogy();
    c.Update();
    h1->Draw("AP");
    // f1C->Draw("Same");f2C->Draw("Same");
    c.SaveAs("mcaDesLog.png");
    c.WaitPrimitive();

    App.Run();
}