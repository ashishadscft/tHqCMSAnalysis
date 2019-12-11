
//#include "TFile.h"
//#include "TTree.h"


void what()

{

//TFile*f = new TFile("/home/ashish/TMVA.root");
//f->ls();

//TDirectoryFile*d=(TDirectoryFile*)(dataset->Get("Method_BDT"));
//d->ls();
//TDirectoryFile*t=(TDirectoryFile*)d->Get("BDTG");
//t->ls();

//TH1D*h = new TH1D("h1","Signal Distribution", 10, -1, 1);
//h=(TH1D*)f->Get("MVA_BDTG_S");
//f->Draw("MVA_BDTG_S>>h1");

//f->Draw("MVA_BDTG_S>>h1");
//h1->Draw();

TFile *f = new TFile("/home/ashish/TMVA_n4.root");

//gDirectory->pwd();
f->ls();


TChain*t1=new TChain("dataset/TrainTree");
TChain*t2=new TChain("dataset/TestTree");


TH1D * h1 = new TH1D("h1","Signal Distribution", 100, -1, 1);
TH1D * h2 = new TH1D("h2","Background Distribution", 100, -1, 1);
TH1D * h3 = new TH1D("h3","",100,-1,1);

h1 = (TH1D*)f->Get("dataset/Method_BDT/BDTG/MVA_BDTG_S");
h1->SetLineColor(2);
h1->Draw();

h2 = (TH1D*)f->Get("dataset/Method_BDT/BDTG/MVA_BDTG_B");
h2->SetLineColor(4);
h2->Draw("same");



for (int i = 1; i <= h3->GetNbinsX(); i++) h3->Fill(h3->GetBinCenter(i), TMath::Min(h1->GetBinContent(i), h2->GetBinContent(i)));

cout << h3->Integral()<<endl;
cout << h3->Integral("width")<<endl;

 TCanvas*c2 = new TCanvas("h3","");
 //gStyle->SetOptStat("nemMrRuoisSkK");

 h3->SetNameTitle("h3", "minimum(h1, h2)"); 
   
 h3->Draw();
 
 c2->Print("BDTcommonarea.pdf");

//f->Draw("dataset/Method_BDT/BDTG/MVA_BDTG_S>>h1");
//f->Draw("dataset/Method_BDT/BDTG/MVA_BDTG_B>>h2");


TCanvas*C=new TCanvas;

C->Print("BoostedDecisionTree.png");


t1->Add("/home/ashish/TMVA_n4.root");
t2->Add("/home/ashish/TMVA_n4.root");


TH1F*H1=new TH1F("H1","",30,-1.2,1.2);
TH1F*H2=new TH1F("H2","",30,-1.2,1.2);


t1->Draw("BDTG>>H1");
t2->Draw("BDTG>>H2");

H1->SetLineColor(2);
H2->SetLineColor(1);

t1->Draw("BDTG");
t2->Draw("BDTG");


H1->Scale(1./H1->Integral());
H2->Scale(1./H2->Integral());

H1->Draw("hist");
H2->Draw("histSAME");

TCanvas*c3 = new TCanvas("TestTreehistogram","");
c3->Print("Testhistogram.pdf");

//gStyle->SetOptStat("nemMrRuoisSkK");

C->Print("BoostedDecisionTree.png");



//TFile *f = new TFile("/home/ashish/TMVA_n.root");



TH1D * h8 = new TH1D("h8","ROC Curve", 100, 0, 1);
h8 = (TH1D*)f->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h8->SetLineColor(48);
h8->Draw();

TFile *f1 = new TFile("/home/ashish/TMVA_n1.root");

TH1D * h4 = new TH1D("h4","ROC Curve1", 100, 0, 1);
h4 = (TH1D*)f1->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h4->SetLineColor(2);
h4->Draw("same");


TFile *f2 = new TFile("/home/ashish/TMVA_n2.root");

TH1D * h5 = new TH1D("h5","ROC Curve1", 100, 0, 1);
h5 = (TH1D*)f2->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h5->SetLineColor(3);
h5->Draw("same");

TFile *f3 = new TFile("/home/ashish/TMVA_n3.root");

TH1D * h6 = new TH1D("h4","ROC Curve1", 100, 0, 1);
h6 = (TH1D*)f3->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h6->SetLineColor(4);
h6->Draw("same");



TFile *f4 = new TFile("/home/ashish/TMVA_n4.root");

TH1D * h7 = new TH1D("h5","ROC Curve1", 100, 0, 1);
h7 = (TH1D*)f4->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h7->SetLineColor(6);
h7->Draw("same");

}

