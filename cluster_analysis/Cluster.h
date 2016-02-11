#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>

struct Channel{
  int ChannelNumber;
  double AdcValue;
};

class Cluster{
  private:
  std::vector<Channel> RelatedChannels;

  public:
  Cluster();
  ~Cluster();
  void Clear();
  void AddChannel(int chanNumber, double adcValue);
  double GetChargeWeightedMean();
  double GetHitWeightedMean();
  double GetSumOfAdcValues();
  double GetMaximumAdcValue();
  int GetClusterSize();
  int GetMinChannel();
  int GetMaxChannel();
};

#endif // CLUSTER_H
