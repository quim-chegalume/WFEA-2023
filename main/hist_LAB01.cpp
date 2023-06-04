#ifdef __CLING__
#pragma cling optimize(0)
#endif
void canvas()
{
//=========Macro generated from canvas: canvas/grafico
//=========  (Thu May 11 12:57:32 2023) by ROOT version 6.28/02
   TCanvas *canvas = new TCanvas("canvas", "grafico",74,64,1846,1016);
   canvas->SetHighLightColor(2);
   canvas->Range(-1.362712,-2.69319,11.13898,20.94968);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetTopMargin(0.08669354);
   canvas->SetBottomMargin(0.1139113);
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   
   TH1F *h1__1 = new TH1F("h1__1","histograma",20,0,10);
   h1__1->SetBinContent(4,1);
   h1__1->SetBinContent(5,4);
   h1__1->SetBinContent(6,6);
   h1__1->SetBinContent(7,18);
   h1__1->SetBinContent(8,10);
   h1__1->SetBinContent(9,8);
   h1__1->SetBinContent(11,2);
   h1__1->SetBarWidth(0.97);
   h1__1->SetEntries(49);
   h1__1->SetContour(20);
   h1__1->SetContourLevel(0,0);
   h1__1->SetContourLevel(1,0.9);
   h1__1->SetContourLevel(2,1.8);
   h1__1->SetContourLevel(3,2.7);
   h1__1->SetContourLevel(4,3.6);
   h1__1->SetContourLevel(5,4.5);
   h1__1->SetContourLevel(6,5.4);
   h1__1->SetContourLevel(7,6.3);
   h1__1->SetContourLevel(8,7.2);
   h1__1->SetContourLevel(9,8.1);
   h1__1->SetContourLevel(10,9);
   h1__1->SetContourLevel(11,9.9);
   h1__1->SetContourLevel(12,10.8);
   h1__1->SetContourLevel(13,11.7);
   h1__1->SetContourLevel(14,12.6);
   h1__1->SetContourLevel(15,13.5);
   h1__1->SetContourLevel(16,14.4);
   h1__1->SetContourLevel(17,15.3);
   h1__1->SetContourLevel(18,16.2);
   h1__1->SetContourLevel(19,17.1);
   
   TPaveStats *ptstats = new TPaveStats(0.6995662,0.7409274,0.8996746,0.9012097,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(22);
   TText *ptstats_LaTex = ptstats->AddText("h1");
   ptstats_LaTex->SetTextSize(0.02457661);
   ptstats_LaTex = ptstats->AddText("Entries = 49     ");
   ptstats_LaTex = ptstats->AddText("Mean  =  3.351 #pm 0.09547");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.6683 #pm 0.06751");
   ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf = 5.388 / 5");
   ptstats_LaTex = ptstats->AddText("Sigma    = 0.5914 ");
   ptstats->SetOptStat(2211);
   ptstats->SetOptFit(101);
   ptstats->Draw();
   h1__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(h1__1);
   
   TF1 *PrevFitTMP2 = new TF1("PrevFitTMP","gaus",1,5, TF1::EAddToList::kNo);
   PrevFitTMP2->SetFillColor(19);
   PrevFitTMP2->SetFillStyle(0);
   PrevFitTMP2->SetLineColor(2);
   PrevFitTMP2->SetLineWidth(2);
   PrevFitTMP2->SetChisquare(5.388318);
   PrevFitTMP2->SetNDF(5);
   PrevFitTMP2->GetXaxis()->SetLabelFont(42);
   PrevFitTMP2->GetXaxis()->SetTitleOffset(1);
   PrevFitTMP2->GetXaxis()->SetTitleFont(42);
   PrevFitTMP2->GetYaxis()->SetLabelFont(42);
   PrevFitTMP2->GetYaxis()->SetTitleFont(42);
   PrevFitTMP2->SetParameter(0,16.61296);
   PrevFitTMP2->SetParError(0,0);
   PrevFitTMP2->SetParLimits(0,12.1979,12.1979);
   PrevFitTMP2->SetParameter(1,3.345745);
   PrevFitTMP2->SetParError(1,0);
   PrevFitTMP2->SetParLimits(1,3.5499,3.5499);
   PrevFitTMP2->SetParameter(2,0.591428);
   PrevFitTMP2->SetParError(2,0.08253285);
   PrevFitTMP2->SetParLimits(2,0,6.15736);
   PrevFitTMP2->SetParent(h1__1);
   h1__1->GetListOfFunctions()->Add(PrevFitTMP2);
   h1__1->SetFillColor(4);
   h1__1->SetFillStyle(3001);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h1__1->SetLineColor(ci);
   h1__1->SetLineWidth(2);
   h1__1->GetXaxis()->SetLabelFont(42);
   h1__1->GetXaxis()->SetTitleOffset(1);
   h1__1->GetXaxis()->SetTitleFont(42);
   h1__1->GetYaxis()->SetLabelFont(42);
   h1__1->GetYaxis()->SetTitleFont(42);
   h1__1->GetZaxis()->SetLabelFont(42);
   h1__1->GetZaxis()->SetTitleOffset(1);
   h1__1->GetZaxis()->SetTitleFont(42);
   h1__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.415705,0.9345161,0.584295,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("histograma");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
