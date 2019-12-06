void bdt(){

TFile *f= new TFile("TMVA.root");

TTree *t = (TTree*)f->Get("dataset/TrainTree");
TTree *t2= (TTree*)f->Get("dataset/TestTree");

TH2F *cs =(TH2F*)f->Get("dataset/CorrelationMatrixS");
TH2F *cb =(TH2F*)f->Get("dataset/CorrelationMatrixB");


TH1F H1("H1","",60,-1,1); //signal
 TH1F H2("H2","",60,-1,1); //background
H1.SetLineColor(kRed);
H2.SetLineColor(kBlue);

t->Draw("BDTG>>H1","classID==0");
t2->Draw("BDTG>>H1","classID==0");
t->Draw("BDTG>>H2","classID==1");
t2->Draw("BDTG>>H2","classID==1");
H1.Scale(1.0/H1.Integral());
H2.Scale(1.0/H2.Integral());

TCanvas *C = new TCanvas("C","C",100,100,1200,900);
H2.Draw("hist");
H1.Draw("histsame");
H2.SetStats(0);
H2.SetXTitle("BDT Discriminant");
H2.SetYTitle("Events normalized to unit area");
auto legend = new TLegend(0.6,0.7,0.65,0.8);
legend->AddEntry("H1","Signal","l");
legend->AddEntry("H2","Background","l");
legend->SetBorderSize(0);
legend->SetTextSize(.05);
legend->SetEntrySeparation(0.5);
legend->Draw();

C->Print("n.eps");
C->Clear();
  //TPad *pad1 = new TPad("pad1","This is pad1",0.2,0.2,0.8,0.8);
  //pad1->Draw();
  //pad1->cd();               // pad1 becomes the current pad]

cs->Draw("colz");
C->SaveAs("CMS.eps");

C->Clear();
  //TPad *pad2 = new TPad("pad2","This is pad1",0.1,0.1,0.9,0.9);
  //pad2->Draw();
  //pad1->cd();               // pad1 becomes the current pad]

cb->Draw("colz");
C->SaveAs("CMB.eps");

}
