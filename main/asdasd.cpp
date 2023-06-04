#include "ReadData.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TRootCanvas.h"
#include "TApplication.h"
#include "TGraphErrors.h"


int main()
{
    ReadData Data1("PET1.txt");
    ReadData Data2("PET2.txt");
    ReadData Data3("PET3.txt");
    auto data1 = Data1.GetData();
    auto data2 = Data2.GetData();
    auto data3 = Data3.GetData();

    // Data 1
    int n1 = data1.size();
    double_t x1[n1];
    double_t y1[n1];
    double_t ex1[n1];
    double_t ey1[n1];

    for (int i = 0; i < n1; i++)
    {
        x1[i] = data1[i][0];
        y1[i] = data1[i][1];
        ex1[i] = data1[i][2];
        ey1[i] = data1[i][3];
    }

    // Data 2
    int n2 = data2.size();
    double_t x2[n2];
    double_t y2[n2];
    double_t ex2[n2];
    double_t ey2[n2];

    for (int i = 0; i < n2; i++)
    {
        x2[i] = data2[i][0];
        y2[i] = data2[i][1];
        ex2[i] = data2[i][2];
        ey2[i] = data2[i][3];
    }

    // Data 2
    int n3 = data3.size();
    double_t x3[n3];
    double_t y3[n3];
    double_t ex3[n3];
    double_t ey3[n3];

    for (int i = 0; i < n3; i++)
    {
        x3[i] = data3[i][0];
        y3[i] = data3[i][1];
        ex3[i] = data3[i][2];
        ey3[i] = data3[i][3];
    }

    TGraphErrors *gr1 = new TGraphErrors(n1, x1, y1, ex1, ey1);
    gr1->SetMarkerSize(2);
    gr1->SetMarkerStyle(8);
    gr1->SetMarkerColor(kRed);

    TGraphErrors *gr2 = new TGraphErrors(n2, x2, y2, ex2, ey2);
    gr2->SetMarkerSize(2.5);
    gr2->SetMarkerStyle(39);
    gr2->SetMarkerColor(kBlue);

    TGraphErrors *gr3 = new TGraphErrors(n3, x3, y3, ex3, ey3);
    gr3->SetMarkerSize(2.5);
    gr3->SetMarkerStyle(43);
    gr3->SetMarkerColor(kGreen);

    gr1->GetXaxis()->SetLimits(-41, 41);

    TCanvas c("canvas", "grafico", 200, 10, 1920, 1080);

    TF1 *f1 = new TF1("f1", "gaus(0)", -20, 20);
    f1->SetParameters(150, 0.1, 1);
    f1->SetLineColor(kRed);
    
    TF1 *f2 = new TF1("f2", "gaus(0)", -40, 0);
    f2->SetParameters(140, -20, 5);
    f2->SetLineColor(kBlue);
    f2->SetParLimits(0, 130, 150);
    
    TF1 *f3 = new TF1("f3", "gaus(0)", 0, 40);
    f3->SetParameters(150, 20, 1);
    f3->SetLineColor(kGreen);
    
    gr1->Fit(f1, "R");
    gr2->Fit(f2);
    gr3->Fit(f3);

    gr1->Draw("AP");
    gr2->Draw("same P");
    gr3->Draw("same P r");
    c.Update();
    c.SaveAs("MultiFit.png");
    return 0;
}