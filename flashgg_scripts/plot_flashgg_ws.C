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


void fitmgg(TString Sample, TH1* h,ofstream * o){
  TF1* f=NULL;
  float fmin,fmax;
  if(Sample.CompareTo("Data")==0){
    fmin=h->GetXaxis()->GetXmin();
    fmax=h->GetXaxis()->GetXmax();
    f=new TF1("fit","[0]+[1]*x+[2]*x*x",fmin,fmax);
  }else {
    fmin=115;
    fmax=135;
    f=new TF1("fit","[0]*exp(-0.5*(x-[1])**2/[2]**2)",fmin,fmax);
    //f->SetParameter(0,1);
    f->SetParameter(1,125);
    f->SetParameter(2,1);
    f->SetParLimits(1,120,130);
    f->SetParLimits(2,1.,10);
  }
  h->Fit(f,"QNLL","",fmin,fmax);
  h->Fit(f,"Q","",fmin,fmax);
  f->SetLineColor(2);
  f->Draw("lsame");
  (*o)<<" "<<f->GetParameter(0)<<" "<<f->GetParameter(1)<<" "<<f->GetParameter(2);
}

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
  ws->Print();

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
    TString tagname=taglist[t];

    RooDataSet * ds=(RooDataSet*)ws->data(Sample+"_13TeV_"+tagname);
    if(!ds){
      cout<<"tag:"<<tagname<<" not found"<<endl;
      continue;
    }
    //ds->Print();

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


    ///blind
    if(Sample.CompareTo("Data")==0){
      for(int b=1;b<=h->GetNbinsX();b++)
	if(fabs(h->GetBinCenter(b)-125)<10){
	  h->SetBinContent(b,0);
	  h->SetBinError(b,0);
	}
    }    

    //draw first pass
    h->Draw("histp");
    
    //write out results
    file<<tagname<<" "<<ds->numEntries()<<" "<<h->Integral();
    fitmgg(Sample,h,&file);
    file<<endl;
  
    //draw again on top of fit
    h->Draw("histpsame");
    text.DrawLatexNDC(0.5,0.75,tagname);
  }

  file.close();
  C.Print(OUTPUTDIR+"/plot_flash_ws_"+Sample+".gif");
}
