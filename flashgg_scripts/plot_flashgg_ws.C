#include "globals.h"

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
  //ws->Print();

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
    if(!(Sample.CompareTo("Data")==0))
      h->Scale(LUMI);
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
      for(int b=1;b<=h->GetNbinsX();b++){
	if(fabs(h->GetBinCenter(b)-125)<10){
	  h->SetBinContent(b,0);
	  h->SetBinError(b,0);
	}
      }
      cout<<Sample.Data()<<"Binning: "<<h->GetXaxis()->GetNbins()<<","<<h->GetXaxis()->GetXmin()<<","<<h->GetXaxis()->GetXmax()<<endl;
    }    

    //write out results
    file<<tagname<<" "<<ds->numEntries()<<" "<<h->Integral();
    TF1*f=fitMgg(Sample,h,&file);
    file<<endl;
  
    //draw again on top of fit
    h->Draw("histp");
    f->Draw("lsame");
    text.DrawLatexNDC(0.5,0.75,tagname);
  }

  file.close();
  C.Print(OUTPUTDIR+"/plot_flash_ws_"+Sample+".gif");
}
