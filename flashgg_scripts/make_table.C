#include "globals.h"

std::map<TString, std::map<TString,float> > hyield;
std::map<TString,float> hwidth;
std::map<TString,float> hyieldtot;
std::map<TString,float> hbkgdensity;
std::map<TString,float> hbkg;

////****** helper function *************************/
void make_latextable(TString INPUTDIR){

  ofstream of;
  of.open(INPUTDIR+"/make_table.tex");
  of<<"\\documentclass[11pt]{article}"<<endl;
  of<<"\\usepackage[landscape,top=20pt,bottom=20pt,left=10pt,right=10pt]{geometry}"<<endl;
  of<<"\\begin{document}"<<endl;

  of<<"\\begin{tabular}{| r | c ";
  for(int s=0;s<samples.size();s++)
    of<<" | c ";
  of<<" | c | c | c | }"<<endl;
  of<<"\\hline"<<endl;

  of<<" Category ";
  of<<" & Total ";
  for(int s=0;s<samples.size();s++)
    of<< " & "<<samplenames[samples[s]];
  of<<" & $\\sigma$ [GeV]";
  of<<" & Bkg [GeV$^{-1}$] ";
  of<<" & $S/\\sqrt{S+B}$ \\\\";
  of<<endl;
  of<<"\\hline"<<endl;

  for(int t=0;t<tablelist.size();t++){
    TString tag=tablelist[t];

    TString tagname=tag;
    tagname.ReplaceAll("_"," ");
    tagname.ReplaceAll("Tag","");

    of<<tagname<<" & "<<std::setprecision(1)<<std::fixed<<hyieldtot[tag];

    for(int s=0;s<samples.size();s++)
      of<<" & "<<std::setprecision(2)<<std::fixed<<100*hyield[samples[s]][tag]/hyieldtot[tag]<<" \\% "; 

    //of<<" & "<<std::setprecision(1)<<std::fixed<<hwidth[hwidthmap[tag]][tag];
    of<<" & "<<std::setprecision(1)<<std::fixed<<hwidth[tag];
    
    if(hbkg[tag]>0){
      of<<" & "<<std::setprecision(2)<<std::fixed<<hbkgdensity[tag];
      of<<" & "<<std::setprecision(2)<<std::fixed<<hyieldtot[tag]/sqrt( hyieldtot[tag] + hbkg[tag]); 
    }else{
      of<<" & "<<0;
      of<<" & "<<0;
    }

    of<<" \\\\ ";
    of<<endl;
  }
  of<<"\\hline"<<endl;
  of<<"\\end{tabular}"<<endl;
  of<<"\\end{document}"<<endl;
  of.close();

  system(TString("pdflatex ")+ INPUTDIR+"/make_table.tex ");
  system(TString("/bin/mv ./make_table.pdf ")+ INPUTDIR+"/make_table.pdf ");

}



//******************************************************///
void make_table(TString INPUTDIR){
  gROOT->ProcessLine(".x tHqCMSAnalysis/flashgg_scripts/rootlogon.C");

  //loop over the higgs files
  for(int s=0;s<samples.size();s++){
    ifstream file;
    file.open(INPUTDIR+"/plot_flash_ws_"+samples[s]+".txt");
      
    //loop over the file content
    for(int t=0;t<taglist.size();t++){
      TString cat;
      int entries;
      float yield;
      float par0, par1, par2;
      file>>cat>>entries>>yield>>par0>>par1>>par2;

      if(cat.CompareTo(taglist[t])!=0){
	cout<<"tag does not match: read="<<cat<<"  expected="<<taglist[t]<<" file="<<samples[s]<<endl;
	return;
      } 

      hyield[samples[s]][cat] = yield;
    }
    file.close();
  }


  ////read the higgs fits per category
  for(int t=0;t<taglist.size();t++){
    hyieldtot[taglist[t]]=0.;
  }
  ifstream fileh;
  fileh.open(INPUTDIR+"/fit_higgs.txt");
  for(int t=0;t<taglist.size();t++){
    TString cat;
    int entries;
    float yield;
    float par0, par1, par2;
    fileh>>cat>>entries>>yield>>par0>>par1>>par2;
    
    if(cat.CompareTo(taglist[t])!=0){
      cout<<"tag does not match: read="<<cat<<"  expected="<<taglist[t]<<" file=fit_higgs"<<endl;
      return;
    } 
    
    hwidth[cat] = par2;
    hyieldtot[cat] = yield;
  }    
  fileh.close();
    

  //read the Data/Bkg params
  for(int t=0;t<taglist.size();t++){
    hbkg[taglist[t]]=0.;
  }
  
  ifstream file;
  file.open(INPUTDIR+"/plot_flash_ws_Data.txt");
  for(int t=0;t<taglist.size();t++){
    TString cat;
    int entries;
    float yield;
    float par0, par1, par2;
    file>>cat>>entries>>yield>>par0>>par1>>par2;

    if(cat.CompareTo(taglist[t])!=0){
      cout<<"tag does not match: read="<<cat<<"  expected="<<taglist[t]<<" file=Data"<<endl;
      return;
    } 
    
    
    TF1 fit("fit","[0]+[1]*x+[2]*x*x",100,180);
    fit.SetParameters(par0,par1,par2);
    
    float rangewidth=0.;
    for(int b=1;b<=HMGG.GetNbinsX();b++){
      if( fabs(HMGG.GetBinCenter(b) - 125) <= hwidth[taglist[t]] ){
	hbkg[taglist[t]] += fit.Eval(HMGG.GetBinCenter(b));
	rangewidth += HMGG.GetBinWidth(b);
      }
    }
    hbkgdensity[taglist[t]] = hbkg[taglist[t]] / rangewidth;

  }    
  file.close();

 
  ///make the latex table
  make_latextable(INPUTDIR);

}
