#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooCategory.h"
#include "RooEfficiency.h"
#include "RooPolynomial.h"
#include "RooProdPdf.h"
#include "RooFormulaVar.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"
#include "RooPlot.h"
using namespace RooFit ;


std::vector<TString> taglist={
"Data_13TeV_TTHDiLeptonTag",
"Data_13TeV_THQLeptonicTag",
"Data_13TeV_TTHLeptonicTag_0",
"Data_13TeV_TTHLeptonicTag_1",
"Data_13TeV_TTHLeptonicTag_2",
"Data_13TeV_TTHLeptonicTag_3",
"Data_13TeV_TTHHadronicTag_0",
"Data_13TeV_TTHHadronicTag_1",
"Data_13TeV_TTHHadronicTag_2",
"Data_13TeV_TTHHadronicTag_3",
"Data_13TeV_VHHadronicTag",
"Data_13TeV_VHMetTag",
"Data_13TeV_VHLeptonicLooseTag",
"Data_13TeV_WHLeptonicTag",
"Data_13TeV_ZHLeptonicTag",
"Data_13TeV_VBFTag_0",
"Data_13TeV_VBFTag_1",
"Data_13TeV_VBFTag_2",
"Data_13TeV_UntaggedTag_0",
"Data_13TeV_UntaggedTag_1",
"Data_13TeV_UntaggedTag_2",
"Data_13TeV_UntaggedTag_3",
//"Data_13TeV_NoTag",
};

//from workspaceStd.py
//  ["NoTag",0],
//  ["UntaggedTag",4],
//  ["VBFTag",3],
//  ["ZHLeptonicTag",0],
//  ["WHLeptonicTag",0],
//  ["VHLeptonicLooseTag",0],
//  ["VHMetTag",0],
//  ["VHHadronicTag",0],
//  ["TTHHadronicTag",4],
//  ["TTHLeptonicTag",4],
//  ["THQLeptonicTag",0],
//  ["TTHDiLeptonTag",0]



void plot_flashgg_ws(TString INPUT,TString OUTPUTDIR="."){

  TFile input(INPUT.Data(),"read");
  RooWorkspace* ws=(RooWorkspace*)input.Get("tagsDumper/cms_hgg_13TeV");
  if(!ws){
    cout<<"Workspace not found"<<endl;
  }
  //ws->Print();

  const RooRealVar* var=(RooRealVar*)ws->var("CMS_hgg_mass");
  if(!var){
    cout<<"variable not found"<<endl;
  }


  
  TCanvas C;
  C.Divide(3,7);

  for(int t=0;t<taglist.size();t++){
    //cout<<taglist[t].Data()<<endl;
    RooDataSet * ds=(RooDataSet*)ws->data(taglist[t].Data());
    if(!ds){
      cout<<"tag:"<<taglist[t].Data()<<" not found"<<endl;
      continue;
    }
    //ds->Print();


    TString tagname=taglist[t];
    tagname.ReplaceAll("Data_13TeV_","");

    TH1*h=ds->createHistogram("CMS_hgg_mass",20);
    h->SetTitle("");
    h->GetYaxis()->SetTitle("Events");
    h->GetYaxis()->SetNdivisions(2);
    h->GetYaxis()->SetTitleSize(.25);
    h->GetYaxis()->SetTitleOffset(.3);
    h->GetYaxis()->SetLabelSize(.17);
    h->GetYaxis()->SetDecimals(0);
    h->GetYaxis()->SetRangeUser(0,h->GetMaximum()*1.2);
    h->GetXaxis()->SetTitle(tagname+"   m(#gamma#gamma) ");
    h->GetXaxis()->SetNdivisions(5);
    h->GetXaxis()->SetLabelSize(.2);
    h->GetXaxis()->SetTitleSize(.2);
    h->GetXaxis()->SetTitleOffset(.7);

    TVirtualPad*P=C.cd(t+1);
    P->SetTopMargin(0.05);    
    P->SetBottomMargin(0.35);
    h->Draw("histpe");
    cout<<taglist[t].Data()<<" "<<h->Integral()<<endl;
  }
  
  C.Print(OUTPUTDIR+"/plot_flash_ws.gif");
}
