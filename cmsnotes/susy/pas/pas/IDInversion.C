TString dir = "";
TFile *Sig = new TFile(dir+"eWPol_Signal_QCD.root");
TFile *Bkgd = new TFile(dir+"eWPol_Control_QCD.root");



TString saving = "/data1/Plots/LCMeeting/IDInv/MCqcd/MCqcd";
UInt_t r1 =5;


void () IDInversion(){
  /* TString dir = "alphat_plots/";
  TString refplot = "AlphaT_binHT_100";
  TString plot = "AlphaT_binHT_200";
 TH1D *S_Ref = ((TH1D*)Sig->Get(dir+refplot))->Clone();
 TH1D *S_Sig = ((TH1D*)Sig->Get(dir+plot))->Clone();

 TCanvas* c = new TCanvas("1","1");
 TLegend *leg = new TLegend(0.5,0.8,0.99,0.99);
 leg->SetFillColor(0);
 leg->AddEntry(S_Ref,"Selected events_HT<100","L");
 leg->AddEntry(S_Sig,"Selected events_100<HT<150","L");
 S_Sig->SetLineColor(kRed);
 S_Sig->SetLineWidth(2);
 S_Ref->SetLineColor(kBlue);
 S_Ref->SetLineWidth(2);
 S_Sig->Draw("E");
 S_Ref->Draw("SAME");
 leg->Draw("SAME");
 c->Update();

 TH1D *AS_Ref = ((TH1D*)Bkgd->Get(dir+refplot))->Clone();

 TH1D *AS_Sig = ((TH1D*)Bkgd->Get(dir+plot))->Clone();

 TCanvas* c2 = new TCanvas("2","2");
 TLegend *leg = new TLegend(0.5,0.8,0.99,0.99);
 leg->SetFillColor(0);
 leg->AddEntry(AS_Ref,"anit-Selected events_HT<100","L");
 leg->AddEntry(AS_Sig,"anit-Selected events_100<HT<150","L");
 AS_Sig->SetLineColor(kRed);
 AS_Sig->SetLineWidth(2);
 AS_Ref->SetLineColor(kBlue);
 AS_Ref->SetLineWidth(2);
 AS_Sig->Draw("E");
 AS_Ref->Draw("SAME");
 leg->Draw("SAME");
 c->Update();
  */
 //AAS_Sig->Divide(AS_Ref);


  //  TCanvas *HT = Com("SumEtall","before_ComPlots/",2,"HT [GeV]",800);
  //  TCanvas *MHT = Com("MHTall","before_ComPlots/",2,"MHT [GeV]",400);
  //  TCanvas *JetMult = Com("JetMultiplicity","before_ComPlots/",1,"# of jets",999999);
  //  TCanvas *JetMult = Com("JetMultiplicity","before_ComPlots/",1,"# of jets",999999);
  // TCanvas *JetPt = Com("JetPtall","before_ComPlots/",1,"Jet p_{T} [GeV]",200);


  //  TCanvas *JetEta = Com("JetEtaall","before_ComPlots/",1,"Jet #eta",5.);

  //  TCanvas *JetMHTdPhi = Com("JetMHTdPhiall","before_ComPlots/",1,"Jet MHT #Delta #phi",999999);
  
  
  // TCanvas *aT_nojetcut = Com("AlphaT_0","before_kinplot",1,"AlphaT",1.,"HT > ");
  /*
   TCanvas *aT_jetcut = Com("AlphaT_0","kinplot",1,"AlphaT",1.,"");
  TCanvas *aT_HTcut50 = Com("AlphaT_0","kinplot_afterHT_50",1,"AlphaT",1.,"HT > 50"); 
 TCanvas *aT_HTcut100 = Com("AlphaT_0","kinplot_afterHT_100",1,"AlphaT",1.,"HT > 100");
 TCanvas *aT_HTcut150 = Com("AlphaT_0","kinplot_afterHT_150",1,"AlphaT",1.,"HT > 150");
 TCanvas *aT_HTcut200 = Com("AlphaT_0","kinplot_afterHT_200",1,"AlphaT",1.,"HT > 200");
 TCanvas *aT_HTcut250 = Com("AlphaT_0","kinplot_afterHT_250",1,"AlphaT",1.,"HT > 250");
 TCanvas *aT_HTcut300 = Com("AlphaT_0","kinplot_afterHT_300",1,"AlphaT",1.,"HT > 300");
 TCanvas *aT_HTcut350 = Com("AlphaT_0","kinplot_afterHT_350",1,"AlphaT",1.,"HT > 350");
  */
  //TCanvas *MinDPhi = Com("MinDPhi_0","before_kinplot/",1,"Min DPhi",999999);
  //TCanvas *MinDEt = Com("MinDEt_0","before_kinplot/",1,"MinDEt",999999);


  //TCanvas *NAT = NAt();
   TCanvas *NAT_Ratio = NAtRatio();

   /*
 TCanvas *100over50 =rogue("AlphaT_binHT_100","#frac{No.Events(100<HT<150)}{No.Events(HT<100)}");
 TCanvas *150over50 =rogue("AlphaT_binHT_150","#frac{No.Events(150<HT<200)}{No.Events(HT<100)}");
 TCanvas *200over50 =rogue("AlphaT_binHT_200","#frac{No.Events(200<HT<250)}{No.Events(HT<100)}");
   */

}

TCanvas* rogue(TString plot,TString ytitle){
  TString dir = "alphat_plots/";
  TString refplot = "AlphaT_binHT_50";

 TH1D *S_Ref = ((TH1D*)Sig->Get(dir+refplot))->Clone();
 TH1D *S_Sig = ((TH1D*)Sig->Get(dir+plot))->Clone();
S_Sig->Divide(S_Ref);

 TH1D *AS_Ref = ((TH1D*)Bkgd->Get(dir+refplot))->Clone();
 TH1D *AS_Sig = ((TH1D*)Bkgd->Get(dir+plot))->Clone();
 AS_Sig->Divide(AS_Ref);

 S_Sig->Rebin(2);
 AS_Sig->Rebin(2);
 gROOT->SetStyle("Plain");
 gStyle->SetTitleFontSize(0.07);



 TCanvas* c = new TCanvas(plot,plot);


 TLegend *leg = new TLegend(0.5,0.8,0.99,0.99);
 leg->SetFillColor(0);
 leg->AddEntry(S_Sig,"Selected events","L");
 leg->AddEntry(AS_Sig,"Anti-selected events","L");
 S_Sig->SetLineColor(kRed);
 S_Sig->SetLineWidth(2);
 AS_Sig->SetLineColor(kBlue);
 AS_Sig->SetLineWidth(2);
 S_Sig->Draw("E");
 AS_Sig->Draw("SAME");
 leg->Draw("SAME");
 //      li->Draw("SAME");
 S_Sig->SetTitle();

S_Sig->SetStats(kFALSE);
// S->GetXaxis()->SetTitle(xtitle);
// if (max == 999999){

// }
/// else{
 S_Sig->GetXaxis()->SetRangeUser(0.2,1);
S_Sig->GetYaxis()->SetTitle(ytitle);
 c->Update();
 c->SaveAs(saving+"Ratio_Of_HTbins_"+plot+".png");
 return c;



}

TCanvas* NAt(){

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

 
 NatSig->SetPoint(0,0.,Sig0->Integral(55,300));
 NatSig->SetPoint(1,50.,Sig50->Integral(55,300));
 NatSig->SetPoint(2,100.,Sig100->Integral(55,300));
 NatSig->SetPoint(3,150.,Sig150->Integral(55,300));
 NatSig->SetPoint(4,200.,Sig200->Integral(55,300));
 NatSig->SetPoint(5,250.,Sig250->Integral(55,300));


 NatSig->SetPointError(0,1.,sqrt(Sig0->Integral(55,300)));
 NatSig->SetPointError(1,1.,sqrt(Sig50->Integral(55,300)));
 NatSig->SetPointError(2,1.,sqrt(Sig100->Integral(55,300)));
 NatSig->SetPointError(3,1.,sqrt(Sig150->Integral(55,300)));
 NatSig->SetPointError(4,1.,sqrt(Sig200->Integral(55,300)));
 NatSig->SetPointError(5,1.,sqrt(Sig250->Integral(55,300)));




 NatCtrl->SetPoint(0,0.,Ctrl0->Integral(55,300));
 NatCtrl->SetPoint(1,50.,Ctrl50->Integral(55,300));
 NatCtrl->SetPoint(2,100.,Ctrl100->Integral(55,300));
 NatCtrl->SetPoint(3,150.,Ctrl150->Integral(55,300));
 NatCtrl->SetPoint(4,200.,Ctrl200->Integral(55,300));
 NatCtrl->SetPoint(5,250.,Ctrl250->Integral(55,300));


 NatCtrl->SetPointError(0,1.,sqrt(Ctrl0->Integral(55,300)));
 NatCtrl->SetPointError(1,1.,sqrt(Ctrl50->Integral(55,300)));
 NatCtrl->SetPointError(2,1.,sqrt(Ctrl100->Integral(55,300)));
 NatCtrl->SetPointError(3,1.,sqrt(Ctrl150->Integral(55,300)));
 NatCtrl->SetPointError(4,1.,sqrt(Ctrl200->Integral(55,300)));
 NatCtrl->SetPointError(5,1.,sqrt(Ctrl250->Integral(55,300)));

  gROOT->SetStyle("Plain");


TCanvas* c = new TCanvas("NalphaT","NAlphaT");
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
 NatCtrl->Draw("AP");
 NatSig->Draw("P");
 NatCtrl->GetXaxis()->SetTitle("HT Cut [GeV]");
 NatCtrl->GetYaxis()->SetTitle("N(AlphaT>0.55)");

 NatCtrl->GetXaxis()->SetTitle("HT Cut [GeV]");
 NatCtrl->GetYaxis()->SetRangeUser(0.01,100000);
 NatCtrl->SetTitle();
 leg->Draw("SAME");

 c->Update();
 c->SaveAs(saving+"NAlphaTbyHTplot.png");
 return c;
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





