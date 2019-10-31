#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
#include "TMath.h"

void overlappingareaintegral()
{



  TChain*t1=new TChain("demo/tuple");
  TChain*t2=new TChain("demo/tuple");


  //t1->Add("/home/ashish/data/RunIISummer16MiniAODv3_tuples/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_0.root");
  //t2->Add("/home/ashish/data/RunIISummer16MiniAODv3_tuples/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_0.root");
  //t1->Add("/home/ashish/data/RunIISummer16MiniAODv3_tuples/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_1.root");
  //t2->Add("/home/ashish/data/RunIISummer16MiniAODv3_tuples/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_1.root");
  //t1->Add("/home/ashish/data/RunIISummer16MiniAODv3_tuples/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_2.root");
  //t2->Add("/home/ashish/data/RunIISummer16MiniAODv3_tuples/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_2.root");
  
  t1->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_3.root");
 t2->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_3.root");

   t1->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_4.root");
 t2->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_4.root");

t1->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_5.root");
 t2->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_5.root");

   t1->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_6.root");
t2->Add("/home/ashish/RunIISummer16MiniAODv3_tuples//_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_6.root");

   t1->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_7.root");
 t2->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_7.root");

   t1->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_8.root");
 t2->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_8.root");

   t1->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2_MINIAODSIM_9.root");
 t2->Add("/home/ashish/RunIISummer16MiniAODv3_tuples/_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_MINIAODSIM_9.root");

 
 
//compare one variable    

                                                                                                                                                                               
  TH1F*H1=new TH1F("H1","",20,0,5);
  TH1F*H2=new TH1F("H2","",20,0,5);
  TH1F*H3=new TH1F("H3","",20,0,5);
  t1->Draw("abs(b1_csv)>>H1");
  t1->Print();
  t2->Draw("abs(b1_csv)>>H2"); 
  t2->Print();  
  H1->Scale(1./H1->Integral());
  H2->Scale(1./H2->Integral());
  H1->SetLineColor(2);
  H2->SetLineColor(1);
  H1->Draw("hist");
  H2->Draw("histSAME"); 

  TCanvas*C=new TCanvas("H1","");
  C->Print("overlappingareaintegral.pdf");

for (int i = 1; i <= H3->GetNbinsX(); i++) H3->Fill(H3->GetBinCenter(i), TMath::Min(H1->GetBinContent(i), H2->GetBinContent(i))); 
 cout << H3->Integral()<<endl;
 cout << H3->Integral("width")<<endl;



 gStyle->SetOptStat("nemMrRuoisSkK");

 H3->SetNameTitle("H3", "minimum(H1, H2)"); 
   
 H3->Draw();
 TCanvas*c1 = new TCanvas("H3","");
 c1->Print("morecommonarealessdiscriminatingpower.pdf");

  
}

