
void compare_variables(){


  
  TChain t1("demo/tuple");
  TChain t2("demo/tuple");

  t1.Add("THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root");
  t2.Add("TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");



  TCanvas C;
  C.Print("compare_variables.pdf[");

  ///compare one variable 
  TH1F H1("H1","",20,0,5);
  TH1F H2("H2","",20,0,5);
  t1.Draw("abs(fj_eta)>>H1");
  t2.Draw("abs(fj_eta)>>H2");
  H1.Scale(1./H1.Integral());
  H2.Scale(1./H2.Integral());
  C.Clear();
  H1.Draw("hist");
  H2.Draw("histsame");
  C.Print("compare_variables.pdf");

  //compare correlations 
  C.Clear();
  C.Divide(1,2);
  C.cd(1);
  t1.Draw("l1_eta:b1_eta");
  C.cd(2);
  t2.Draw("l1_eta:b1_eta");
  C.Print("compare_variables.pdf");

  
  C.Print("compare_variables.pdf]");
  
}
