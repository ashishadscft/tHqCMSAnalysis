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


std::vector<TString> samples={"ggh","vbf","tth","bbh","thq","thw","vh"};

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





void fitMgg(TString Sample, TH1* h,ofstream * o){
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

