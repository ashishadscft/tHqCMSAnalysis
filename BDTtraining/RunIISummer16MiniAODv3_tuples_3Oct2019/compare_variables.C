
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
  C.Print("compare_variables.eps");
  C.Print("compare_variables.png");
  C.Print("compare_variables.pdf");



  ///compare one variable
  TH1F H1("H1","",5,-3,3);
  TH1F H2("H2","",5,-3,3);



 t1.Draw("(l1_ch+l2_ch)>>H1","(l1_ch+l2_ch)!=0>>H1");
 t2.Draw("(l1_ch+l2_ch)>>H2","(l1_ch+l2_ch)!=0>>H2");

  H1.Scale(1.0/H1.Integral());
  H2.Scale(1.0/H2.Integral());

  H1.SetLineColor(kBlue);
  H2.SetLineColor(kRed);

  C.Clear();

  H1.Draw("hist");
  H2.Draw("histsame");

  //
  //H1.SetAxisRange(0,0.2,"Y");
  H1.SetAxisRange(-4,4,"X");
  H1.SetYTitle("Events normalized to unit area");
  H1.SetStats(0);
  H1.SetXTitle("Number of untagged jets with |#eta|>1.0");

  auto legend = new TLegend(0.75,0.75,0.89,0.89);
  legend->AddEntry("H1","tHq","l");
  legend->AddEntry("H2","t#bar{t}W","l");
  legend->SetBorderSize(0);
  legend->SetTextSize(.05);
  legend->SetEntrySeparation(0.5);
  legend->Draw();

  C.Print("compare_variables.png");
  C.Print("compare_variables.eps");
  C.Print("compare_variables.pdf");
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
