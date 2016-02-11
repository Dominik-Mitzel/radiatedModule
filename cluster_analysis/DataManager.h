#ifndef DataManager_h
#define DataManager_h

#include <TTree.h>
#include <TPaveText.h>
#include <TGraphErrors.h>
#include <iostream>
#include <fstream>

#include "boost/program_options.hpp"
#include <boost/foreach.hpp>


#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TSpectrum.h>
#include <TFitResult.h>
#include <TAxis.h>
#include <TMath.h>
#include <TObjArray.h>
#include <TLegend.h>

#include "Cluster.h"



class TH1;
class TH2;

class DataManager
{
public:
  DataManager(const std::vector<int>& uplinksToBeAnalyzed, bool overview = false, int nBins=1);
  ~DataManager();

  void fillEvent(std::string pedestalFilename, std::string gainFilename, std::string dataFilename, std::string fileRunnumber, bool perEventDisplay, std::string position, bool draw, int identifier);
  

  const static unsigned short maxAdcValue = 3000;  
private:
  unsigned int uplinkIndex(int uplinkId);

  void findClusters(const std::vector<Channel>& dataVector, const float neighbour_threshold, const float seed_threshold, const float sum_threshold, const float correction_factor, std::vector<Cluster*>& Clusters);
  std::vector<double> GetPedestals(std::string fileName, int uplink, int nChannels);
  std::vector<double> GetGains(std::string fileName, int nChannels);

  void ShowPerEventDisplay(const int j, int number_channels, float* channel_float, const std::vector<Channel>& dataVector, const std::vector<Cluster*>& Clusters);  
  double FitPhotopeaks(int numberPhotopeaks, bool draw, float &gain, TH1* adc_of_clusters);
  void DrawAndSaveOverview(TH2* adc_vs_channel, TH1* adc_withCluster, TH1* collected_charge_distribution_1, TH1* cluster_size_distribution_1, std::string run_number, int uplink, std::string string_threshold, float gainCorrection, bool write_OverviewTxtFile, std::string position);
  void draw_collectedCharge(std::string run_number, int uplink, std::string string_threshold);

  double m_overallCollectedCharge;
  int m_overall_NumberOfEvents;
  int m_overall_NumberOfClusters;

  int nBins;
  int goodRangeUp;
  int goodRangeDown;
  int uplink_DUT;

  std::vector<std::pair<double,double> > m_ranges;
  std::vector<TH1D*> m_collectedChargeBinned;
  std::vector<TH1D*> m_clusterSizeBinned;
  std::vector<double> m_overallCollectedChargeBinned;
  std::vector<double> m_overall_NumberOfClustersBinned;
  TH1* m_ChargeBins;
  TH1* m_ClustersBins;
  TH1* m_ClusterSizeBins;
  std::vector<int> m_uplinkIds;
  std::vector<double> m_adcValues;
  bool m_overview;
  std::vector< std::vector <float> > m_pedestalPosition;
  std::map<int,TH2*> m_adcHistogram;
  std::map<int,TH1*> m_collectedChargeHistogram;
  std::map<int,TH1*> m_clusterSizeHistogram;
  std::map<int,TH1*> m_clusterChannelAdcHistogram;
  std::map<int,TH1*> m_clusterChannelAdcHistogram_SingleChannelNoRadiation;
  std::map<int,TH1*> m_clusterChannelAdcHistogram_SingleChannelWithRadiation;
  std::map<int,TH1*> m_residualHistogram;
};

#endif
