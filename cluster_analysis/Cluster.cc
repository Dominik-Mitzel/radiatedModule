#include "Cluster.h"

Cluster::Cluster(){}

Cluster::~Cluster(){}

void Cluster::Clear(){
  RelatedChannels.clear();
}

void Cluster::AddChannel(int chanNumber, double adcValue){
  Channel c;
  c.ChannelNumber = chanNumber;
  c.AdcValue = adcValue;
  RelatedChannels.push_back(c);
}

double Cluster::GetChargeWeightedMean(){
  double totalCharge = 0.;
  double mean = 0.;
  for(const auto& chan : RelatedChannels){
    mean += chan.ChannelNumber * chan.AdcValue;
    totalCharge += chan.AdcValue;
  }
  return mean/totalCharge;
}

double Cluster::GetHitWeightedMean(){
  double mean = 0.;
  for(const auto& chan : RelatedChannels){
    mean += chan.ChannelNumber;
  }
  return mean/RelatedChannels.size();
}

double Cluster::GetSumOfAdcValues(){
  double sumOfAdcValues = 0;
    for(const auto& chan : RelatedChannels){
    sumOfAdcValues += chan.AdcValue;
  }
  return sumOfAdcValues;
}

double Cluster::GetMaximumAdcValue(){
  double maxAdcValue = 0;
  for(const auto& chan : RelatedChannels){
    if(chan.AdcValue > maxAdcValue) maxAdcValue = chan.AdcValue;
  }
  return maxAdcValue;
}

int Cluster::GetClusterSize(){
  return RelatedChannels.size();
}

int Cluster::GetMinChannel(){
  int minChannel = 9999999;
  for(const auto& chan : RelatedChannels){
    if(chan.ChannelNumber < minChannel) minChannel = chan.ChannelNumber;
  }
  return minChannel;
}
int Cluster::GetMaxChannel(){
  int maxChannel = 0;
  for(const auto& chan : RelatedChannels){
    if(chan.ChannelNumber > maxChannel) maxChannel = chan.ChannelNumber;
  }
  return maxChannel;
}
