#include <iomanip>

gStyle->SetErrorX();

TDirectory* inDir1;
TDirectory* inDir2;

void createLowPtIsoOptHists(TString outFileName)
{
  TFile* inFile1 = new TFile("lm1Elec.root", "read");
  TFile* inFile2 = new TFile("qcd.root",     "read");
  TFile* outFile = new TFile(outFileName,    "recreate");

  Int_t                nBins[2];
  Double_t             lowPt[2], pureCut[9], optCut[9], effCut[9];
  std::vector<TString> isoName, idName, ptCutName;

  nBins[0] = 5;
  nBins[1] = 9;

  lowPt[0] = 5.0;
  lowPt[1] = 3.0;

  isoName.push_back("track");
  isoName.push_back("ecal");
  isoName.push_back("hcal");
  isoName.push_back("comb");

  idName.push_back("elec");
  idName.push_back("muon");

  ptCutName.push_back("ptCut0_ptCut1");
  ptCutName.push_back("ptCut1_ptCut2");
  ptCutName.push_back("ptCut2_ptCut3");
  ptCutName.push_back("ptCut3_ptCut4");
  ptCutName.push_back("ptCut4_ptCut5");
  ptCutName.push_back("ptCut5_ptCut6");
  ptCutName.push_back("ptCut6_ptCut7");
  ptCutName.push_back("ptCut7_ptCut8");
  ptCutName.push_back("ptCut8_ptCut9");

  inDir1 = inFile1->GetDirectory("eff/absIsoCut_absIsoCutEff");
  inDir2 = inFile2->GetDirectory("eff/absIsoCut_absIsoCutRej");

  for (Int_t i = 0; i < isoName.size(); i++) {
    for (Int_t j = 0; j < idName.size(); j++) {
      for (Int_t k = 0; k < ptCutName.size(); k++)
        pureCut[k] = getPureCut(isoName.at(i), idName.at(j), ptCutName.at(k));

      for (Int_t k = 0; k < ptCutName.size(); k++)
        optCut[k]  = getOptCut (isoName.at(i), idName.at(j), ptCutName.at(k));

      for (Int_t k = 0; k < ptCutName.size(); k++)
        effCut[k]  = getEffCut (isoName.at(i), idName.at(j), ptCutName.at(k));

      makeOptHist(nBins[j], pureCut, lowPt[j], isoName.at(i), idName.at(j), "pure");
      makeOptHist(nBins[j], optCut,  lowPt[j], isoName.at(i), idName.at(j), "opt");
      makeOptHist(nBins[j], effCut,  lowPt[j], isoName.at(i), idName.at(j), "eff");
    }
  }

  inFile1->Close();
  inFile2->Close();
  outFile->Close();
}

Double_t getPureCut(TString iso, TString id, TString ptCut)
{
  Int_t    optCutBin        = -1;
  Double_t optCut           = -9.9;
  Double_t optCutEff        = -9.9;
  Double_t optCutHadRej     = -9.9;
  Double_t optCutFakeRej    = -9.9;
  Double_t optCutEffErr     = -9.9;
  Double_t optCutHadRejErr  = -9.9;
  Double_t optCutFakeRejErr = -9.9;
  Double_t bestVal          = -9.9;
  Double_t currVal          = -9.9;

  TString isoTitle;

  TH2D* h_eff     = (TH2D*)inDir1->Get(iso + "Iso_" + id + "_prompt_"    + ptCut);
  TH2D* h_hadRej  = (TH2D*)inDir2->Get(iso + "Iso_" + id + "_nonPrompt_" + ptCut);
  TH2D* h_fakeRej = (TH2D*)inDir2->Get(iso + "Iso_" + id + "_fake_"      + ptCut);

  for (Int_t i = 1; i <= h_eff->GetNbinsX(); i++) {
    Double_t eff        = h_eff->GetBinContent    (i);
    Double_t hadRej     = h_hadRej->GetBinContent (i);
    Double_t fakeRej    = h_fakeRej->GetBinContent(i);
    Double_t effErr     = h_eff->GetBinError      (i);
    Double_t hadRejErr  = h_hadRej->GetBinError   (i);
    Double_t fakeRejErr = h_fakeRej->GetBinError  (i);

    if (fakeRej > 0.60)
      currVal = eff;

    if (currVal > bestVal) {
      optCutBin        = i;
      optCut           = h_eff->GetBinCenter(i);
      optCutEff        = eff;
      optCutHadRej     = hadRej;
      optCutFakeRej    = fakeRej;
      optCutEffErr     = effErr;
      optCutHadRejErr  = hadRejErr;
      optCutFakeRejErr = fakeRejErr;
      bestVal          = currVal;
    }
  }

  if      (iso == "track") isoTitle = "tracker";
  else if (iso == "ecal")  isoTitle = "ECAL";
  else if (iso == "hcal")  isoTitle = "HCAL";
  else if (iso == "comb")  isoTitle = "comb";

  if (id == "elec") {
    if (ptCut == "ptCut0_ptCut1") {
      std::cout << std::endl << std::endl << std::endl;

      std::cout << "\\begin{table}[htbp]"             << std::endl;
      std::cout << "   \\centering"                   << std::endl;
      std::cout << "   \\begin{tabular}{|c|c|c|c|c|}" << std::endl;
      std::cout << "      \\hline"                    << std::endl;
      std::cout << "      $p_T$ range (GeV) & Optimal cut & eff & $\\textrm{rej}_{HF}$ & $\\textrm{rej}_{fake}$ \\\\" << std::endl;
      std::cout << "      \\hline"                    << std::endl;

      std::cout << "      5 - 10 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "        << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "        << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "        << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"   << std::endl;
    }
    else if (ptCut == "ptCut1_ptCut2") {
      std::cout << "      10 - 15 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut2_ptCut3") {
      std::cout << "      15 - 20 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut3_ptCut4") {
      std::cout << "      20 - 25 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut4_ptCut5") {
      std::cout << "      25 - 30 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;

      std::cout << "   \\end{tabular}" << std::endl;
      std::cout << "   \\caption{\\small{Performances of the " << isoTitle << " isolation for"
                << " electrons when the rejection of fakes is fixed at $\\geq 0.6$}\\label{tab:" << iso << "_" << id << "_pure}}" << std::endl;
      std::cout << "\\end{table}" << std::endl << std::endl << std::endl << std::endl;
    }
  }
  else if (id == "muon") {
    if (ptCut == "ptCut0_ptCut1") {
      std::cout << std::endl << std::endl << std::endl;

      std::cout << "\\begin{table}[htbp]"             << std::endl;
      std::cout << "   \\centering"                   << std::endl;
      std::cout << "   \\begin{tabular}{|c|c|c|c|c|}" << std::endl;
      std::cout << "      \\hline"                    << std::endl;
      std::cout << "      $p_T$ range (GeV) & Optimal cut & eff & $\\textrm{rej}_{HF}$ & $\\textrm{rej}_{fake}$ \\\\" << std::endl;
      std::cout << "      \\hline"                    << std::endl;

      std::cout << "      3 - 6 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "       << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "       << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "       << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"  << std::endl;
    }
    else if (ptCut == "ptCut1_ptCut2") {
      std::cout << "      6 - 9 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "       << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "       << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "       << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"  << std::endl;
    }
    else if (ptCut == "ptCut2_ptCut3") {
      std::cout << "      9 - 12 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "        << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "        << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "        << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"   << std::endl;
    }
    else if (ptCut == "ptCut3_ptCut4") {
      std::cout << "      12 - 15 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut4_ptCut5") {
      std::cout << "      15 - 18 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut5_ptCut6") {
      std::cout << "      18 - 21 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut6_ptCut7") {
      std::cout << "      21 - 24 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut7_ptCut8") {
      std::cout << "      24 - 27 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut8_ptCut9") {
      std::cout << "      27 - 30 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;

      std::cout << "   \\end{tabular}" << std::endl;
      std::cout << "   \\caption{\\small{Performances of the " << isoTitle << " isolation for"
                << " muons when the rejection of fakes is fixed at $\\geq 0.6$}\\label{tab:" << iso << "_" << id << "_pure}}" << std::endl;
      std::cout << "\\end{table}" << std::endl << std::endl << std::endl << std::endl;
    }
  }

  return optCut;
}

Double_t getOptCut(TString iso, TString id, TString ptCut)
{
  Int_t    optCutBin        = -1;
  Double_t optCut           = -9.9;
  Double_t optCutEff        = -9.9;
  Double_t optCutHadRej     = -9.9;
  Double_t optCutFakeRej    = -9.9;
  Double_t optCutEffErr     = -9.9;
  Double_t optCutHadRejErr  = -9.9;
  Double_t optCutFakeRejErr = -9.9;
  Double_t bestVal          = 9.9;
  Double_t currVal          = 9.9;

  TString isoTitle;

  TH2D* h_eff     = (TH2D*)inDir1->Get(iso + "Iso_" + id + "_prompt_"    + ptCut);
  TH2D* h_hadRej  = (TH2D*)inDir2->Get(iso + "Iso_" + id + "_nonPrompt_" + ptCut);
  TH2D* h_fakeRej = (TH2D*)inDir2->Get(iso + "Iso_" + id + "_fake_"      + ptCut);

  for (Int_t i = 1; i <= h_eff->GetNbinsX(); i++) {
    Double_t eff        = h_eff->GetBinContent    (i);
    Double_t hadRej     = h_hadRej->GetBinContent (i);
    Double_t fakeRej    = h_fakeRej->GetBinContent(i);
    Double_t effErr     = h_eff->GetBinError      (i);
    Double_t hadRejErr  = h_hadRej->GetBinError   (i);
    Double_t fakeRejErr = h_fakeRej->GetBinError  (i);

    currVal = sqrt((1.0 - eff) * (1.0 - eff) + (1.0 - fakeRej) * (1.0 - fakeRej));

    if (currVal < bestVal) {
      optCutBin        = i;
      optCut           = h_eff->GetBinCenter(i);
      optCutEff        = eff;
      optCutHadRej     = hadRej;
      optCutFakeRej    = fakeRej;
      optCutEffErr     = effErr;
      optCutHadRejErr  = hadRejErr;
      optCutFakeRejErr = fakeRejErr;
      bestVal          = currVal;
    }
  }

  if      (iso == "track") isoTitle = "tracker";
  else if (iso == "ecal")  isoTitle = "ECAL";
  else if (iso == "hcal")  isoTitle = "HCAL";
  else if (iso == "comb")  isoTitle = "comb";

  if (id == "elec") {
    if (ptCut == "ptCut0_ptCut1") {
      std::cout << std::endl << std::endl << std::endl;

      std::cout << "\\begin{table}[htbp]"             << std::endl;
      std::cout << "   \\centering"                   << std::endl;
      std::cout << "   \\begin{tabular}{|c|c|c|c|c|}" << std::endl;
      std::cout << "      \\hline"                    << std::endl;
      std::cout << "      $p_T$ range (GeV) & Optimal cut & eff & $\\textrm{rej}_{HF}$ & $\\textrm{rej}_{fake}$ \\\\" << std::endl;
      std::cout << "      \\hline"                    << std::endl;

      std::cout << "      5 - 10 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "        << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "        << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "        << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"   << std::endl;
    }
    else if (ptCut == "ptCut1_ptCut2") {
      std::cout << "      10 - 15 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut2_ptCut3") {
      std::cout << "      15 - 20 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut3_ptCut4") {
      std::cout << "      20 - 25 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut4_ptCut5") {
      std::cout << "      25 - 30 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;

      std::cout << "   \\end{tabular}" << std::endl;
      std::cout << "   \\caption{\\small{Performances of the " << isoTitle << " isolation for"
                << " electrons after minimizing the iso variable $x$}\\label{tab:" << iso << "_" << id << "_opt}}" << std::endl;
      std::cout << "\\end{table}" << std::endl << std::endl << std::endl << std::endl;
    }
  }
  else if (id == "muon") {
    if (ptCut == "ptCut0_ptCut1") {
      std::cout << std::endl << std::endl << std::endl;

      std::cout << "\\begin{table}[htbp]"             << std::endl;
      std::cout << "   \\centering"                   << std::endl;
      std::cout << "   \\begin{tabular}{|c|c|c|c|c|}" << std::endl;
      std::cout << "      \\hline"                    << std::endl;
      std::cout << "      $p_T$ range (GeV) & Optimal cut & eff & $\\textrm{rej}_{HF}$ & $\\textrm{rej}_{fake}$ \\\\" << std::endl;
      std::cout << "      \\hline"                    << std::endl;

      std::cout << "      3 - 6 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "       << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "       << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "       << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"  << std::endl;
    }
    else if (ptCut == "ptCut1_ptCut2") {
      std::cout << "      6 - 9 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "       << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "       << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "       << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"  << std::endl;
    }
    else if (ptCut == "ptCut2_ptCut3") {
      std::cout << "      9 - 12 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "        << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "        << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "        << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"   << std::endl;
    }
    else if (ptCut == "ptCut3_ptCut4") {
      std::cout << "      12 - 15 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut4_ptCut5") {
      std::cout << "      15 - 18 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut5_ptCut6") {
      std::cout << "      18 - 21 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut6_ptCut7") {
      std::cout << "      21 - 24 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut7_ptCut8") {
      std::cout << "      24 - 27 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut8_ptCut9") {
      std::cout << "      27 - 30 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;

      std::cout << "   \\end{tabular}" << std::endl;
      std::cout << "   \\caption{\\small{Performances of the " << isoTitle << " isolation for"
                << " muons after minimizing the iso variable $x$}\\label{tab:" << iso << "_" << id << "_opt}}" << std::endl;
      std::cout << "\\end{table}" << std::endl << std::endl << std::endl << std::endl;
    }
  }

  return optCut;
}

Double_t getEffCut(TString iso, TString id, TString ptCut)
{
  Int_t    optCutBin        = -1;
  Double_t optCut           = -9.9;
  Double_t optCutEff        = -9.9;
  Double_t optCutHadRej     = -9.9;
  Double_t optCutFakeRej    = -9.9;
  Double_t optCutEffErr     = -9.9;
  Double_t optCutHadRejErr  = -9.9;
  Double_t optCutFakeRejErr = -9.9;
  Double_t bestVal          = -9.9;
  Double_t currVal          = -9.9;

  TString isoTitle;

  TH2D* h_eff     = (TH2D*)inDir1->Get(iso + "Iso_" + id + "_prompt_"    + ptCut);
  TH2D* h_hadRej  = (TH2D*)inDir2->Get(iso + "Iso_" + id + "_nonPrompt_" + ptCut);
  TH2D* h_fakeRej = (TH2D*)inDir2->Get(iso + "Iso_" + id + "_fake_"      + ptCut);

  for (Int_t i = 1; i <= h_eff->GetNbinsX(); i++) {
    Double_t eff        = h_eff->GetBinContent    (i);
    Double_t hadRej     = h_hadRej->GetBinContent (i);
    Double_t fakeRej    = h_fakeRej->GetBinContent(i);
    Double_t effErr     = h_eff->GetBinError      (i);
    Double_t hadRejErr  = h_hadRej->GetBinError   (i);
    Double_t fakeRejErr = h_fakeRej->GetBinError  (i);

    if (eff > 0.90)
      currVal = fakeRej;

    if (currVal > bestVal) {
      optCutBin        = i;
      optCut           = h_eff->GetBinCenter(i);
      optCutEff        = eff;
      optCutHadRej     = hadRej;
      optCutFakeRej    = fakeRej;
      optCutEffErr     = effErr;
      optCutHadRejErr  = hadRejErr;
      optCutFakeRejErr = fakeRejErr;
      bestVal          = currVal;
    }
  }

  if      (iso == "track") isoTitle = "tracker";
  else if (iso == "ecal")  isoTitle = "ECAL";
  else if (iso == "hcal")  isoTitle = "HCAL";
  else if (iso == "comb")  isoTitle = "comb";

  if (id == "elec") {
    if (ptCut == "ptCut0_ptCut1") {
      std::cout << std::endl << std::endl << std::endl;

      std::cout << "\\begin{table}[htbp]"             << std::endl;
      std::cout << "   \\centering"                   << std::endl;
      std::cout << "   \\begin{tabular}{|c|c|c|c|c|}" << std::endl;
      std::cout << "      \\hline"                    << std::endl;
      std::cout << "      $p_T$ range (GeV) & Optimal cut & eff & $\\textrm{rej}_{HF}$ & $\\textrm{rej}_{fake}$ \\\\" << std::endl;
      std::cout << "      \\hline"                    << std::endl;

      std::cout << "      5 - 10 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "        << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "        << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "        << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"   << std::endl;
    }
    else if (ptCut == "ptCut1_ptCut2") {
      std::cout << "      10 - 15 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut2_ptCut3") {
      std::cout << "      15 - 20 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut3_ptCut4") {
      std::cout << "      20 - 25 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut4_ptCut5") {
      std::cout << "      25 - 30 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;

      std::cout << "   \\end{tabular}" << std::endl;
      std::cout << "   \\caption{\\small{Performances of the " << isoTitle << " isolation for"
                << " electrons when the prompt efficiency is fixed at $\\geq 0.9$}\\label{tab:" << iso << "_" << id << "_eff}}" << std::endl;
      std::cout << "\\end{table}" << std::endl << std::endl << std::endl << std::endl;
    }
  }
  else if (id == "muon") {
    if (ptCut == "ptCut0_ptCut1") {
      std::cout << std::endl << std::endl << std::endl;

      std::cout << "\\begin{table}[htbp]"             << std::endl;
      std::cout << "   \\centering"                   << std::endl;
      std::cout << "   \\begin{tabular}{|c|c|c|c|c|}" << std::endl;
      std::cout << "      \\hline"                    << std::endl;
      std::cout << "      $p_T$ range (GeV) & Optimal cut & eff & $\\textrm{rej}_{HF}$ & $\\textrm{rej}_{fake}$ \\\\" << std::endl;
      std::cout << "      \\hline"                    << std::endl;

      std::cout << "      3 - 6 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "       << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "       << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "       << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"  << std::endl;
    }
    else if (ptCut == "ptCut1_ptCut2") {
      std::cout << "      6 - 9 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "       << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "       << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "       << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"  << std::endl;
    }
    else if (ptCut == "ptCut2_ptCut3") {
      std::cout << "      9 - 12 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "        << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "        << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "        << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"   << std::endl;
    }
    else if (ptCut == "ptCut3_ptCut4") {
      std::cout << "      12 - 15 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut4_ptCut5") {
      std::cout << "      15 - 18 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut5_ptCut6") {
      std::cout << "      18 - 21 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut6_ptCut7") {
      std::cout << "      21 - 24 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut7_ptCut8") {
      std::cout << "      24 - 27 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;
    }
    else if (ptCut == "ptCut8_ptCut9") {
      std::cout << "      27 - 30 & " << setprecision(3) << optCut           << " & "    << setprecision(3) << optCutEff
                << " $\\pm$ "         << setprecision(2) << optCutEffErr     << " & "    << setprecision(3) << optCutHadRej
                << " $\\pm$ "         << setprecision(2) << optCutHadRejErr  << " & "    << setprecision(3) << optCutFakeRej
                << " $\\pm$ "         << setprecision(2) << optCutFakeRejErr << " \\\\ " << std::endl;
      std::cout << "      \\hline"    << std::endl;

      std::cout << "   \\end{tabular}" << std::endl;
      std::cout << "   \\caption{\\small{Performances of the " << isoTitle << " isolation for"
                << " muons when the prompt efficiency is fixed at $\\geq 0.9$}\\label{tab:" << iso << "_" << id << "_eff}}" << std::endl;
      std::cout << "\\end{table}" << std::endl << std::endl << std::endl << std::endl;
    }
  }

  return optCut;
}

void makeOptHist(Int_t nBins, Double_t* cut, Double_t pt, TString iso, TString id, TString opt)
{
  TCanvas* c = new TCanvas();

  TString isoTitle, idTitle;
  TString histName = iso + "Iso_" + id + "_" + opt;

  TH1D* h = new TH1D(histName, "", nBins, pt, 30.0);

  if      (iso == "track") isoTitle = "track";
  else if (iso == "ecal")  isoTitle = "ECAL";
  else if (iso == "hcal")  isoTitle = "HCAL";
  else if (iso == "comb")  isoTitle = "comb";

  if      (id == "elec") idTitle = "Electrons";
  else if (id == "muon") idTitle = "Muons";

  h->Sumw2();

  for (Int_t i = 1; i <= nBins; i++) {
    h->SetBinContent(i, cut[i - 1]);
    h->SetBinError  (i, 1.0);
  }

  h->Fit("pol1", "e");

  h->GetXaxis()->SetTitle("reco p_{T}");
  h->GetYaxis()->SetTitle(isoTitle + " abs iso " + opt + " cut");

  h->GetYaxis()->SetRangeUser(0.0, 30.0);

  h->GetYaxis()->SetTitleOffset(1.0);

  h->SetTitle(idTitle);

  h->Draw();

  c->SaveAs("./optIsoCut/" + histName + ".png");

  h->Write();
}
