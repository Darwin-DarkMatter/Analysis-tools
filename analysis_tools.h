TCut define_cuts_for6(){
	double A = 620. ;
	double B = TMath::Power(750.,2);

	TCut fid = Form( "TMath::Power( (TMath::Abs(Zp[0] +200. )) /%f ,8)  + TMath::Power( TMath::Power(Yp[0],2) / %f + TMath::Power(Xp[0],2) / %f , 4) < 1.",A,B,B); 
	return fid;
}


double sigma(double x){
	double a=0.313,b=0.002;
    return a*sqrt(x)+b*x;
}


Double_t Gauss(double x, double mu, double sigma) {

	double delta=(x-mu)/sigma;
    return TMath::Exp(-(delta*delta)/2.)/sigma/TMath::Sqrt(2.)/ TMath::Sqrt( TMath::Pi());
}

void SmearEnergySpectra(TH1D* h){
	TH1F* h2 = (TH1F*)h->Clone();
	h->Reset();
	double content;
	double error;
	double x, w;
	const UInt_t nX = h->GetNbinsX();
	UInt_t kmin, kmax;
	for(UInt_t i=1;i<=nX;++i)
	{
		x = h->GetXaxis()->GetBinCenter(i);
		content = 0;			
		kmin = 1;
		kmax = nX;
			
		for(UInt_t k=kmin;k<=kmax;++k)
		{
			w = h2->GetXaxis()->GetBinCenter(k);
			content+=h2->GetBinContent(k)*Gauss(w,x,sigma(x));
			error+= TMath::Power(h2->GetBinError(k)*Gauss(w,x,sigma(x)),2);
		}
			content=content*h->GetXaxis()->GetBinWidth(i);
			if(	content < 1e-20){ // To exclude underflow, you can deactivate this
				content = 1e-20;
			}
			h->SetBinContent(i,content);
			h->SetBinError(i,error);
	}	
}

double GetRateinRoi(TH1D *h){
	TAxis *xaxis = h->GetXaxis();
	double Bound = h -> Integral(xaxis->FindBin(2435.),xaxis->FindBin(2481.), "width");
	cout << "Rate in ROI [2435 - 2481]  is    " << Bound << endl;
	return Bound;

}

double GetTotalRate(TH1D *h){
	TAxis *xaxis = h->GetXaxis();
	double Bound = h -> Integral(xaxis->FindBin(0.),xaxis->FindBin(3000.), "width");
	cout << "Rate in the total spectra [0, 3000] is   " << Bound << endl;
	return Bound;

}


void Generate0nbb( TH1D *h, double expected_events){
	TH1F* h2 = (TH1F*)h->Clone();
	h->Reset();
	double content;
	double x, w;
	const UInt_t nX = h2->GetNbinsX();
	
	for(int k=1; k<nX+1 ; k++){
		x = h2->GetXaxis()->GetBinCenter(k);
		content = expected_events*Gauss(x, 2457.83, sigma(x));
		h->SetBinContent(k, content);

	}
}
