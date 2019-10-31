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

void comvar()
{



  TChain*t1=new TChain("demo/tuple");
  TChain*t2=new TChain("demo/tuple");


  //t1.Add("/home/ashish/data/RunIISummer16MiniAODv3_tuples/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_0.root");
  //t2.Add("/home/ashish/data/RunIISummer16MiniAODv3_tuples/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_0.root");
  //t1.Add("/home/ashish/data/RunIISummer16MiniAODv3_tuples/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_1.root");
  //t2.Add("/home/ashish/data/RunIISummer16MiniAODv3_tuples/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_1.root");
  //t1.Add("/home/ashish/data/RunIISummer16MiniAODv3_tuples/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1_2.root");
  //t2.Add("/home/ashish/data/RunIISummer16MiniAODv3_tuples/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_2.root");
  
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

 TCanvas*C=new TCanvas("compare_variables","");
  C->Print("compare_variables.pdf");

//compare one variable    

                                                                                                                                                                               
  TH1F*H1=new TH1F("H1","",10,0,5);

  //H1->GetYaxis()->SetRange(0,100);
  //H1->GetXaxis()->SetRange(0,50);
 
  H1->GetXaxis()->SetTitle("fj_eta");
  H1->GetYaxis()->SetTitle("number of events normalized");
  
  TH1F*H2=new TH1F("H2","",10,0,5);

  //H2->GetYaxis()->SetRange(0,100);
  //H2->GetXaxis()->SetRange(0,50);

 
  t1->Draw("fj_eta>>H1");
  t2->Draw("fj_eta>>H2");

  H1->Scale(1./H1->Integral());
  H2->Scale(1./H2->Integral());

  H1->SetLineColor(2);
  H2->SetLineColor(1);

  C->Clear();
  H1->Draw("hist");
  H2->Draw("histsame");

  auto legend = new TLegend(0.1,0.7,0.48,0.9);
   //legend->SetHeader("Histograms","C"); 
   legend->AddEntry(H1,"Signal ","l");
   legend->AddEntry(H2,"Background","l");
   legend->Draw("same");
  C->Print("compare_variables.pdf");

}




                                                                                                                                                                     

