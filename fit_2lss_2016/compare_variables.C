
void compare_variables(){


  TChain t1("demo/tuple");
  TChain t2("demo/tuple");


  t1.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_0.root");
  t1.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_1.root");
  t1.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_2.root");
  t1.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_3.root");
  t1.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_4.root");
  t1.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_5.root");
  t1.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_6.root");
  t1.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_7.root");
  t1.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_8.root");
  t1.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_9.root");
////////////////////////////////////////////////////////////////////
  t2.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_0.root");
  t2.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_1.root");
  t2.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_2.root");
  t2.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_3.root");
  t2.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_4.root");
  t2.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_5.root");
  t2.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_6.root");
  t2.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_7.root");
  t2.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_8.root");
  t2.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_9.root");


  TCanvas C;
  C.Print("compare_variables-pt-sub.eps");
  C.Print("compare_variables-pt-sub.png");
  C.Print("compare_variables-pt-sub.pdf");



  ///compare one variable
  TH1F H1("H1","",40,0,200);
  TH1F H2("H2","",40,0,200);

  t1.Draw("l2_pt>>H1");
  t2.Draw("l2_pt>>H2");

  H1.Scale(1.0/H1.Integral());
  H2.Scale(1.0/H2.Integral());

  H1.SetLineColor(kBlue);
  H2.SetLineColor(kRed);

  C.Clear();

  H1.Draw("hist");
  H2.Draw("histsame");

  //
  //H1.SetAxisRange(0,0.05,"Y");
  H1.SetAxisRange(0,150,"X");
  H1.SetYTitle("Events normalized to unit area");
  H1.SetStats(0);
  H1.SetXTitle("pT of subleading lepton");

  auto legend = new TLegend(0.8,0.7,0.86,0.8);
  legend->AddEntry("H1","tHq","l");
  legend->AddEntry("H2","t#bar{t}W","l");
  legend->SetBorderSize(0);
  legend->SetTextSize(.05);
  legend->SetEntrySeparation(0.5);
  legend->Draw();

  C.Print("compare_variables-pt-sub.png");
  C.Print("compare_variables-pt-sub.eps");
  C.Print("compare_variables-pt-sub.pdf");
  //compare correlations
  C.Clear();
  C.Divide(1,2);
  C.cd(1);
  t1.Draw("l1_eta:b1_eta");
  C.cd(2);
  t2.Draw("l1_eta:b1_eta");
  //C.Print("compare_variables.pdf");


 // C.Print("compare_variables.pdf");

}
