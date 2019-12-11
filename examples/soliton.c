//#include "TFile.h"
//#include "TTree.h"

void soliton()
{


TFile *f = new TFile("/home/ashish/TMVA_n.root");

TH1D * h1 = new TH1D("h1","ROC Curve", 1000, 0, 1);
h1 = (TH1D*)f->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h1->SetLineColor(48); //Brown
h1->Draw();


TFile *f1 = new TFile("/home/ashish/TMVA_n1.root");

TH1D * h2 = new TH1D("h2","ROC Curve1", 1000, 0, 1);
h2 = (TH1D*)f1->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h2->SetLineColor(2); //Red
h2->Draw("same");


TFile *f2 = new TFile("/home/ashish/TMVA_n2.root");

TH1D * h3 = new TH1D("h3","ROC Curve1", 1000, 0, 1);
h3 = (TH1D*)f2->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h3->SetLineColor(50); //Flourescent Green
h3->Draw("same");

TFile *f3 = new TFile("/home/ashish/TMVA_n3.root");

TH1D * h4 = new TH1D("h4","ROC Curve1", 1000, 0, 1);
h4 = (TH1D*)f3->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h4->SetLineColor(4); //Blue
h4->Draw("same");



TFile *f4 = new TFile("/home/ashish/TMVA_n4.root");

TH1D * h5 = new TH1D("h5","ROC Curve1", 1000, 0, 1);
h5 = (TH1D*)f4->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h5->SetLineColor(6); //Magenta
h5->Draw("same");


TFile *f5 = new TFile("/home/ashish/TMVA_n5.root");

TH1D * h6 = new TH1D("h6","ROC Curve1", 1000, 0, 1);
h6 = (TH1D*)f5->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h6->SetLineColor(8); //Green
h6->Draw("same");


TFile *f6 = new TFile("/home/ashish/TMVA_n6.root");

TH1D * h7 = new TH1D("h7","ROC Curve1", 1000, 0, 1);
h7 = (TH1D*)f6->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h7->SetLineColor(28); 
h7->Draw("same");

TFile *f7 = new TFile("/home/ashish/TMVA_n7.root");

TH1D * h8 = new TH1D("h8","ROC Curve1", 1000, 0, 1);
h8 = (TH1D*)f7->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h8->SetLineColor(46); 
h8->Draw("same");

TFile *f8 = new TFile("/home/ashish/TMVA_n8.root");

TH1D * h9 = new TH1D("h9","ROC Curve1", 1000, 0, 1);
h9 = (TH1D*)f8->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h9->SetLineColor(41); 
h9->Draw("same");

TFile *f5 = new TFile("/home/ashish/TMVA_n15.root");

TH1D * h6 = new TH1D("h6","ROC Curve1", 1000, 0, 1);
h6 = (TH1D*)f5->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h6->SetLineColor(7); //Blue
h6->Draw("same");

TFile *f6 = new TFile("/home/ashish/TMVA_n15.root");

TH1D * h7 = new TH1D("h7","ROC Curve1", 1000, 0, 1);
h7 = (TH1D*)f6->Get("dataset/Method_BDT/BDTG/MVA_BDTG_rejBvsS");
h7->SetLineColor(12); //Grey
h7->Draw("same");


}






