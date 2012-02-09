
TString dir ="";
TFile *Sig = new TFile(dir+"eWPol_Signal_QCD.root");
TFile *Bkgd = new TFile(dir+"eWPol_Control_QCD.root");
TString saving = "/data1/Plots/LCMeeting/IDInv/MCqcd/MCqcd";
UInt_t r1 =5;


void () IDInversion2(){
 
   TCanvas *NAT_Ratio = NAtRatio();

 

}





TCanvas* NAtRatio(){

  TGraphErrors *NatSig = new TGraphErrors(6);
  TGraphErrors *NatCtrl = new TGraphErrors(6); 


 TH1D *Sig0 = ((TH1D*)Sig->Get("kinplot/AlphaT_0"))->Clone();
 TH1D *Ctrl0= ((TH1D*)Bkgd->Get("kinplot/AlphaT_0"))->Clone();

 TH1D *Sig50 = ((TH1D*)Sig->Get("kinplot_afterHT_50/AlphaT_0"))->Clone();
 TH1D *Ctrl50= ((TH1D*)Bkgd->Get("kinplot_afterHT_50/AlphaT_0"))->Clone();

 TH1D *Sig100 = ((TH1D*)Sig->Get("kinplot_afterHT_100/AlphaT_0"))->Clone();
 TH1D *Ctrl100= ((TH1D*)Bkgd->Get("kinplot_afterHT_100/AlphaT_0"))->Clone();

 TH1D *Sig150 = ((TH1D*)Sig->Get("kinplot_afterHT_150/AlphaT_0"))->Clone();
 TH1D *Ctrl150= ((TH1D*)Bkgd->Get("kinplot_afterHT_150/AlphaT_0"))->Clone();

 TH1D *Sig200 = ((TH1D*)Sig->Get("kinplot_afterHT_200/AlphaT_0"))->Clone();
 TH1D *Ctrl200= ((TH1D*)Bkgd->Get("kinplot_afterHT_200/AlphaT_0"))->Clone();

 TH1D *Sig250 = ((TH1D*)Sig->Get("kinplot_afterHT_250/AlphaT_0"))->Clone();
 TH1D *Ctrl250= ((TH1D*)Bkgd->Get("kinplot_afterHT_250/AlphaT_0"))->Clone();

 

 NatSig->SetPoint(0,0.,(Sig0->Integral(55,300)/Sig0->Integral(0,54)));
 NatSig->SetPoint(1,50.,(Sig50->Integral(55,300)/Sig50->Integral(0,54)));
 NatSig->SetPoint(2,100.,(Sig100->Integral(55,300)/Sig100->Integral(0,54)));
 NatSig->SetPoint(3,150.,(Sig150->Integral(55,300)/Sig150->Integral(0,54)));
 NatSig->SetPoint(4,200.,(Sig200->Integral(55,300)/Sig200->Integral(0,54)));
 NatSig->SetPoint(5,250.,(Sig250->Integral(55,300)/Sig250->Integral(0,54)));



 NatSig->SetPointError(0,1.,sqrt(Sig0->Integral(55,300)/Sig0->Integral(0,54)));
 NatSig->SetPointError(1,1.,sqrt(Sig50->Integral(55,300)/Sig50->Integral(0,54)));
 NatSig->SetPointError(2,1.,sqrt(Sig100->Integral(55,300)/Sig100->Integral(0,54)));
 NatSig->SetPointError(3,1.,sqrt(Sig150->Integral(55,300)/Sig150->Integral(0,54)));
 NatSig->SetPointError(4,1.,sqrt(Sig200->Integral(55,300)/Sig200->Integral(0,54)));
 NatSig->SetPointError(5,1.,sqrt(Sig250->Integral(55,300)/Sig250->Integral(0,54)));

 NatCtrl->SetPoint(0,0.,(Ctrl0->Integral(55,300)/Ctrl0->Integral(0,54)));
 NatCtrl->SetPoint(1,50.,(Ctrl50->Integral(55,300)/Ctrl50->Integral(0,54)));
 NatCtrl->SetPoint(2,100.,(Ctrl100->Integral(55,300)/Ctrl100->Integral(0,54)));
 NatCtrl->SetPoint(3,150.,(Ctrl150->Integral(55,300)/Ctrl150->Integral(0,54)));
 NatCtrl->SetPoint(4,200.,(Ctrl200->Integral(55,300)/Ctrl200->Integral(0,54)));
 NatCtrl->SetPoint(5,250.,(Ctrl250->Integral(55,300)/Ctrl250->Integral(0,54)));



 NatCtrl->SetPointError(0,1.,sqrt(Ctrl0->Integral(55,300)/Ctrl0->Integral(0,54)));
 NatCtrl->SetPointError(1,1.,sqrt(Ctrl50->Integral(55,300)/Ctrl50->Integral(0,54)));
 NatCtrl->SetPointError(2,1.,sqrt(Ctrl100->Integral(55,300)/Ctrl100->Integral(0,54)));
 NatCtrl->SetPointError(3,1.,sqrt(Ctrl150->Integral(55,300)/Ctrl150->Integral(0,54)));
 NatCtrl->SetPointError(4,1.,sqrt(Ctrl200->Integral(55,300)/Ctrl200->Integral(0,54)));
 NatCtrl->SetPointError(5,1.,sqrt(Ctrl250->Integral(55,300)/Ctrl250->Integral(0,54)));




  gROOT->SetStyle("Plain");


TCanvas* c = new TCanvas("NalphaT_Ratio","NAlphaT_Ratio");
 c->SetLogy();
 TLegend *leg = new TLegend(0.5,0.8,0.99,0.99);
 leg->SetFillColor(0);
 leg->AddEntry(NatSig,"Selected Events","P");
 leg->AddEntry(NatCtrl,"Anti-selected events","P");
 NatSig->SetMarkerColor(kRed);
 NatSig->SetMarkerStyle(kFullCircle);
 NatSig->SetLineColor(kRed);
 NatSig->SetLineWidth(2);
 NatCtrl->SetMarkerColor(kBlue);
 NatCtrl->SetMarkerStyle(kFullCircle);
 NatCtrl->SetLineColor(kBlue);
 NatCtrl->SetLineWidth(2);
 NatCtrl->Draw("APX");
 NatSig->Draw("PX");



 //NatSig->Fit("pol1");
 NatCtrl->GetXaxis()->SetTitle("HT Cut [GeV]");
 NatCtrl->GetYaxis()->SetTitle("#frac{N(#alpha_{T}>0.55)}{N(#alpha_{T}<0.55)}");

 NatCtrl->GetXaxis()->SetTitle("HT Cut [GeV]");
 NatCtrl->GetYaxis()->SetRangeUser(0.0005,0.5);
 NatCtrl->SetTitle();
 leg->Draw("SAME");

 c->Update();
 c->SaveAs(saving+"NAlphaTRatio_plot.png");
 return c;
}

TCanvas* Com(TString plot,TString plot_dir,UInt_t rbin, TString xtitle, Double_t max, TString title){
  gROOT->SetStyle("Plain");
  gStyle->SetTitleFontSize(0.07);
 TH1D *Sig = ((TH1D*)Sig->Get(plot_dir+"/"+plot))->Clone();
 TH1D *Bkgd= ((TH1D*)Bkgd->Get(plot_dir+"/"+plot))->Clone();
 Sig->Rebin(rbin);
 Bkgd->Rebin(rbin);
 Sig->Scale(1/(Sig->Integral()));
 Bkgd->Scale(1/(Bkgd->Integral()));
 //TLine *li =new TLine(0.55,0.,0.55,100000);
TCanvas* c = new TCanvas(plot_dir+plot,plot_dir+plot);
 c->SetLogy();

 TLegend *leg = new TLegend(0.5,0.8,0.99,0.99);
 leg->SetFillColor(0);
 leg->AddEntry(Sig,"Selected events","L");
 leg->AddEntry(Bkgd,"Anti-selected events","L");
 Sig->SetLineColor(kRed);
 Sig->SetLineWidth(2);
 Bkgd->SetLineColor(kBlue);
 Bkgd->SetLineWidth(2);
 Sig->Draw("EHIST");
 Bkgd->Draw("HISTSAME");
 leg->Draw("SAME");
 //      li->Draw("SAME");
 Sig->SetTitle(title);

Sig->SetStats(kFALSE);
 Sig->GetXaxis()->SetTitle(xtitle);
 if (max == 999999){

 }
 else{
   Sig->GetXaxis()->SetRangeUser(0.2,max);}
 Sig->GetYaxis()->SetTitle("");
 c->Update();
 c->SaveAs(saving+"IDinv_Delta_"+plot_dir+plot+".png");
 return c;


}





