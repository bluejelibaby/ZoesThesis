TDirectory* inDir1;
TDirectory* inDir2;

void createLowPtIsoCanvases(TString outFileName)
{
  TFile* inFile1 = new TFile("lm1Elec.root", "read");
  TFile* inFile2 = new TFile("qcd.root",     "read");
  TFile* outFile = new TFile(outFileName,    "recreate");

  std::vector<TString> isoName,  idName,  ptCutName;
  std::vector<TString> isoTitle, idTitle, elecPtCutTitle, muonPtCutTitle;

  outFile->mkdir("eff");
  outFile->mkdir("recoPt_absIso");
  outFile->mkdir("recoPt_relIso");

  outFile->GetDirectory("eff")->mkdir("genPt_recoEff");
  outFile->GetDirectory("eff")->mkdir("absIsoCut_cutEff");

  isoName.push_back("trackIso");
  isoName.push_back("ecalIso");
  isoName.push_back("hcalIso");
  isoName.push_back("combIso");

  isoTitle.push_back("track");
  isoTitle.push_back("ECAL");
  isoTitle.push_back("HCAL");
  isoTitle.push_back("comb");

  idName.push_back("elec");
  idName.push_back("muon");

  idTitle.push_back("Electrons");
  idTitle.push_back("Muons");

  ptCutName.push_back("ptCut0_ptCut1");
  ptCutName.push_back("ptCut4_ptCut5");
  ptCutName.push_back("ptCut8_ptCut9");

  elecPtCutTitle.push_back("5 - 10 GeV");
  elecPtCutTitle.push_back("25 - 30 GeV");
  elecPtCutTitle.push_back("45 - 50 GeV");

  muonPtCutTitle.push_back("3 - 6 GeV");
  muonPtCutTitle.push_back("15 - 18 GeV");
  muonPtCutTitle.push_back("27 - 30 GeV");

  for (Int_t i = 0; i < isoName.size(); i++) {
    for (Int_t j = 0; j < idName.size(); j++) {

      inDir1 = inFile1->GetDirectory("eff/absIsoCut_absIsoCutEff");
      inDir2 = inFile2->GetDirectory("eff/absIsoCut_absIsoCutRej");

      outFile->cd("eff/absIsoCut_cutEff");

      for (Int_t k = 0; k < ptCutName.size(); k++) {
        if (j == 0) {
          make3H1Canvas(isoName.at(i) + "_" + idName.at(j) + "_prompt_"    + ptCutName.at(k),
                        isoName.at(i) + "_" + idName.at(j) + "_nonPrompt_" + ptCutName.at(k),
                        isoName.at(i) + "_" + idName.at(j) + "_fake_"      + ptCutName.at(k),
                        "", "prompt eff", "hadronic rej", "fake rej",
                        "absIsoCut_" + isoName.at(i) + "_cutEff_" + idName.at(j) + "_" + ptCutName.at(k), isoTitle.at(i), idTitle.at(j), elecPtCutTitle.at(k));
        }
        else if (j == 1) {
          make3H1Canvas(isoName.at(i) + "_" + idName.at(j) + "_prompt_"    + ptCutName.at(k),
                        isoName.at(i) + "_" + idName.at(j) + "_nonPrompt_" + ptCutName.at(k),
                        isoName.at(i) + "_" + idName.at(j) + "_fake_"      + ptCutName.at(k),
                        "", "prompt eff", "hadronic rej", "fake rej",
                        "absIsoCut_" + isoName.at(i) + "_cutEff_" + idName.at(j) + "_" + ptCutName.at(k), isoTitle.at(i), idTitle.at(j), muonPtCutTitle.at(k));
        }
      }
    }
  }

  inFile1->Close();
  inFile2->Close();
  outFile->Close();
}

make3H1Canvas(TString histName1,   TString histName2,   TString histName3,   TString stackName,
              TString legendName1, TString legendName2, TString legendName3, TString canvasName,
              TString xAxisIso,    TString histId,      TString histPtCut)
{
  TH1D* h1 = (TH1D*)inDir1->Get(histName1);
  TH1D* h2 = (TH1D*)inDir2->Get(histName2);
  TH1D* h3 = (TH1D*)inDir2->Get(histName3);

  THStack* s = new THStack();

  TLegend* l = new TLegend(0.67, 0.81, 0.99, 0.99, "");

  TCanvas* c = new TCanvas(canvasName, "", 600, 600);

  h1->SetLineColor(kRed);
  h1->SetMarkerColor(kRed);
  h1->SetMarkerStyle(20);

  h2->SetLineColor(kGreen);
  h2->SetMarkerColor(kGreen);
  h2->SetMarkerStyle(21);

  h3->SetLineColor(kBlue);
  h3->SetMarkerColor(kBlue);
  h3->SetMarkerStyle(22);

  s->Add(h1);
  s->Add(h2);
  s->Add(h3);

  l->AddEntry(h1, legendName1, "LP");
  l->AddEntry(h2, legendName2, "LP");
  l->AddEntry(h3, legendName3, "LP");

  s->Draw("nostack");

  l->Draw();

  s->GetXaxis()->SetRangeUser(0.0, 25.0);
  s->GetXaxis()->SetTitle(xAxisIso + " abs iso cut");
  s->GetYaxis()->SetTitle("cut eff / rej");
  s->GetYaxis()->SetTitleOffset(1.0);
  s->SetTitle(histId + ", " + histPtCut);

  l->SetFillColor(0);

  c->SaveAs("./absIsoCut_cutEff/" + canvasName + ".png");

  c->Draw();
  c->Write();
}