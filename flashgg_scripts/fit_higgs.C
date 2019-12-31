#include "globals.h"

void fit_higgs(TString INPUT,TString OUTPUTDIR="."){
  gROOT->ProcessLine(".x tHqCMSAnalysis/flashgg_scripts/rootlogon.C");

  std::map<TString,TH1F*> hist;
  for(int t=0;t<taglist.size();t++){
    hist[taglist[t]]=(TH1F*)HMGG.Clone(TString(HMGG.GetName())+taglist[t]);
    hist[taglist[t]]->SetTitle("");
    hist[taglist[t]]->GetYaxis()->SetTitle("Events");
    hist[taglist[t]]->GetYaxis()->SetNdivisions(2);
    hist[taglist[t]]->GetYaxis()->SetTitleSize(.25);
    hist[taglist[t]]->GetYaxis()->SetTitleOffset(.3);
    hist[taglist[t]]->GetYaxis()->SetLabelSize(.17);
    hist[taglist[t]]->GetYaxis()->SetDecimals(0);
    hist[taglist[t]]->GetYaxis()->SetMaxDigits(3);
    hist[taglist[t]]->GetXaxis()->SetTitle("m(#gamma#gamma)    [GeV]       ");
    hist[taglist[t]]->GetXaxis()->SetNdivisions(5);
    hist[taglist[t]]->GetXaxis()->SetLabelSize(.2);
    hist[taglist[t]]->GetXaxis()->SetTitleSize(.2);
    hist[taglist[t]]->GetXaxis()->SetTitleOffset(.7);
    hist[taglist[t]]->SetMarkerStyle(8);
    hist[taglist[t]]->SetMarkerSize(0.5);
  }  




  //loop over the samples
  for(int s=0;s<samples.size();s++){
    TFile input(INPUT+"/"+samples[s]+".root","read");
    if(input.IsZombie()){
      cout<<"unable to open input"<<endl;
      continue;
    }

    RooWorkspace* ws=(RooWorkspace*)input.Get("tagsDumper/cms_hgg_13TeV");
    if(!ws){
      cout<<"Workspace not found"<<endl;
      return;
    }
    
    //loop over the categories
    for(int t=0;t<taglist.size();t++){
      RooDataSet * ds=(RooDataSet*)ws->data(samples[s]+"_13TeV_"+taglist[t]);
      if(!ds){
	cout<<"tag: "<<taglist[t]<<" not found"<<endl;
	return;
      }
      
      TH1*h=ds->createHistogram("CMS_hgg_mass",40);
      h->Scale(LUMI(OUTPUTDIR));
      hist[taglist[t]]->Add(h);
    }
  }
   

  ///fit and write out the fit results
  ofstream file;
  file.open(OUTPUTDIR+"/fit_higgs.txt");
  std::map<TString,TF1*> fits;
  for(int t=0;t<taglist.size();t++){
    //write out results
    file<<taglist[t]<<" "<<hist[taglist[t]]->GetEntries()<<" "<<hist[taglist[t]]->Integral();
    TF1*f=fitMgg(taglist[t],hist[taglist[t]],&file);
    file<<endl;
    fits[taglist[t]]=f;
  }
  file.close();


  /////Draw the fits
  TLatex text;
  text.SetTextSize(0.2);
  text.SetTextColor(4);

  TCanvas C;
  C.Divide(3,7);
  for(int t=0;t<taglist.size();t++){
    TVirtualPad*P=C.cd(t+1);
    P->SetTopMargin(0.05);    
    P->SetBottomMargin(0.35);

    hist[taglist[t]]->GetYaxis()->SetRangeUser(0,hist[taglist[t]]->GetMaximum()*1.2);
    hist[taglist[t]]->Draw("histp");
    fits[taglist[t]]->Draw("lsame");

    TString label=taglist[t];
    label.ReplaceAll("Tag","");
    label.ReplaceAll("_"," ");
    text.DrawLatexNDC(0.6,0.75,label);
  }
  C.Print(OUTPUTDIR+"/fit_higgs.gif");

}
