void bdt(){

TFile *f= new TFile("TMVA.root");
TFile *d= new TFile("TMVA6.root");
TFile *q= new TFile("TMVA8.root");
/////////////////////////
///4 variables//////
TTree *t = (TTree*)f->Get("dataset/TrainTree");
TTree *t2= (TTree*)f->Get("dataset/TestTree");
/////////////////////////
///6 variables//////
TTree *t3 = (TTree*)d->Get("dataset/TrainTree");
TTree *t4= (TTree*)d->Get("dataset/TestTree");
/////////////////////////
///8 variables//////
TTree *t5 = (TTree*)q->Get("dataset/TrainTree");
TTree *t6= (TTree*)q->Get("dataset/TestTree");
//////////////////////////////////////////////
TH2F *cs =(TH2F*)f->Get("dataset/CorrelationMatrixS");
TH2F *cb =(TH2F*)f->Get("dataset/CorrelationMatrixB");


TH1F H1("H1","",40,-1,1); //signal
TH1F H2("H2","",40,-1,1); //background

TH1F H3("H3","",40,-1,1); //signal
TH1F H4("H4","",40,-1,1); //background

TH1F H5("H5","",40,-1,1); //signal
TH1F H6("H6","",40,-1,1); //background

H1.SetLineColor(kRed);
H2.SetLineColor(kBlue);
H3.SetLineColor(kRed+4);
H4.SetLineColor(kBlue+4);
H5.SetLineColor(kAzure+3);
H6.SetLineColor(kGreen+3);

t->Draw("BDTG>>H1","classID==0");
t2->Draw("BDTG>>H1","classID==0");
t->Draw("BDTG>>H2","classID==1");
t2->Draw("BDTG>>H2","classID==1");

t3->Draw("BDTG>>H3","classID==0");
t4->Draw("BDTG>>H3","classID==0");
t3->Draw("BDTG>>H4","classID==1");
t4->Draw("BDTG>>H4","classID==1");

t5->Draw("BDTG>>H5","classID==0");
t6->Draw("BDTG>>H5","classID==0");
t5->Draw("BDTG>>H6","classID==1");
t6->Draw("BDTG>>H6","classID==1");



H1.Scale(1.0/H1.Integral());
H2.Scale(1.0/H2.Integral());

H3.Scale(1.0/H3.Integral());
H4.Scale(1.0/H4.Integral());

H5.Scale(1.0/H5.Integral());
H6.Scale(1.0/H6.Integral());

TCanvas *C = new TCanvas("C","C",100,100,1200,900);
H6.Draw("hist");
H1.Draw("histsame");
H3.Draw("histsame");
H5.Draw("histsame");
H2.Draw("histsame");
H4.Draw("histsame");

H6.SetStats(0);
H6.SetXTitle("BDT Discriminant");
H6.SetYTitle("Events normalized to unit area");
  H6.SetAxisRange(0,0.1,"Y");
//H2.SetTitle("BDT Training 2 variables");
auto legend = new TLegend(0.7,0.6,0.8,0.8);
legend->AddEntry("H1","4 variables","l");
legend->AddEntry("H3","6 variables","l");
legend->AddEntry("H5","8 variables ","l");
legend->SetHeader("Signal","C");

legend->SetBorderSize(1);
legend->SetTextSize(.02);
legend->SetEntrySeparation(0.5);
legend->Draw();

auto legend2 = new TLegend(0.55,0.6,0.65,0.8);
legend2->AddEntry("H2","4 variables ","l");
legend2->AddEntry("H4","6 variables","l");
legend2->AddEntry("H6","8 variables","l");
legend2->SetHeader("Background","C");

legend2->SetBorderSize(1);
legend2->SetTextSize(.02);
legend2->SetEntrySeparation(0.5);
legend2->Draw();


C->Print("bdt-2var.eps");
C->Print("bdt-2var.png");

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
