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

//taglist from workspaceStd.py
std::vector<TString> taglist={
"TTHDiLeptonTag",
"THQLeptonicTag",
"TTHLeptonicTag_0",
"TTHLeptonicTag_1",
"TTHLeptonicTag_2",
"TTHLeptonicTag_3",
"TTHHadronicTag_0",
"TTHHadronicTag_1",
"TTHHadronicTag_2",
"TTHHadronicTag_3",
"VHHadronicTag",
"VHMetTag",
"VHLeptonicLooseTag",
"WHLeptonicTag",
"ZHLeptonicTag",
"VBFTag_0",
"VBFTag_1",
"VBFTag_2",
"UntaggedTag_0",
"UntaggedTag_1",
"UntaggedTag_2",
"UntaggedTag_3",
};


void plot_flashgg_ws(TString INPUT,TString Sample,TString OUTPUTDIR="."){
  gROOT->ProcessLine(".x tHqCMSAnalysis/flashgg_scripts/rootlogon.C");


  TFile input(INPUT.Data(),"read");
  if(input.IsZombie()){
    cout<<"unable to open input"<<endl;
    return;
  }

  RooWorkspace* ws=(RooWorkspace*)input.Get("tagsDumper/cms_hgg_13TeV");
  if(!ws){
    cout<<"Workspace not found"<<endl;
    return;
  }

  // const RooRealVar* var=(RooRealVar*)ws->var("CMS_hgg_mass");
  // if(!var){
  //   cout<<"variable not found"<<endl;
  //   return;
  // }


  ofstream file;
  file.open(OUTPUTDIR+"/plot_flash_ws_"+Sample+".txt");

  TLatex text;
  text.SetTextSize(0.2);
  text.SetTextColor(4);

  TCanvas C;
  C.Divide(3,7);

  for(int t=0;t<taglist.size();t++){
    RooDataSet * ds=(RooDataSet*)ws->data(Sample+"_13TeV_"+taglist[t]);
    if(!ds){
      cout<<"tag:"<<taglist[t].Data()<<" not found"<<endl;
      continue;
    }

    TString tagname=taglist[t];
    tagname.ReplaceAll("Data_13TeV_","");

    TH1*h=ds->createHistogram("CMS_hgg_mass",40);
    h->SetTitle("");
    h->GetYaxis()->SetTitle("Events");
    h->GetYaxis()->SetNdivisions(2);
    h->GetYaxis()->SetTitleSize(.25);
    h->GetYaxis()->SetTitleOffset(.3);
    h->GetYaxis()->SetLabelSize(.17);
    h->GetYaxis()->SetDecimals(0);
    h->GetYaxis()->SetRangeUser(0,h->GetMaximum()*1.2);
    h->GetXaxis()->SetTitle("m(#gamma#gamma)    [GeV]       ");
    h->GetXaxis()->SetNdivisions(5);
    h->GetXaxis()->SetLabelSize(.2);
    h->GetXaxis()->SetTitleSize(.2);
    h->GetXaxis()->SetTitleOffset(.7);

    TVirtualPad*P=C.cd(t+1);
    P->SetTopMargin(0.05);    
    P->SetBottomMargin(0.35);
    h->Draw("histlp");

    text.DrawLatexNDC(0.5,0.75,tagname);
    
    file<<tagname<<" "<<h->Integral()<<endl;
  }

  file.close();
  C.Print(OUTPUTDIR+"/plot_flash_ws_"+Sample+".gif");
}
