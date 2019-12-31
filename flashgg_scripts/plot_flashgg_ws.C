#include "globals.h"
#include <dirent.h>
#include <sys/types.h>


std::vector<TFile*> files;
std::vector<RooWorkspace*> workspace;

void read_ws(TString INPUT,TString Sample){
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (INPUT.Data())) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      if(TString(ent->d_name).Contains(Sample)){
	cout<<ent->d_name<<endl;
	
	TFile *f=new TFile(INPUT+"/"+ent->d_name,"read");
	if(f->IsZombie()){
	  cout<<ent->d_name<<" is bad"<<endl;
	  continue;
	}

	RooWorkspace* w=(RooWorkspace*)f->Get("tagsDumper/cms_hgg_13TeV");
	if(!w){
	  cout<<" No workspace in"<<ent->d_name<<endl;
	  continue;
	}
	files.push_back(f);
	workspace.push_back(w);
      }
    }
    closedir (dir);
  }
}


void plot_flashgg_ws(TString INPUT,TString Sample,TString OUTPUTDIR="."){
  gROOT->ProcessLine(".x tHqCMSAnalysis/flashgg_scripts/rootlogon.C");


  TLatex text;
  text.SetTextSize(0.2);
  text.SetTextColor(4);


  ofstream file;
  file.open(OUTPUTDIR+"/plot_flash_ws_"+Sample+".txt");

  ///Read the workspaces
  read_ws(INPUT,Sample);

  ///check if any files
  if(workspace.size()==0){
    for(int t=0;t<taglist.size();t++)
      file<<taglist[t]<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<endl;;

    return;
  }



  TCanvas C;
  C.Divide(3,7);
  for(int t=0;t<taglist.size();t++){
    TVirtualPad*P=C.cd(t+1);
    P->SetTopMargin(0.05);    
    P->SetBottomMargin(0.35);

    ///sum the workspaces
    TH1*h=NULL;
    for(int w=0;w<workspace.size();w++){
      RooDataSet * ds=(RooDataSet*)workspace[w]->data(Sample+"_13TeV_"+taglist[t]);
      if(!ds){
	cout<<"tag: not found"<<endl;
	continue;
      }

      TH1*H=ds->createHistogram("CMS_hgg_mass",HMGG.GetNbinsX());
      H->SetName(TString("CMS_hgg_mass")+taglist[t]+(long)w);
      if(!(Sample.CompareTo("Data")==0))
	H->Scale(LUMI(OUTPUTDIR));

      if(h==NULL) h=H;
      else h->Add(H);
    }
    if(h==NULL) continue;

    ///blind
    if(Sample.CompareTo("Data")==0){
      for(int b=1;b<=h->GetNbinsX();b++){
	if(fabs(h->GetBinCenter(b)-125)<10){
	  h->SetBinContent(b,0);
	  h->SetBinError(b,0);
	}
      }
    }    


    //write out results
    file<<taglist[t]<<" "<<h->GetEntries()<<" "<<h->Integral();
    TF1*f=fitMgg(Sample,h,&file);
    file<<endl;
  

    ///graph
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
    h->Draw("histp");
    f->Draw("lsame");
    text.DrawLatexNDC(0.5,0.75,taglist[t]);
  }

  file.close();
  C.Print(OUTPUTDIR+"/plot_flash_ws_"+Sample+".gif");
}
