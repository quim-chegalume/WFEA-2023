#include "TStyle.h"
#include "TAxis.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int N = 1024; const int Maria = 0; const int Manel = 200;

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
                cout << valor << endl;
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
    string nome = "4C_CESIO.txt";

    ReadFileMCA(nome, channels, contagens, ROIs);

    TApplication App("A", nullptr, nullptr);

    // Canvas onde é desenhado o gráfico
    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);
    
    // Criar o objeto 
    TH1F *h1 = new TH1F("h1", "histograma", Manel-Maria, Maria, Manel);

    for (int i = 1; i < N; i++)
    {
        cout << channels[i] << contagens[i] << endl;
        h1->Fill(channels[i], contagens[i]);
    }

    c.Update();
    h1->Draw();
    c.SaveAs("ex1.png");
    c.WaitPrimitive();

    App.Run();
}