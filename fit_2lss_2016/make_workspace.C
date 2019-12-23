#include "RooStats/HistFactory/MakeModelAndMeasurementsFast.h"
#include "TH1D.h"
#include "eps.h"
//////////////
//redistribuite the histogram info
//////////////////
void qw(TH1* ht)
{
for (int i=1;i<=16;i++){
ht->SetBinError(i,sqrt(ht->GetBinContent(i)));
}
}

void make_workspace(){
//load the file that contains the MC simulation.
TFile* f = TFile::Open("plots-thq-2lss-kinMVA.root");
/////////////////////////////////////////////////////
//loads the histograms from the MC
/////////////////////////////////////////////////////
TH1D *tzq =(TH1D*)f->Get("thqMVA_ttv_2lss_40_tZq");
TH1D *ttz =(TH1D*)f->Get("thqMVA_ttv_2lss_40_ttZ");
TH1D *tzw =(TH1D*)f->Get("thqMVA_ttv_2lss_40_tZW");
TH1D *vvv =(TH1D*)f->Get("thqMVA_ttv_2lss_40_VVV");
TH1D *sg =(TH1D*)f->Get("thqMVA_ttv_2lss_40_signal");
TH1D *ttw =(TH1D*)f->Get("thqMVA_ttv_2lss_40_ttW");
TH1D *fakes =(TH1D*)f->Get("thqMVA_ttv_2lss_40_data_fakes");
TH1D *gstar =(TH1D*)f->Get("thqMVA_ttv_2lss_40_Gstar");
TH1D *tth =(TH1D*)f->Get("thqMVA_ttv_2lss_40_ttH");
TH1D *thw =(TH1D*)f->Get("thqMVA_ttv_2lss_40_tHW_hww");
TH1D *zz =(TH1D*)f->Get("thqMVA_ttv_2lss_40_ZZ");
TH1D *ww =(TH1D*)f->Get("thqMVA_ttv_2lss_40_WWss");
TH1D *ww2=(TH1D*)f->Get("thqMVA_ttv_2lss_40_WWDPS");
TH1D *tttt =(TH1D*)f->Get("thqMVA_ttv_2lss_40_tttt");
TH1D *data =(TH1D*)f->Get("thqMVA_ttv_2lss_40_data");
TH1D *wz =(TH1D*)f->Get("thqMVA_ttv_2lss_40_WZ");
TH1D *thq =(TH1D*)f->Get("thqMVA_ttv_2lss_40_tHq_hww");

////////////////////////////////////////////////////////////////
//Scales the histogram to 1
tzq->Scale(5.8/tzq->Integral()); //tzq
vvv->Scale(3/vvv->Integral()); //vvv
ww->Scale(4.0/ww->Integral()); //wwss
ww2->Scale(2.5/ww2->Integral());//wwdps
tttt->Scale(2.3/tttt->Integral()); // tttt
fakes->Scale(80.9/fakes->Integral()); //non prompt
wz->Scale(15.1/wz->Integral()); //WZ
ttz->Scale(25.9/ttz->Integral());//ttZ
ttw->Scale(68/ttw->Integral());//ttW
tth->Scale(24.2/tth->Integral());//tth
tzw->Scale(2.1/tzw->Integral());//tzw
zz->Scale(1.16/zz->Integral()); //zz
//////////////////////////////////////////////
//for SM
/////////////////////////////////////////////
thq->Scale(1.43/thq->Integral());//thq
thw->Scale(0.71/thw->Integral());//thw
///////////////////////////////////////////
//for kt=-1
/////////////////////////////////////////
//thq->Scale(18.5/thq->Integral());//thq
//thw->Scale(7.72/thw->Integral());//thw

///it clones the histogram to later to create another one
TH1F *th=(TH1F*)thq->Clone("th");
th->Add(thw);

TH1F *wwt=(TH1F*)ww->Clone("wwt");
wwt->Add(ww2);

TH1F *tz=(TH1F*)tzq->Clone("tz");
tz->Add(vvv);
tz->Add(tttt);
tz->Add(wwt);
tz->Add(tzw);
tz->Add(zz);

///////////////////////////////////////////////////////////////////
//creates the data to fit. Use in case of real data unavailable.
//In case of having real data, load the information in the histogram section and comment the next lines from 80 to 93
TH1F *hmc=(TH1F*)tth->Clone("hmc");
hmc->Add(tz);
hmc->Add(wz);
hmc->Add(ttw);
hmc->Add(ttz);
hmc->Add(fakes);
hmc->Add(th);
////////////////////////////////////////////////////////////
TH1F *hat = new TH1F("hat","hat",16,-1,1);

for (int i=1;i<=16;i++){
hat->Fill(hmc->GetBinCenter(i), hmc->GetBinContent(i));
}
qw(hat);

////////////////////////////////////////////
//create the histfactory model
RooStats::HistFactory::Measurement meas("kinMVA", "kinMVA");
meas.SetExportOnly(1);
meas.SetPOI("mu");

  // this scales the histogram content, which already includes lumi, so set to 1
  meas.SetLumi(1.0);
  meas.SetLumiRelErr(0.026);
//file eps.h loads the parameters for the model

  //first the signal normalization
RooStats::HistFactory::NormFactor normS;
normS.SetName("mu");
normS.SetHigh(100); // maximum value it can take
normS.SetLow(-33); // minimum value it can take
normS.SetVal(1); // nominal value

//create the SR. Here the data to fit is loaded.
RooStats::HistFactory::Channel SR("SR");
SR.SetData(hat);

//add the signal and background samples300
RooStats::HistFactory::Sample sample_th("th"); //signal thq
sample_th.SetHisto(th);
sample_th.AddNormFactor(normS);
SR.AddSample(sample_th);


RooStats::HistFactory::Sample sample_tth("tth"); //background tth
sample_tth.SetHisto(tth);
sample_tth.AddOverallSys("sample_tth_sys",1./(1+eps_tth),(1+eps_tth));
SR.AddSample(sample_tth);

RooStats::HistFactory::Sample sample_ttz("ttz"); //background ttz
sample_ttz.SetHisto(ttz);
sample_ttz.AddOverallSys("sample_ttz_sys",1./(1+eps_ttz),(1+eps_ttz));
SR.AddSample(sample_ttz);


RooStats::HistFactory::Sample sample_ttw("ttw");
sample_ttw.SetHisto(ttw); //background ttw
sample_ttw.AddOverallSys("sample_ttw_sys",1./(1+eps_ttw),(1+eps_ttw));
SR.AddSample(sample_ttw);

RooStats::HistFactory::Sample sample_tz("tz");
sample_tz.SetHisto(tz);//background tz
sample_tz.AddOverallSys("sample_tz_sys",1./(eps_tz+1),(1+eps_tz));
SR.AddSample(sample_tz);


RooStats::HistFactory::Sample sample_wz("wz");
sample_wz.SetHisto(wz); //background wz
sample_wz.AddOverallSys("sample_wz_sys",1./(eps_wz+1),(1+eps_wz));
SR.AddSample(sample_wz);


RooStats::HistFactory::Sample sample_fakes("fakes");
sample_fakes.SetHisto(fakes);//background fake
sample_fakes.AddOverallSys("sample_fakes_sys",1./(1+eps_fakes),(1+eps_fakes));
SR.AddSample(sample_fakes);

//add the single region to the measurement
meas.AddChannel(SR);

//make the workspace
RooStats::HistFactory::MakeModelAndMeasurementFast(meas);

}
