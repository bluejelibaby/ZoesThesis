TDirectory* inDir1;
TDirectory* inDir2;

void createLowPtIsoGraphs(TString outFileName)
{
  TFile* inFile1 = new TFile("lm1Elec.root", "read");
  TFile* inFile2 = new TFile("qcd.root",     "read");
  TFile* outFile = new TFile(outFileName,    "recreate");

  std::vector<TString> isoName, idName,         ptCutName;
  std::vector<TString> idTitle, elecPtCutTitle, muonPtCutTitle;

  outFile->mkdir("effGraph");
  outFile->mkdir("effGraphCanvas");
  // outFile->mkdir("optimization");

  outFile->GetDirectory("effGraph")->mkdir      ("absIsoCutRej_absIsoCutEff");
  outFile->GetDirectory("effGraphCanvas")->mkdir("absIsoCutRej_absIsoCutEff");

  isoName.push_back("trackIso");
  isoName.push_back("ecalIso");
  isoName.push_back("hcalIso");
  isoName.push_back("combIso");

  idName.push_back("elec");
  idName.push_back("muon");

  idTitle.push_back("Electrons");
  idTitle.push_back("Muons");

  ptCutName.push_back("ptCut0_ptCut1");
  ptCutName.push_back("ptCut1_ptCut2");
  ptCutName.push_back("ptCut2_ptCut3");
  ptCutName.push_back("ptCut3_ptCut4");
  ptCutName.push_back("ptCut4_ptCut5");
  ptCutName.push_back("ptCut5_ptCut6");
  ptCutName.push_back("ptCut6_ptCut7");
  ptCutName.push_back("ptCut7_ptCut8");
  ptCutName.push_back("ptCut8_ptCut9");

  elecPtCutTitle.push_back("5 - 10 GeV");
  elecPtCutTitle.push_back("10 - 15 GeV");
  elecPtCutTitle.push_back("15 - 20 GeV");
  elecPtCutTitle.push_back("20 - 25 GeV");
  elecPtCutTitle.push_back("25 - 30 GeV");
  elecPtCutTitle.push_back("30 - 35 GeV");
  elecPtCutTitle.push_back("35 - 40 GeV");
  elecPtCutTitle.push_back("40 - 45 GeV");
  elecPtCutTitle.push_back("45 - 50 GeV");

  muonPtCutTitle.push_back("3 - 6 GeV");
  muonPtCutTitle.push_back("6 - 9 GeV");
  muonPtCutTitle.push_back("9 - 12 GeV");
  muonPtCutTitle.push_back("12 - 15 GeV");
  muonPtCutTitle.push_back("15 - 18 GeV");
  muonPtCutTitle.push_back("18 - 21 GeV");
  muonPtCutTitle.push_back("21 - 24 GeV");
  muonPtCutTitle.push_back("24 - 27 GeV");
  muonPtCutTitle.push_back("27 - 30 GeV");

  inDir1 = inFile1->GetDirectory("eff/absIsoCut_absIsoCutEff");
  inDir2 = inFile2->GetDirectory("eff/absIsoCut_absIsoCutRej");

  outFile->cd("effGraph/absIsoCutRej_absIsoCutEff");

  for (Int_t i = 0; i < isoName.size(); i++) {
    for (Int_t j = 0; j < idName.size(); j++) {
      for (Int_t k = 0; k < ptCutName.size(); k++) {
        makeGraph(isoName.at(i) + "_" + idName.at(j) + "_prompt_"    + ptCutName.at(k),
                  isoName.at(i) + "_" + idName.at(j) + "_nonPrompt_" + ptCutName.at(k),
                  isoName.at(i) + "_" + idName.at(j) + "_nonPrompt_" + ptCutName.at(k));

        makeGraph(isoName.at(i) + "_" + idName.at(j) + "_prompt_" + ptCutName.at(k),
                  isoName.at(i) + "_" + idName.at(j) + "_fake_"   + ptCutName.at(k),
                  isoName.at(i) + "_" + idName.at(j) + "_fake_"   + ptCutName.at(k));
      }
    }
  }

  inDir1 = outFile->GetDirectory("effGraph/absIsoCutRej_absIsoCutEff");
  inDir2 = outFile->GetDirectory("effGraph/absIsoCutRej_absIsoCutEff");

  outFile->cd("effGraphCanvas/absIsoCutRej_absIsoCutEff");

  for (Int_t i = 0; i < idName.size(); i++) {
    for (Int_t j = 0; j < ptCutName.size(); j++) {
      if (i == 0) {
        make4GCanvas("trackIso_" + idName.at(i) + "_nonPrompt_" + ptCutName.at(j),
                     "ecalIso_"  + idName.at(i) + "_nonPrompt_" + ptCutName.at(j),
                     "hcalIso_"  + idName.at(i) + "_nonPrompt_" + ptCutName.at(j),
                     "combIso_"  + idName.at(i) + "_nonPrompt_" + ptCutName.at(j),
                     "track abs iso", "ECAL abs iso", "HCAL abs iso", "comb abs iso",
                     idName.at(i) + "_nonPrompt_" + ptCutName.at(j),
                     "non-prompt", idTitle.at(i), elecPtCutTitle.at(j));
      }
      else if (i == 1) {
        make4GCanvas("trackIso_" + idName.at(i) + "_nonPrompt_" + ptCutName.at(j),
                     "ecalIso_"  + idName.at(i) + "_nonPrompt_" + ptCutName.at(j),
                     "hcalIso_"  + idName.at(i) + "_nonPrompt_" + ptCutName.at(j),
                     "combIso_"  + idName.at(i) + "_nonPrompt_" + ptCutName.at(j),
                     "track abs iso", "ECAL abs iso", "HCAL abs iso", "comb abs iso",
                     idName.at(i) + "_nonPrompt_" + ptCutName.at(j),
                     "non-prompt", idTitle.at(i), muonPtCutTitle.at(j));
      }
      if (i == 0) {
        make4GCanvas("trackIso_" + idName.at(i) + "_fake_" + ptCutName.at(j),
                     "ecalIso_"  + idName.at(i) + "_fake_" + ptCutName.at(j),
                     "hcalIso_"  + idName.at(i) + "_fake_" + ptCutName.at(j),
                     "combIso_"  + idName.at(i) + "_fake_" + ptCutName.at(j),
                     "track abs iso", "ECAL abs iso", "HCAL abs iso", "comb abs iso",
                     idName.at(i) + "_fake_" + ptCutName.at(j),
                     "fake", idTitle.at(i), elecPtCutTitle.at(j));
      }
      else if (i == 1) {
        make4GCanvas("trackIso_" + idName.at(i) + "_fake_" + ptCutName.at(j),
                     "ecalIso_"  + idName.at(i) + "_fake_" + ptCutName.at(j),
                     "hcalIso_"  + idName.at(i) + "_fake_" + ptCutName.at(j),
                     "combIso_"  + idName.at(i) + "_fake_" + ptCutName.at(j),
                     "track abs iso", "ECAL abs iso", "HCAL abs iso", "comb abs iso",
                     idName.at(i) + "_fake_" + ptCutName.at(j),
                     "fake", idTitle.at(i), muonPtCutTitle.at(j));
      }
    }
  }

  inFile1->Close();
  inFile2->Close();
  outFile->Close();
}

makeGraph(TString effHistName, TString rejHistName, TString graphName)
{
  TH2D* h_eff = (TH2D*)inDir1->Get(effHistName);
  TH2D* h_rej = (TH2D*)inDir2->Get(rejHistName);

  TGraphErrors* g = new TGraphErrors();

  g->SetName(graphName);

  for (Int_t i = 1; i <= h_eff->GetNbinsX(); i++) {
    Double_t eff = h_eff->GetBinContent(i);
    Double_t rej = h_rej->GetBinContent(i);

    g->SetPoint(i, rej, eff);
  }

  g->Write();
}

make3GCanvas(TString graphName1,  TString graphName2,  TString graphName3,
             TString legendName1, TString legendName2, TString legendName3, TString canvasName,
             TString xAxisType,   TString histId,      TString histPtCut)
{
  TGraphErrors* g1 = (TGraphErrors*)inDir1->Get(graphName1);
  TGraphErrors* g2 = (TGraphErrors*)inDir1->Get(graphName2);
  TGraphErrors* g3 = (TGraphErrors*)inDir1->Get(graphName3);

  TMultiGraph* m = new TMultiGraph();

  TLegend* l = new TLegend(0.67, 0.81, 0.99, 0.99, "");

  TCanvas* c = new TCanvas(canvasName, "", 600, 600);

  g1->SetLineColor(kRed);
  g1->SetMarkerColor(kRed);
  g1->SetMarkerStyle(20);

  g2->SetLineColor  (kGreen);
  g2->SetMarkerColor(kGreen);
  g2->SetMarkerStyle(21);

  g3->SetLineColor  (kBlue);
  g3->SetMarkerColor(kBlue);
  g3->SetMarkerStyle(22);

  m->Add(g1);
  m->Add(g2);
  m->Add(g3);

  l->AddEntry(g1, legendName1, "P");
  l->AddEntry(g2, legendName2, "P");
  l->AddEntry(g3, legendName3, "P");

  m->Draw("ap");

  l->Draw();

  g1->GetXaxis()->SetRangeUser(0.0, 1.0);
  g1->GetYaxis()->SetRangeUser(0.0, 1.0);

  m->GetXaxis()->SetTitle(xAxisType + " rej");
  m->GetYaxis()->SetTitle("prompt eff");
  m->GetYaxis()->SetTitleOffset(1.0);
  m->SetTitle(histId + ", " + histPtCut);

  l->SetFillColor(0);

  c->SaveAs("./bkgdRej_sigEff/" + canvasName + ".png");

  c->Draw();
  c->Write();
}

make4GCanvas(TString graphName1,  TString graphName2,  TString graphName3,  TString graphName4,
             TString legendName1, TString legendName2, TString legendName3, TString legendName4,
             TString canvasName,  TString xAxisType,   TString histId,      TString histPtCut)
{
  TGraphErrors* g1 = (TGraphErrors*)inDir1->Get(graphName1);
  TGraphErrors* g2 = (TGraphErrors*)inDir1->Get(graphName2);
  TGraphErrors* g3 = (TGraphErrors*)inDir1->Get(graphName3);
  TGraphErrors* g4 = (TGraphErrors*)inDir1->Get(graphName4);

  TMultiGraph* m = new TMultiGraph();

  TLegend* l = new TLegend(0.67, 0.81, 0.99, 0.99, "");

  TCanvas* c = new TCanvas(canvasName, "", 600, 600);

  g1->SetLineColor(kRed);
  g1->SetMarkerColor(kRed);
  g1->SetMarkerStyle(20);

  g2->SetLineColor  (kGreen);
  g2->SetMarkerColor(kGreen);
  g2->SetMarkerStyle(21);

  g3->SetLineColor  (kBlue);
  g3->SetMarkerColor(kBlue);
  g3->SetMarkerStyle(22);

  g4->SetLineColor  (kMagenta);
  g4->SetMarkerColor(kMagenta);
  g4->SetMarkerStyle(23);

  m->Add(g1);
  m->Add(g2);
  m->Add(g3);
  m->Add(g4);

  l->AddEntry(g1, legendName1, "P");
  l->AddEntry(g2, legendName2, "P");
  l->AddEntry(g3, legendName3, "P");
  l->AddEntry(g4, legendName4, "P");

  m->Draw("ap");

  l->Draw();

  g1->GetXaxis()->SetRangeUser(0.0, 1.0);
  g1->GetYaxis()->SetRangeUser(0.0, 1.0);

  m->GetXaxis()->SetTitle(xAxisType + " rej");
  m->GetYaxis()->SetTitle("prompt eff");
  m->GetYaxis()->SetTitleOffset(1.0);
  m->SetTitle(histId + ", " + histPtCut);

  l->SetFillColor(0);

  c->SaveAs("./bkgdRej_sigEff/" + canvasName + ".png");

  c->Draw();
  c->Write();
}