#include "globals.h"

const float LUMI=36.5;


void make_table(TString INPUTDIR){
  gROOT->ProcessLine(".x tHqCMSAnalysis/flashgg_scripts/rootlogon.C");

  std::map<TString, std::map<TString,float> > hyield;
  std::map<TString, std::map<TString,float> > hwidth;

  std::map<TString,float> hyieldtot;
  for(int t=0;t<taglist.size();t++){
    hyieldtot[taglist[t]]=0.;
  }

///maps which sample to take the signal width from
std::map<TString,TString> hwidthmap;
hwidthmap["TTHDiLeptonTag"]="tth";
hwidthmap["THQLeptonicTag"]="thq";
hwidthmap["TTHLeptonicTag_0"]="tth";
hwidthmap["TTHLeptonicTag_1"]="tth";
hwidthmap["TTHLeptonicTag_2"]="tth";
hwidthmap["TTHLeptonicTag_3"]="tth";
hwidthmap["TTHHadronicTag_0"]="tth";
hwidthmap["TTHHadronicTag_1"]="tth";
hwidthmap["TTHHadronicTag_2"]="tth";
hwidthmap["TTHHadronicTag_3"]="tth";
hwidthmap["VHHadronicTag"]="vh";
hwidthmap["VHMetTag"]="vh";
hwidthmap["VHLeptonicLooseTag"]="vh";
hwidthmap["WHLeptonicTag"]="vh";
hwidthmap["ZHLeptonicTag"]="vh";
hwidthmap["VBFTag_0"]="vbf";
hwidthmap["VBFTag_1"]="vbf";
hwidthmap["VBFTag_2"]="vbf";
hwidthmap["UntaggedTag_0"]="ggh";
hwidthmap["UntaggedTag_1"]="ggh";
hwidthmap["UntaggedTag_2"]="ggh";
hwidthmap["UntaggedTag_3"]="ggh";


  //loop over the files
  for(int s=0;s<samples.size();s++){
    TString sample=samples[s];

    ifstream file;
    if(sample.CompareTo("vh")==0)
      file.open(INPUTDIR+"/plot_flash_ws_"+sample+".txt");
    else file.open(INPUTDIR+"/plot_flash_ws_"+sample+"_.txt");

    //loop over the file content
    for(int t=0;t<taglist.size();t++){
      TString tag=taglist[t];

      TString cat;
      int entries;
      float yield;
      float par0, par1, par2;
      file>>cat>>entries>>yield>>par0>>par1>>par2;

      //if(cat.CompareTo(tag)==0)
      //cout<<tag<<" "<<yield<<endl;

      hyield[sample][tag]=LUMI*yield;
      hwidth[sample][tag]=par2;

      hyieldtot[tag]+=LUMI*yield;
    }
    file.close();
  }


  //read the Data params
  std::map<TString,float> hbkg;
  for(int t=0;t<taglist.size();t++){
    hbkg[taglist[t]]=0.;
  }
  
  ifstream file;
  file.open(INPUTDIR+"/plot_flash_ws_Data.txt");
  for(int t=0;t<taglist.size();t++){
    TString tag=taglist[t];
    
    TString cat;
    int entries;
    float yield;
    float par0, par1, par2;
    file>>cat>>entries>>yield>>par0>>par1>>par2;
    
    TF1 fit("fit","[0]+[1]*x+[2]*x*x",100,180);
    fit.SetParameters(par0,par1,par2);
    
    //for this tag, calculate the bkg around m=125
    hbkg[taglist[t]] = fit.Integral(125-hwidth[hwidthmap[taglist[t]]][taglist[t]],
				    125+hwidth[hwidthmap[taglist[t]]][taglist[t]]);
  
  }    
    


  ///now print out in tag list order
  ofstream of;
  of.open(INPUTDIR+"/make_table.tex");
  of<<"\\documentclass[11pt]{article}"<<endl;
  of<<"\\usepackage[landscape,top=20pt,bottom=20pt,left=10pt,right=10pt]{geometry}"<<endl;
  of<<"\\begin{document}"<<endl;
  of<<"\\begin{tabular}{| c | c ";
  for(int s=0;s<samples.size();s++)
    of<<" | c ";
  of<<" | c | c | c | }"<<endl;
  of<<"\\hline"<<endl;

  of<<" Category ";
  of<<" & Total ";
  for(int s=0;s<samples.size();s++)
    of<< " & "<<samples[s];
  of<<" & width [GeV]";
  of<<" & Bkg ";
  of<<" & Significance \\\\";
  of<<endl;
  of<<"\\hline"<<endl;

  for(int t=1;t<=taglist.size();t++){
    TString tag=taglist[taglist.size()-t];

    TString tagname=tag;
    tagname.ReplaceAll("_"," ");

    of<<tagname<<" & "<<std::setprecision(1)<<std::fixed<<hyieldtot[tag];

    for(int s=0;s<samples.size();s++)
      of<<" & "<<std::setprecision(2)<<std::fixed<<100*hyield[samples[s]][tag]/hyieldtot[tag]<<" \\% "; 

    of<<" & "<<std::setprecision(1)<<std::fixed<<hwidth[hwidthmap[tag]][tag];
    of<<" & "<<std::setprecision(1)<<std::fixed<<hbkg[tag];
    of<<" & "<<std::setprecision(2)<<std::fixed<<hyieldtot[tag]/sqrt(hyieldtot[tag]+hbkg[tag]); 
    //if(t<taglist.size()) 
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
