    #include "RooWorkspace.h"
    #include "RooStats/ModelConfig.h"
    #include "RooRealVar.h"
    #include "RooMinimizerFcn.h"
    #include "RooNLLVar.h"
    #include "TFile.h"
    #include "minimize.C"
    #include <iostream>
    #include "eps.h"

    using namespace std;
    using namespace RooFit;
    using namespace RooStats;
    //////////////
    //redistribuite the histogram info
    //////////////////
    void qw(TH1* ht)
    {
      for (int i=1;i<=16;i++)
      {
        ht->SetBinError(i,sqrt(ht->GetBinContent(i)));
      }
    }

    void fit_workspace(string version, int strategy=0)
    {
      //Open the file, grab the workspace
      TFile* f = new TFile(Form("_combined_kinMVA_model.root",version.c_str(),version.c_str()));
    //combined is where the model and data are saved
      RooWorkspace* w = (RooWorkspace*)f->Get("combined");
      if (!w){
        cout << "ERROR::Workspace doesn't exist! Check file name" << endl;
        exit(1);
      }
      //Grab the ModelConfig and the data
      ModelConfig* mc = (ModelConfig*)w->obj("ModelConfig");
      RooDataSet* data = (RooDataSet*)w->data("obsData");

      //Configure MINUIT. MINUIT contains the tools to make a numerical minimization
      ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
      ROOT::Math::MinimizerOptions::SetDefaultStrategy(strategy);
      ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(1);

      //Put the NPs and POIs into one set to send to the NLL
      RooArgSet params(*mc->GetNuisanceParameters(),*mc->GetParametersOfInterest());

      //Build the NLL (negative logarith likelihood )
      RooNLLVar* nll = (RooNLLVar*)mc->GetPdf()->createNLL(*data, Constrain(params),
    						       GlobalObservables(*mc->GetGlobalObservables()),
    						       RooFit::Offset(1));
    ////////////////////////////////////////////////////////////////////////////////
    //Load the parameters of interest
      RooAbsArg* a1 =params.find("alpha_sample_ttz_sys");
      RooAbsArg* a2 =params.find("alpha_sample_fakes_sys");
      RooAbsArg* a3 =params.find("alpha_sample_tth_sys");
      RooAbsArg* a4 =params.find("alpha_sample_ttw_sys");
      RooAbsArg* a5 =params.find("alpha_sample_wz_sys");
      RooAbsArg* a6 =params.find("alpha_sample_tz_sys");
      RooAbsArg* a7 =params.find("mu");
      RooAbsArg* a8 =params.find("Lumi");

      RooRealVar* alpha_ttz=(RooRealVar*)a1; //ttz
      RooRealVar* alpha_fakes=(RooRealVar*)a2; //non prompt leptons (fakes)
      RooRealVar* alpha_tth=(RooRealVar*)a3; //tth
      RooRealVar* alpha_ttw=(RooRealVar*)a4;  //ttw
      RooRealVar* alpha_wz=(RooRealVar*)a5; //wz
      RooRealVar* alpha_tz=(RooRealVar*)a6;  //tz
      RooRealVar* alpha_mu=(RooRealVar*)a7; //signal
      RooRealVar* lumi=(RooRealVar*)a8;
    //////////////////////////////////////////////////////////////
      //Do the minimization and save the RooFitResult
    /// get RooArgSet containing the nuisance parameters (return NULL if not existing)
    // const RooArgSet * GetNuisanceParameters() const { return (GetWS()) ? GetWS()->set(fNuisParamsName.c_str()) : 0; }
    //Definition in macros/minimize.C:
      RooFitResult* minimize(RooAbsReal* fcn, bool save=0, int retry_mode=3, int* ret_status=NULL);
    ////fit the model and the data
      RooFitResult* result = minimize(nll, true, 0);
    //////////////////////////////////
    //load and creates the histograms after the minimazation (fit)
      RooAbsPdf* mf= mc->GetPdf();
      RooArgSet spdf(*mf->getComponents());
      RooHistFunc* th_SR_nominal=(RooHistFunc*)spdf.find("th_SR_nominal");
      RooHistFunc* tth_SR_nominal=(RooHistFunc*)spdf.find("tth_SR_nominal");
      RooHistFunc* ttz_SR_nominal=(RooHistFunc*)spdf.find("ttz_SR_nominal");
      RooHistFunc* ttw_SR_nominal=(RooHistFunc*)spdf.find("ttw_SR_nominal");
      RooHistFunc* wz_SR_nominal=(RooHistFunc*)spdf.find("wz_SR_nominal");
      RooHistFunc* tz_SR_nominal=(RooHistFunc*)spdf.find("tz_SR_nominal");
      RooHistFunc* fakes_SR_nominal=(RooHistFunc*)spdf.find("fakes_SR_nominal");

      RooArgSet * parSet = (RooArgSet*)mc->GetObservables();
      RooRealVar * x_obs = (RooRealVar*)parSet->find("obs_x_SR"); //variable

      RooDataHist sth=th_SR_nominal->dataHist(); //signal thq
      RooDataHist stth=tth_SR_nominal->dataHist(); //tth
      RooDataHist sttz=ttz_SR_nominal->dataHist(); //ttz
      RooDataHist sttw=ttw_SR_nominal->dataHist();//ttw
      RooDataHist sfakes=fakes_SR_nominal->dataHist();//fakes
      RooDataHist swz=wz_SR_nominal->dataHist();//wz
      RooDataHist stz=tz_SR_nominal->dataHist();//tz
    /////////////////////////////////////////////////////////////
      TH1* data1=data->createHistogram("obs_x_SR",16);
      TH1* th=sth.createHistogram("obs_x_SR",16); //th
      TH1* tth=stth.createHistogram("obs_x_SR",16);  //tth
      TH1* ttz=sttz.createHistogram("obs_x_SR",16);  //ttz
      TH1* ttw=sttw.createHistogram("obs_x_SR",16);  ///ttw
      TH1* fakes=sfakes.createHistogram("obs_x_SR",16);  ///non prompt/fakes
      TH1* wz=swz.createHistogram("obs_x_SR",16); ///wz
      TH1* tz=stz.createHistogram("obs_x_SR",16); /// tz

      qw(data1);
    ///////////////////////////////////////////////
    //number of events post fit//
    //////////////////////////////////////////////////
    float i1 =(fakes->Integral())*(1.0+eps_fakes*alpha_fakes->getVal());//*lumi->getVal();  //fakes
    float i2 =(tz->Integral())*(1.0+ eps_tz*alpha_tz->getVal());//*lumi->getVal();  //Rares
    float i3=(wz->Integral())*(1.0+ eps_wz*alpha_wz->getVal());//*lumi->getVal(); //wz
    float i4=(ttz->Integral())*(1.0+ eps_ttz*alpha_ttz->getVal());//*lumi->getVal(); //ttz
    float i5=(ttw->Integral())*(1.0+ eps_ttw*alpha_ttw->getVal());//*lumi->getVal(); //ttw
    float i6=(th->Integral())*(alpha_mu->getVal());//*lumi->getVal();  //signal
    float i7=(tth->Integral())*(1.0+ eps_tth*alpha_tth->getVal());//*lumi->getVal(); //tth
    float id=data1->Integral(); //data
    ////////////////////////////////////////////////////////////
    //Shows the class of the object
    //cout<<params.InheritsFrom(RooAbsArg::Class())<<endl;
    //cout<< result->ClassName()<<endl;
    ///////////////////////////////////////////////////////////////
    //calculate the error of the fit for signal and backgrounds
    ///////////////////////////////////////////////////////////
    float(efakes)=(fakes->Integral())*(eps_fakes*alpha_fakes->getError()); //fakes
    float(etz)=(tz->Integral())*(eps_tz*alpha_tz->getError());  //tz
    float(ewz)=(wz->Integral())*(eps_wz*alpha_wz->getError()); //wz
    float(ettz)=(ttz->Integral())*(eps_ttz*alpha_ttz->getError()); //ttz
    float(ettw)=(ttw->Integral())*(eps_ttw*alpha_ttw->getError()); //ttw
    float(eth)=(th->Integral())*(alpha_mu->getError());  //signal
    float(etth)=(tth->Integral())*(eps_tth*alpha_tth->getError()); //tth
    ///////////////////////////////////////////////////////////////
    //normalize the  the histograms to one
    ////////////////////////////////////////
    fakes->Scale(i1/fakes->Integral()); //fakes
    tz->Scale(i2/tz->Integral());  //rares
    wz->Scale(i3/wz->Integral()); //wz
    ttz->Scale(i4/ttz->Integral()); //ttz
    ttw->Scale(i5/ttw->Integral()); //ttw
    th->Scale(i6/th->Integral());  //signal
    tth->Scale(i7/tth->Integral()); //tth
    /////////////////////////////////////////////
    //Plot the fit
    //////////////////////////////////////
    tth->SetFillColor(kOrange+7);
    th->SetFillColor(kRed+1);
    ttz->SetFillColor(kSpring+2);
    ttw->SetFillColor(kSpring+3);
    wz->SetFillColor(kMagenta-3);
    tz->SetFillColor(kCyan);
    fakes->SetFillStyle(3005);
    fakes->SetFillColor(kBlue-3);
    data1->SetMarkerStyle(8);
    data1->SetLineColor(kBlack);
    /////////////////////////////////////////////////////////////
    //group the histograms for the plotting
    THStack *hs = new THStack("hs","");
      hs->Add(fakes,"hist");
      hs->Add(tz,"hist");
      hs->Add(wz,"hist");
      hs->Add(ttz,"hist");
      hs->Add(ttw,"hist");
      hs->Add(tth,"hist");
      hs->Add(th,"hist");
    ///////////////////////////////////////////
    TCanvas *cs = new TCanvas("cs","cs",100,100,700,900);
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
      cs->SetCanvasSize(900,900);
      pad1->SetBottomMargin(0.01); // Upper and lower plot are joined
      //pad1->SetGridx();         // Vertical grid
      pad1->Draw();             // Draw the upper pad: pad1
      pad1->cd();               // pad1 becomes the current pad]
      data1->Draw();
      hs->Draw("same");
      data1->Draw("same");
      data1->SetStats(0);
      //  data1->SetAxisRange(0,40,"Y");
      data1->SetTitle("");
      data1->GetYaxis()->SetTitle("Events");

    TLegend* legend1 = new TLegend(0.6,0.6,0.89,0.89);
      //legend->SetHeader("Test","C"); // option "C" allows to center the header
      legend1->AddEntry(data1,"Data","lep");
      legend1->AddEntry(th,"tH (SM)","f");
      //legend1->AddEntry(th,"tH (k_{t}=-1)","f");
      legend1->AddEntry(tth,"t#bar{t}H","f");
      legend1->AddEntry(ttw,"t#bar{t}W","f");
      legend1->AddEntry(ttz,"t#bar{t}Z","f");
      legend1->AddEntry(wz,"WZ","f");
      legend1->AddEntry(tz,"Rares","f");
      legend1->AddEntry(fakes,"Fakes","f");
      legend1->SetBorderSize(0);
      legend1->Draw();
      pad1->RedrawAxis();
    // Draw the ratio plot
    TH1F *data_obs = (TH1F*)data1->Clone("data_obs");
    TH1F *sum =(TH1F*)fakes->Clone("sum");
      sum->Add(th);
      sum->Add(tth);
      sum->Add(ttw);
      sum->Add(ttz);
      sum->Add(wz);
      sum->Add(tz);
      data_obs->Divide(sum);
      cout<<sum->Integral()<<endl;
      data_obs->SetLineColor(kBlack);
      data_obs->SetMarkerStyle(8);
      cs->cd();  // Go back to the main canvas before defining pad2
    /////////////////////////////////////////
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
      pad2->SetTopMargin(0.1);
      pad2->SetBottomMargin(0.2);
      pad2->SetLeftMargin(0.1);
      pad2->Draw();
      pad2->cd();       // pad2 becomes the current pad
      data_obs->Draw();       // Draw the ratio plot
      data_obs->SetTitle(" ");
    ///////////////////////////////////
    data_obs->GetXaxis()->SetTitle("BDT Discriminant");
    data_obs->GetXaxis()->SetTitleOffset(1.0);
    data_obs->GetXaxis()->SetTitleSize(0.1);
    data_obs->GetXaxis()->SetLabelSize(0.1);
    /////////////////////////////////////
    data_obs->GetYaxis()->SetTitle("Data/Pred");
    data_obs->GetYaxis()->SetTitleOffset(0.4);
    data_obs->GetYaxis()->SetTitleSize(0.1);
    data_obs->GetYaxis()->SetLabelSize(0.1);
    data_obs->SetAxisRange(0, 2,"Y");
    data_obs->SetStats(0);
    data_obs->GetYaxis()->SetNdivisions(5);
    ////////////////////////////
    TLine *line = new TLine(-1.0,1,1,1.0);
      line->SetLineColor(kRed);
      line->Draw("same");
    //save the plot as an image
    cs->SaveAs("simple-3000.png");
    //cs->SaveAs("simple-3000-kt-1.png");
      //Save to file
      system(Form("mkdir -vp root-files/%s",version.c_str()));
        result->SetName("result");
          result->SaveAs(Form("root-files/%s/fit.root",version.c_str()));
    }
