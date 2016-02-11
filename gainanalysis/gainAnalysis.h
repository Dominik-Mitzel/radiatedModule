
#include <string.h>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TNtuple.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TMultiGraph.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TChain.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include <TSpectrum.h>
#include <TFitResult.h>
#include <TMath.h>
#include <TColor.h>


void setRootStyle();
Double_t fpeaks(Double_t *x, Double_t *par);

void gainAnalysis(TString filename, TString gainname, int Uplink);

void FitPhotopeaks(int numberPhotopeaks, int uplink, int channel, bool draw, float* gain, TH1** histograms, TH2*adc_vs_channel);
void GainMeasurement(int selectNumberPeaks_Gain, int uplink, const char*pathToGain, bool ShowAllPlots,TH2* adc_vs_channel);


