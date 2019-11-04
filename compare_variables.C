
void compare_variables(){

  TChain t1("demo/tuple");
  TChain t2("demo/tuple");
  TChain t3("demo/tuple");
  t1.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_0.root");
  t2.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_0.root");
  t3.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_0.root");


  TCanvas C;
  C.Print("compare_variables.pdf");

  ///compare one variable
  TH1F H1("H1","",20,0,5);
  TH1F H2("H2","",20,0,5);
  TH1F H3("H3","",20,0,5);

H1.SetLineColor(kGreen-3);
H2.SetLineColor(kRed-3);
H3.SetLineColor(kBlue-3);
 t1.Draw("fj_eta>>H1");
 t2.Draw("fj_eta>>H2");
 t3.Draw("fj_eta>>H3");
  H1.Scale(2.14/H1.Integral());
  H2.Scale(68.0/H2.Integral());
  H3.Scale(26.22/H3.Integral());
  C.Clear();
  H2.Draw("hist");
  H1.Draw("histsame");
  H3.Draw("histsame");
  H2.SetAxisRange(0,10,"Y");
  H2.SetAxisRange(0,5,"X");
  H2.SetYTitle("Events");
  H2.SetStats(0);
  H2.SetTitle("#eta Distribution");
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
