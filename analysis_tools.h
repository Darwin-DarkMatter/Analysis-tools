
double GetTotalRate(TH1D *h){
	TAxis *xaxis = h->GetXaxis();
	double Bound = h -> Integral(xaxis->FindBin(0.),xaxis->FindBin(3000.), "width");
	cout << "Rate in the total spectra [0, 3000] is   " << Bound << endl;
	return Bound;

}
