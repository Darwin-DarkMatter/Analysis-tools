# Analysis-tools
Tools for data analysis of MC data
List of functions in analysis_tools.h

# TCut define_cuts_for6() : *Returns a superellipsoid cut that contains 6 tons of LXe

# double sigma(double x) : *Sigma used in the Gaussian, same as used by Shayne in https://www.physik.uzh.ch/groups/groupbaudis/aspera09/wiki/doku.php?id=shayne:ersolarneutrinos#epilogueneutrino_capture_april_2019 Not the latest one

# Double_t Gauss(double x, double mu, double sigma) : *Returns a Gaussian function.

# void SmearEnergySpectra(TH1D* h) : *Smears a 1D-histogram with the Gauss function.

# double GetRateinRoi(TH1D* h) : *Calculates the rate in ROI : [2435 - 2481] 

# void Generate0nbb( TH1D* h, double expected_events) : *Generates a 1-D histogram of a gaussian signal with the total integral equal to expected_events
