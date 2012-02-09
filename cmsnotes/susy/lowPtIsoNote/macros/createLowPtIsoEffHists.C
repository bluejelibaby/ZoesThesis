TFile*      file;
TDirectory* inDir1;
TDirectory* inDir2;
TDirectory* inDir3;

void createLowPtIsoEffHists(TString fileName)
{
  file = new TFile(fileName, "update");

  std::vector<TString>  idName,  typeName,  isoName,  ptCutName, isoCutName;
  std::vector<TString>  idTitle, typeTitle, isoTitle;
  Double_t xMin[2];

  if (file->GetDirectory("eff") != 0)
    file->Delete("eff;1");

  if (file->GetDirectory("norm") != 0)
    file->Delete("norm;1");

  file->mkdir("eff");
  file->mkdir("norm");

  file->GetDirectory("eff")->mkdir("genPt_recoEff");
  file->GetDirectory("eff")->mkdir("recoPt_absIsoCutEff");
  file->GetDirectory("eff")->mkdir("recoPt_relIsoCutEff");
  file->GetDirectory("eff")->mkdir("absIsoCut_recoEff");
  file->GetDirectory("eff")->mkdir("relIsoCut_recoEff");
  file->GetDirectory("eff")->mkdir("absIsoCut_absIsoCutEff");
  file->GetDirectory("eff")->mkdir("relIsoCut_relIsoCutEff");
  file->GetDirectory("eff")->mkdir("absIsoCut_absIsoCutRej");
  file->GetDirectory("eff")->mkdir("relIsoCut_relIsoCutRej");

  file->GetDirectory("norm")->mkdir("recoPt_absIso");
  file->GetDirectory("norm")->mkdir("recoPt_relIso");

  idName.push_back("elec");
  idName.push_back("muon");

  idTitle.push_back("electrons");
  idTitle.push_back("muons");

  typeName.push_back("prompt");
  typeName.push_back("nonPrompt");
  typeName.push_back("fake");

  typeTitle.push_back("Prompt");
  typeTitle.push_back("Non-prompt");
  typeTitle.push_back("Fake");

  isoName.push_back("trackIso");
  isoName.push_back("ecalIso");
  isoName.push_back("hcalIso");
  isoName.push_back("combIso");

  isoTitle.push_back("track");
  isoTitle.push_back("ECAL");
  isoTitle.push_back("HCAL");
  isoTitle.push_back("comb");

  ptCutName.push_back("ptCut0_ptCut1");
  ptCutName.push_back("ptCut1_ptCut2");
  ptCutName.push_back("ptCut2_ptCut3");
  ptCutName.push_back("ptCut3_ptCut4");
  ptCutName.push_back("ptCut4_ptCut5");
  ptCutName.push_back("ptCut5_ptCut6");
  ptCutName.push_back("ptCut6_ptCut7");
  ptCutName.push_back("ptCut7_ptCut8");
  ptCutName.push_back("ptCut8_ptCut9");

  isoCutName.push_back("cut1");
  isoCutName.push_back("cut2");

  xMin[0] = 5.0;
  xMin[1] = 3.0;

  for (Int_t i = 0; i < idName.size(); i++) {
    for (Int_t j = 0; j < typeName.size(); j++) {
      if (j == 0)
        createGenPtRecoEff(idName.at(i) + "_" + typeName.at(j));

      for (Int_t k = 0; k < isoName.size(); k++) {
        // if (j == 0) {  // For LM1
        if (j > 0) {  // For QCD
          createRecoPtIsoNorm(isoName.at(k) + "_" + idName.at(i) + "_" + typeName.at(j), xMin[i],
                              isoTitle.at(k), typeTitle.at(j) + " " + idTitle.at(i));
        }

        for (Int_t l = 0; l < isoCutName.size(); l++)
          createRecoPtIsoCutEff(isoName.at(k) + "Cut_" + idName.at(i) + "_" + typeName.at(j) + "_" + isoCutName.at(l),
                                                         idName.at(i) + "_" + typeName.at(j));

        for (Int_t l = 0; l < ptCutName.size(); l++) {
          if (j < typeName.size() - 1)
            createIsoCutRecoEff(isoName.at(k) + "_" + idName.at(i) + "_" + typeName.at(j) + "_" + ptCutName.at(l),
                                                      idName.at(i) + "_" + typeName.at(j) + "_" + ptCutName.at(l));

          createIsoCutIsoCutEff(isoName.at(k) + "_" + idName.at(i) + "_" + typeName.at(j) + "_" + ptCutName.at(l));
          createIsoCutIsoCutRej(isoName.at(k) + "_" + idName.at(i) + "_" + typeName.at(j) + "_" + ptCutName.at(l));
        }
      }
    }
  }

  file->Close();
}

void createGenPtRecoEff(TString histName)
{
  inDir1 = file->GetDirectory("genPt_matched");
  inDir2 = file->GetDirectory("genPt_all");

  TH1D* h_in1 = (TH1D*)inDir1->Get(histName);
  TH1D* h_in2 = (TH1D*)inDir2->Get(histName);

  // For electrons
  // TH1D* h_in1_new = h_in1->Rebin(15, "h_in1_new");
  // TH1D* h_in2_new = h_in2->Rebin(15, "h_in2_new");

  // For muons
  TH1D* h_in1_new = h_in1->Rebin(9, "h_in1_new");
  TH1D* h_in2_new = h_in2->Rebin(9, "h_in2_new");

  file->cd("eff/genPt_recoEff");

  // For electrons
  // TH1D* h_out = new TH1D(histName, "", 9, 0.0, 45.0);

  // For muons
  TH1D* h_out = new TH1D(histName, "", 15, 0.0, 45.0);

  h_out->Sumw2();

  h_out->Divide(h_in1_new, h_in2_new, 1.0, 1.0, "B");

  h_out->Write();
}

void createRecoPtIsoCutEff(TString histName1, TString histName2)
{
  inDir1 = file->GetDirectory("recoPt_absIsoCut");
  inDir2 = file->GetDirectory("recoPt_relIsoCut");
  inDir3 = file->GetDirectory("recoPt_all");

  TH1D* h_in1 = (TH1D*)inDir1->Get(histName1);
  TH1D* h_in2 = (TH1D*)inDir2->Get(histName1);
  TH1D* h_in3 = (TH1D*)inDir3->Get(histName2);

  file->cd("eff/recoPt_absIsoCutEff");

  TH1D* h_out1 = new TH1D(histName1, "", 135, 0.0, 45.0);

  h_out1->Sumw2();

  h_out1->Divide(h_in1, h_in3, 1.0, 1.0, "B");

  h_out1->Write();

  file->cd("eff/recoPt_relIsoCutEff");

  TH1D* h_out2 = new TH1D(histName1, "", 135, 0.0, 45.0);

  h_out2->Sumw2();

  h_out2->Divide(h_in2, h_in3, 1.0, 1.0, "B");

  h_out2->Write();
}

void createIsoCutRecoEff(TString histName1, TString histName2)
{
  inDir1 = file->GetDirectory("absIso");
  inDir2 = file->GetDirectory("relIso");
  inDir3 = file->GetDirectory("genIso");

  TH1D* h_in1 = (TH1D*)inDir1->Get(histName1);
  TH1D* h_in2 = (TH1D*)inDir2->Get(histName1);
  TH1D* h_in3 = (TH1D*)inDir3->Get(histName2);

  TH1D* h_integral1 = new TH1D("h_integral1", "", 135, 0.0, 45.0);
  TH1D* h_integral2 = new TH1D("h_integral2", "", 135, 0.0, 1.5);

  h_integral1->Sumw2();
  h_integral2->Sumw2();

  for (Int_t i = 1; i <= 135; i++) {
    Double_t integral1 = h_in1->Integral(1, i);
    Double_t integral2 = h_in2->Integral(1, i);

    h_integral1->SetBinContent(i, integral1);
    h_integral2->SetBinContent(i, integral2);
  }

  file->cd("eff/absIsoCut_recoEff");

  TH1D* h_out1 = new TH1D(histName1, "", 135, 0.0, 45.0);

  h_out1->Sumw2();

  h_out1->Divide(h_integral1, h_in3, 1.0, 1.0, "B");

  h_out1->Write();

  file->cd("eff/relIsoCut_recoEff");

  TH1D* h_out2 = new TH1D(histName1, "", 135, 0.0, 1.5);

  h_out2->Sumw2();

  h_out2->Divide(h_integral2, h_in3, 1.0, 1.0, "B");

  h_out2->Write();

  h_integral1->Delete();
  h_integral2->Delete();
}

void createIsoCutIsoCutEff(TString histName)
{
  inDir1 = file->GetDirectory("absIso");
  inDir2 = file->GetDirectory("relIso");

  TH1D* h_in1 = (TH1D*)inDir1->Get(histName);
  TH1D* h_in2 = (TH1D*)inDir2->Get(histName);

  TH1D* h_integral1    = new TH1D("h_integral1",    "", 135, 0.0, 45.0);
  TH1D* h_integral2    = new TH1D("h_integral2",    "", 135, 0.0, 1.5);
  TH1D* h_maxIntegral1 = new TH1D("h_maxIntegral1", "", 135, 0.0, 45.0);
  TH1D* h_maxIntegral2 = new TH1D("h_maxIntegral2", "", 135, 0.0, 1.5);

  h_integral1->Sumw2();
  h_integral2->Sumw2();
  h_maxIntegral1->Sumw2();
  h_maxIntegral2->Sumw2();

  for (Int_t i = 1; i <= 135; i++) {
    Double_t integral1    = h_in1->Integral(1, i);
    Double_t integral2    = h_in2->Integral(1, i);
    Double_t maxIntegral1 = h_in1->Integral(1, 136);
    Double_t maxIntegral2 = h_in2->Integral(1, 136);

    h_integral1->SetBinContent   (i, integral1);
    h_integral2->SetBinContent   (i, integral2);
    h_maxIntegral1->SetBinContent(i, maxIntegral1);
    h_maxIntegral2->SetBinContent(i, maxIntegral2);

    h_integral1->SetBinError   (i, sqrt(integral1));
    h_integral2->SetBinError   (i, sqrt(integral2));
    h_maxIntegral1->SetBinError(i, sqrt(maxIntegral1));
    h_maxIntegral2->SetBinError(i, sqrt(maxIntegral2));
  }

  file->cd("eff/absIsoCut_absIsoCutEff");

  TH1D* h_out1 = new TH1D(histName, "", 135, 0.0, 45.0);

  h_out1->Sumw2();

  h_out1->Divide(h_integral1, h_maxIntegral1, 1.0, 1.0, "B");

  h_out1->Write();

  file->cd("eff/relIsoCut_relIsoCutEff");

  TH1D* h_out2 = new TH1D(histName, "", 135, 0.0, 1.5);

  h_out2->Sumw2();

  h_out2->Divide(h_integral1, h_maxIntegral1, 1.0, 1.0, "B");

  h_out2->Write();

  h_integral1->Delete();
  h_integral2->Delete();
  h_maxIntegral1->Delete();
  h_maxIntegral2->Delete();
}

void createIsoCutIsoCutRej(TString histName)
{
  inDir1 = file->GetDirectory("absIso");
  inDir2 = file->GetDirectory("relIso");

  TH1D* h_in1 = (TH1D*)inDir1->Get(histName);
  TH1D* h_in2 = (TH1D*)inDir2->Get(histName);

  TH1D* h_integral1    = new TH1D("h_integral1",    "", 135, 0.0, 45.0);
  TH1D* h_integral2    = new TH1D("h_integral2",    "", 135, 0.0, 1.5);
  TH1D* h_maxIntegral1 = new TH1D("h_maxIntegral1", "", 135, 0.0, 45.0);
  TH1D* h_maxIntegral2 = new TH1D("h_maxIntegral2", "", 135, 0.0, 1.5);

  h_integral1->Sumw2();
  h_integral2->Sumw2();
  h_maxIntegral1->Sumw2();
  h_maxIntegral2->Sumw2();

  for (Int_t i = 1; i <= 135; i++) {
    Double_t integral1    = h_in1->Integral(1, i);
    Double_t integral2    = h_in2->Integral(1, i);
    Double_t maxIntegral1 = h_in1->Integral(1, 136);
    Double_t maxIntegral2 = h_in2->Integral(1, 136);

    h_integral1->SetBinContent   (i, integral1);
    h_integral2->SetBinContent   (i, integral2);
    h_maxIntegral1->SetBinContent(i, maxIntegral1);
    h_maxIntegral2->SetBinContent(i, maxIntegral2);

    h_integral1->SetBinError   (i, sqrt(integral1));
    h_integral2->SetBinError   (i, sqrt(integral2));
    h_maxIntegral1->SetBinError(i, sqrt(maxIntegral1));
    h_maxIntegral2->SetBinError(i, sqrt(maxIntegral2));
  }

  file->cd("eff/absIsoCut_absIsoCutRej");

  TH1D* h_out1 = new TH1D(histName, "", 135, 0.0, 45.0);

  h_out1->Sumw2();

  h_out1->Divide(h_integral1, h_maxIntegral1, 1.0, 1.0, "B");

  for (Int_t i = 1; i <= 135; i++) {
    Double_t stuff = h_out1->GetBinContent(i);

    h_out1->SetBinContent(i, 1.0 - stuff);
  }

  h_out1->Write();

  file->cd("eff/relIsoCut_relIsoCutRej");

  TH1D* h_out2 = new TH1D(histName, "", 135, 0.0, 1.5);

  h_out2->Sumw2();

  h_out2->Divide(h_integral1, h_maxIntegral1, 1.0, 1.0, "B");

  for (Int_t i = 1; i <= 135; i++) {
    Double_t stuff = h_out2->GetBinContent(i);

    h_out2->SetBinContent(i, 1.0 - stuff);
  }

  h_out2->Write();

  h_integral1->Delete();
  h_integral2->Delete();
  h_maxIntegral1->Delete();
  h_maxIntegral2->Delete();
}

void createRecoPtIsoNorm(TString histName, Double_t xAxisMin, TString yAxisIso, TString histTitle)
{
  inDir1 = file->GetDirectory("recoPt_absIso");
  inDir2 = file->GetDirectory("recoPt_relIso");

  TCanvas* c = new TCanvas();

  TH2D* h_in1 = (TH2D*)inDir1->Get(histName);
  TH2D* h_in2 = (TH2D*)inDir2->Get(histName);

  TLine* l = new TLine();

  Double_t integral1 = h_in1->Integral(1, 136, 1, 136);
  Double_t integral2 = h_in2->Integral(1, 136, 1, 136);

  h_in1->GetXaxis()->SetRangeUser(xAxisMin, 30.0);
  h_in2->GetXaxis()->SetRangeUser(xAxisMin, 30.0);

  h_in1->GetXaxis()->SetTitle("reco p_{T}");
  h_in2->GetXaxis()->SetTitle("reco p_{T}");

  h_in1->GetYaxis()->SetRangeUser(0.0, 25.0);
  h_in2->GetYaxis()->SetRangeUser(0.0, 1.0);

  h_in1->GetYaxis()->SetTitle(yAxisIso + " abs iso");
  h_in2->GetYaxis()->SetTitle(yAxisIso + " rel iso");

  h_in1->GetYaxis()->SetTitleOffset(1.2);
  h_in2->GetYaxis()->SetTitleOffset(1.2);

  h_in1->Scale(1.0 / integral1);
  h_in2->Scale(1.0 / integral2);

  h_in1->SetName(histName + "_norm");
  h_in2->SetName(histName + "_norm");

  h_in1->SetTitle(histTitle);
  h_in2->SetTitle(histTitle);

  h_in1->Draw("col");

  c->SaveAs("./recoPt_absIso/" + histName + ".png");

  h_in2->Draw("col");

  if (histName.BeginsWith("comb")) {
    l->SetLineColor(kRed);
    l->SetLineWidth(2);

    l->DrawLine(xAxisMin, 0.1, 30.0, 0.1);
  }

  c->SaveAs("./recoPt_relIso/" + histName + ".png");

  file->cd("norm/recoPt_absIso");

  h_in1->Write();

  file->cd("norm/recoPt_relIso");

  h_in2->Write();
}