
void compare_variables(){

  TChain t1("demo/tuple");
  TChain t2("demo/tuple");
  TChain t3("demo/tuple");
  TChain t4("demo/tuple");
  TChain t5("demo/tuple");
  TChain t6("demo/tuple");
  TChain t7("demo/tuple");
  TChain t8("demo/tuple");
  TChain t9("demo/tuple");
  TChain t10("demo/tuple");
  TChain t11("demo/tuple");
  TChain t12("demo/tuple");
  TChain t13("demo/tuple");
  TChain t14("demo/tuple");
  TChain t15("demo/tuple");
  TChain t16("demo/tuple");
  TChain t17("demo/tuple");
  TChain t18("demo/tuple");
  TChain t19("demo/tuple");
  TChain t20("demo/tuple");

  t1.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_0.root");
  t2.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_1.root");
  t3.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_2.root");
  t4.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_3.root");
  t5.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_4.root");
  t6.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_5.root");
  t7.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_6.root");
  t8.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_7.root");
  t9.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_8.root");
  t10.Add("_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_9.root");
////////////////////////////////////////////////////////////////////
  t11.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_0.root");
  t12.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_1.root");
  t13.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_2.root");
  t14.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_3.root");
  t15.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_4.root");
  t16.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_5.root");
  t17.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_6.root");
  t18.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_7.root");
  t19.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_8.root");
  t20.Add("_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_9.root");


  TCanvas C;
  C.Print("compare_variables.pdf");

  ///compare one variable
  TH1F H1("H1","",20,-5,5);
  TH1F H2("H2","",20,-5,5);
  TH1F H3("H3","",20,-5,5);
  TH1F H4("H4","",20,-5,5);
  TH1F H5("H5","",20,-5,5);
  TH1F H6("H6","",20,-5,5);
  TH1F H7("H7","",20,-5,5);
  TH1F H8("H8","",20,-5,5);
  TH1F H9("H9","",20,-5,5);
  TH1F H10("H10","",20,-5,5);
  TH1F H11("H1","",20,-5,5);
  TH1F H12("H2","",20,-5,5);
  TH1F H13("H1","",20,-5,5);
  TH1F H14("H2","",20,-5,5);
  TH1F H15("H1","",20,-5,5);
  TH1F H16("H2","",20,-5,5);
  TH1F H17("H1","",20,-5,5);
  TH1F H18("H2","",20,-5,5);
  TH1F H19("H1","",20,-5,5);
  TH1F H20("H2","",20,-5,5);


 t1.Draw("fj_eta>>H1");
 t2.Draw("fj_eta>>H2");
 t3.Draw("fj_eta>>H3");
 t4.Draw("fj_eta>>H4");
 t5.Draw("fj_eta>>H5");
 t6.Draw("fj_eta>>H6");
 t7.Draw("fj_eta>>H7");
 t8.Draw("fj_eta>>H8");
 t9.Draw("fj_eta>>H9");
 t10.Draw("fj_eta>>H10");
 t11.Draw("fj_eta>>H11");
 t12.Draw("fj_eta>>H12");
 t13.Draw("fj_eta>>H13");
 t14.Draw("fj_eta>>H14");
 t15.Draw("fj_eta>>H15");
 t16.Draw("fj_eta>>H16");
 t17.Draw("fj_eta>>H17");
 t18.Draw("fj_eta>>H18");
 t19.Draw("fj_eta>>H19");
 t20.Draw("fj_eta>>H20");
 //t3.Draw("fj_eta>>H3");
  H1.Scale(1.0/H1.Integral());
  H2.Scale(1.0/H2.Integral());
  H3.Scale(1.0/H3.Integral());
  H4.Scale(1.0/H4.Integral());
  H5.Scale(1.0/H5.Integral());
  H6.Scale(1.0/H6.Integral());
  H7.Scale(1.0/H7.Integral());
  H8.Scale(1.0/H8.Integral());
  H9.Scale(1.0/H9.Integral());
  H10.Scale(1.0/H10.Integral());
  H11.Scale(1.0/H11.Integral());
  H12.Scale(1.0/H12.Integral());
  H13.Scale(1.0/H13.Integral());
  H14.Scale(1.0/H14.Integral());
  H15.Scale(1.0/H15.Integral());
  H16.Scale(1.0/H16.Integral());
  H17.Scale(1.0/H17.Integral());
  H18.Scale(1.0/H18.Integral());
  H19.Scale(1.0/H19.Integral());
  H20.Scale(1.0/H20.Integral());

  H1.SetLineColor(kBlue);
  H2.SetLineColor(kBlue);
  H3.SetLineColor(kBlue);
  H4.SetLineColor(kBlue);
  H5.SetLineColor(kBlue);
  H6.SetLineColor(kBlue);
  H7.SetLineColor(kBlue);
  H8.SetLineColor(kBlue);
  H9.SetLineColor(kBlue);
  H10.SetLineColor(kBlue);

H11.SetLineColor(kRed);
H12.SetLineColor(kRed);
H13.SetLineColor(kRed);
H14.SetLineColor(kRed);
H15.SetLineColor(kRed);
H16.SetLineColor(kRed);
H17.SetLineColor(kRed);
H18.SetLineColor(kRed);
H19.SetLineColor(kRed);
H20.SetLineColor(kRed);

  C.Clear();
  H20.Draw("hist");
  H1.Draw("histsame");
    H2.Draw("histsame");
      H3.Draw("histsame");
        H4.Draw("histsame");
          H5.Draw("histsame");
            H6.Draw("histsame");
              H7.Draw("histsame");
                H8.Draw("histsame");
                  H9.Draw("histsame");
                    H10.Draw("histsame");
                      H11.Draw("histsame");
                        H12.Draw("histsame");
                          H13.Draw("histsame");
                            H14.Draw("histsame");
                              H15.Draw("histsame");
                                H16.Draw("histsame");
                                  H17.Draw("histsame");
                                    H18.Draw("histsame");
                                      H19.Draw("histsame");
  //
  H20.SetAxisRange(0,0.2,"Y");
  H20.SetAxisRange(-5,5,"X");
  H20.SetYTitle("Events normalized to unit area");
  H20.SetStats(0);
  H20.SetXTitle("Forward Jet #eta");
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
