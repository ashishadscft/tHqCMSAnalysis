void chi (){
TF1 *chi = new TF1("chi","x**([0]/2.-1)*exp(-x/2.)/(2**([0]/2.)*TMath::Gamma([0]/2.))",0,20);
TF1 *chi2 = new TF1("chi","x**([0]/2.-1)*exp(-x/2.)/(2**([0]/2.)*TMath::Gamma([0]/2.))",14,20);
chi2->SetFillColor(kBlue+1);
chi2->SetFillStyle(3005);
chi->SetParameter(0,7);
chi2->SetParameter(0,7);

TCanvas *cs = new TCanvas("cs","cs",100,100,700,900);
cs->SetCanvasSize(1200,900);
chi->Draw();
chi2->Draw("fcsame");
chi->SetTitle("#chi^{2} Distribution");
chi->GetXaxis()->SetTitle("#chi^{2}");
chi->GetYaxis()->SetTitle("P(#chi^{2})");
TLatex lat;
lat.SetTextSize(0.05);
lat.DrawLatex(15.4,0.003,"#alpha");
cout<<"df 7, a=0.05"<<chi->Integral(14,20)<<endl;
cs->SaveAs("chi.eps");
}
