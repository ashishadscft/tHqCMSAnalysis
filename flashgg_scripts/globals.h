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


float LUMI(TString INDIR){
  if(INDIR.Contains("Era2016") ) return 35.9;
  if(INDIR.Contains("Era2017") ) return 41.5;
  if(INDIR.Contains("Era2018") ) return 63.7;
  return 0.;
}

TH1F HMGG("HMGG","",40,100,180);//binning for m(gg) histograms 

std::vector<TString> samples={"ggh_","vbf_","tth_","bbh_","thq_","thw_","vh"};
std::map<TString,TString> samplenames={{"ggh_","ggH"},{"vbf_","VBF"},{"tth_","ttH"},{"bbh_","bbH"},{"thq_","tHq"},{"thw_","tHW"},{"vh","VH"}};

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

std::vector<TString> tablelist={
"UntaggedTag_0",
"UntaggedTag_1",
"UntaggedTag_2",
"UntaggedTag_3",
"VBFTag_0",
"VBFTag_1",
"VBFTag_2",
"TTHHadronicTag_0",
"TTHHadronicTag_1",
"TTHHadronicTag_2",
"TTHHadronicTag_3",
"TTHDiLeptonTag",
"TTHLeptonicTag_0",
"TTHLeptonicTag_1",
"TTHLeptonicTag_2",
"TTHLeptonicTag_3",
"ZHLeptonicTag",
"WHLeptonicTag",
"VHLeptonicLooseTag",
"VHHadronicTag",
"VHMetTag",
"THQLeptonicTag",
};


///maps which sample to take the signal width from
std::map<TString,TString> hwidthmap = {
{"TTHDiLeptonTag","tth_"},
{"THQLeptonicTag","thq_"},
{"TTHLeptonicTag_0","tth_"},
{"TTHLeptonicTag_1","tth_"},
{"TTHLeptonicTag_2","tth_"},
{"TTHLeptonicTag_3","tth_"},
{"TTHHadronicTag_0","tth_"},
{"TTHHadronicTag_1","tth_"},
{"TTHHadronicTag_2","tth_"},
{"TTHHadronicTag_3","tth_"},
{"VHHadronicTag","vh"},
{"VHMetTag","vh"},
{"VHLeptonicLooseTag","vh"},
{"WHLeptonicTag","vh"},
{"ZHLeptonicTag","vh"},
{"VBFTag_0","vbf_"},
{"VBFTag_1","vbf_"},
{"VBFTag_2","vbf_"},
{"UntaggedTag_0","ggh_"},
{"UntaggedTag_1","ggh_"},
{"UntaggedTag_2","ggh_"},
{"UntaggedTag_3","ggh_"},
};



TF1* fitMgg(TString Sample, TH1* h,ofstream * o){
  if(!h){cout<<" fitMgg h=NULL "<<Sample<<endl; return NULL;}

  TF1* f=NULL;
  float fmin,fmax;
  if(Sample.CompareTo("Data")==0){
    fmin=h->GetXaxis()->GetXmin();
    fmax=h->GetXaxis()->GetXmax();
    f=new TF1("fit","[0]+[1]*x+[2]*x*x",fmin,fmax);
  }else {
    fmin=125-2*h->GetRMS();
    fmax=125+2*h->GetRMS();
    f=new TF1("fit","[0]*exp(-0.5*(x-[1])**2/[2]**2)",fmin,fmax);
    //f->SetParameter(0,1);
    f->SetParameter(1,125);
    f->SetParameter(2,1);
    f->SetParLimits(1,120,130);
    f->SetParLimits(2,0.5,10);
  }
  h->Fit(f,"QNLL","",fmin,fmax);
  h->Fit(f,"Q","",fmin,fmax);
  f->SetLineColor(2);
  //f->Draw("lsame");

  if(o)
    (*o)<<" "<<f->GetParameter(0)<<" "<<f->GetParameter(1)<<" "<<f->GetParameter(2);


  return f;
}


