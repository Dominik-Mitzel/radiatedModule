#include "DataManager.h"
#include <TString.h>
#include <TMath.h>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

DataManager::DataManager(const std::vector<int>& uplinksToBeAnalyzed, bool overview, int position)
{
  m_overview = overview;


  BOOST_FOREACH(int uplinkId, uplinksToBeAnalyzed){
    
    m_uplinkIds.push_back(uplinkId);

    std::string name;

    name = "adcHistogram_uplink" + std::to_string(uplinkId);
    TH2* adcHistogram = new TH2I(name.c_str(), name.c_str(), 128, .0, 128, maxAdcValue, -500., maxAdcValue);
    adcHistogram->GetXaxis()->SetTitle("channel");
    adcHistogram->GetYaxis()->SetTitle("adcValue");
    m_adcHistogram[uplinkId] = adcHistogram;

    std::string name2;
    name2 = "collectedChargeHistogram_uplink" + std::to_string(uplinkId);
    TH1* collectedChargeHistogram = new TH1D(name2.c_str(), "", 910, -.5, 90.5);
    collectedChargeHistogram->SetXTitle("collected charge [p.e.]");
    collectedChargeHistogram->SetYTitle("Events");
    m_collectedChargeHistogram[uplinkId] = collectedChargeHistogram;

    name = "clusterSizeHistogram_uplink" + std::to_string(uplinkId);
    TH1* clusterSizeHistogram = new TH1D(name.c_str(), name.c_str(), 9, -0.5, 8.5);
    clusterSizeHistogram->GetXaxis()->SetTitle("cluster size [channel]");
    clusterSizeHistogram->GetYaxis()->SetTitle("Events");
    m_clusterSizeHistogram[uplinkId] = clusterSizeHistogram;

    name = "clusterChannelAdcHistogram_uplink" + std::to_string(uplinkId);
    TH1* clusterChannelAdcHistogram = new TH1D(name.c_str(), name.c_str(), 200, -0.5, 12.5);
    clusterChannelAdcHistogram->GetXaxis()->SetTitle("led-corrected channel charge [p.e.]");
    clusterChannelAdcHistogram->GetYaxis()->SetTitle("Events");
    m_clusterChannelAdcHistogram[uplinkId] = clusterChannelAdcHistogram;

    name = "clusterChannelAdcHistogram_SingleChannelNoRadiation_uplink" + std::to_string(uplinkId);
    TH1* clusterChannelAdcHistogram_SingleChannelNoRadiation = new TH1D(name.c_str(), name.c_str(), 200, -0.5, 12.5);
    clusterChannelAdcHistogram_SingleChannelNoRadiation->GetXaxis()->SetTitle("led-corrected channel charge [p.e.]");
    clusterChannelAdcHistogram_SingleChannelNoRadiation->GetYaxis()->SetTitle("Events");
    m_clusterChannelAdcHistogram_SingleChannelNoRadiation[uplinkId] = clusterChannelAdcHistogram_SingleChannelNoRadiation;

    name = "clusterChannelAdcHistogram_SingleChannelWithRadiation_uplink" + std::to_string(uplinkId);
    TH1* clusterChannelAdcHistogram_SingleChannelWithRadiation = new TH1D(name.c_str(), name.c_str(), 200, -0.5, 12.5);
    clusterChannelAdcHistogram_SingleChannelWithRadiation->GetXaxis()->SetTitle("led-corrected channel charge [p.e.]");
    clusterChannelAdcHistogram_SingleChannelWithRadiation->GetYaxis()->SetTitle("Events");
    m_clusterChannelAdcHistogram_SingleChannelWithRadiation[uplinkId] = clusterChannelAdcHistogram_SingleChannelWithRadiation;


    name = "residualHistogram_uplink" + std::to_string(uplinkId);
    TH1* residualHistogram = new TH1D(name.c_str(), name.c_str(), 200, -128, 128);
    residualHistogram->GetXaxis()->SetTitle("residial [channel]");
    residualHistogram->GetYaxis()->SetTitle("Events");
    m_residualHistogram[uplinkId] = residualHistogram;

  }

  
 
  if(position==0){      
    uplink_DUT = 10; 
    goodRangeUp = 128;
    goodRangeDown =0 ;
    nBins=128;
   } 
  if(position==1){      
    uplink_DUT = 11; 
    goodRangeUp = 128;
    goodRangeDown =0 ;
    nBins=128;
   } 
  if(position==2){      
    uplink_DUT = 12; 
    goodRangeUp = 128;
    goodRangeDown =0 ;
    nBins=128;
   } 
  if(position==3){      
    uplink_DUT = 13; 
    goodRangeUp = 128;
    goodRangeDown =0 ;
    nBins=128;
   } 
  
  //slayer positions

  if(position==8){      
    uplink_DUT = 8; 
    goodRangeUp = 128;
    goodRangeDown =0 ;
    nBins=128;
   } 
  if(position==7){      
    uplink_DUT = 7; 
    goodRangeUp = 128;
    goodRangeDown =0 ;
    nBins=128;
   } 
  if(position==6){      
    uplink_DUT = 6; 
    goodRangeUp = 128;
    goodRangeDown =0 ;
    nBins=128;
   } 
  if(position==5){      
    uplink_DUT = 5; 
    goodRangeUp = 128;
    goodRangeDown =0 ;
    nBins=128;
    }

  //octo positions

  if(position==12){      
    uplink_DUT = 4; 
    goodRangeUp = 128;
    goodRangeDown =0 ;
    nBins=128;
   } 
  if(position==11){      
    uplink_DUT = 3; 
    goodRangeUp = 128;
    goodRangeDown =0 ;
    nBins=128;
   } 
  if(position==10){      
    uplink_DUT = 2; 
    goodRangeUp = 128;
    goodRangeDown =0 ;
    nBins=128;
   } 
  if(position==9){      
    uplink_DUT = 1; 
    goodRangeUp = 128;
    goodRangeDown =0 ;
    nBins=128;
   } 
  

  std::cout<<"uplink of DUT "<<uplink_DUT<<std::endl; 

  // nBins = bins;//64; //!
  //std::vector<std::pair<double,double> > ranges;

  m_ChargeBins=new TH1D("chargeBins","charge as function of bins",nBins,-.5,nBins-.5);
  m_ClustersBins=new TH1D("clustersBins","clusters as function of bins",nBins,-.5,nBins-.5);
  m_ClusterSizeBins=new TH1D("clustersSizeBins","cluster size as function of bins",nBins,-.5,nBins-.5);


  for(int i=0;i<nBins;++i) {
    double length = (goodRangeUp-goodRangeDown)/nBins;
    double lowEdge = goodRangeDown + i*length;
    double highEdge = goodRangeDown + (i+1)*length;
    std::pair<double,double> temppair(lowEdge,highEdge);
    std::cout<<"bin "<<i<<": "<<lowEdge<<"-"<<highEdge<<std::endl;
    m_ranges.push_back(temppair);
  }

  //std::vector<TH1D*> collectedChargeBinned(0);
  TH1D* temp(0);
  for(int i =0;i<nBins;++i) {
    temp = new TH1D(TString::Format("collected_charge_%i",i),"collected_charge [p.e.]",910,-.5,90.5);
    m_collectedChargeBinned.push_back(temp);
  }

  TH1D* temp2(0);
  for(int i =0;i<nBins;++i) {
    temp2 = new TH1D(TString::Format("cluser_size_%i",i),"cluster_size [channels]",910,-.5,10.5);
    m_clusterSizeBinned.push_back(temp2);
  }

  for(int i=1;i<nBins;++i) { //collects the total charge and number of clusters in the bins
    m_overallCollectedChargeBinned.push_back(0);
    m_overall_NumberOfClustersBinned.push_back(0);
  }
   m_overallCollectedCharge = 0.;
   m_overall_NumberOfEvents = 0;
   m_overall_NumberOfClusters = 0;

}

DataManager::~DataManager()
{}

unsigned int DataManager::uplinkIndex(int uplinkId)
{
  std::vector<int>::iterator uplinkIdIt = m_uplinkIds.begin();
  std::vector<int>::iterator uplinkIdItEnd = m_uplinkIds.end();
  for (int i = 0; uplinkIdIt != uplinkIdItEnd; ++uplinkIdIt, ++i) {
    if (*uplinkIdIt == uplinkId)
      return i;
  }
  assert(false);
  return 0;
}



void DataManager::fillEvent(std::string pedestalFilename, std::string gainFilename, std::string dataFilename, std::string run_number, bool perEventDisplay, std::string position, bool draw, int identifier)
{
  

   std::cout<<"pedestal  "<<identifier <<std::endl;


   std::map <int,double> correction_factors;


   //Hd modules use channels 1-128 of FrontEndBoars, but Aachen uses channels 129-256

   int channel_range_down = 0;
   int channel_range_up = 128;


   //define seed and cluster threshold
   float correction_factor=1;
   if(uplink_DUT==10) correction_factor = 0.925;
   if(uplink_DUT==11) correction_factor = 0.95*0.998*1.02; 
   if( uplink_DUT==12 || uplink_DUT==13  ) correction_factor = 0.95*1.02*0.96;
   if(uplink_DUT==8 ) correction_factor = 1.025*0.972;
   if(uplink_DUT==7 ) correction_factor = 1.025*0.972;
   if(uplink_DUT==6 ) correction_factor = 1.025*0.977;
   if (uplink_DUT==5 ) correction_factor = 1.025*0.96*1.04*1.01;
   

   //float correction_factor=0.95;//(1125X);
    //float seed_threshold =2.5;// 2.5; //2.5
   //float neighbour_threshold =1.5;// 1.5;// 1.5
   //float sum_threshold = 4.5;//4.5;//4.5
   int totalNumberClusters_binned=0;
   int totalNumberClusters_UNbinned=0;

   float seed_threshold =1.5;// 2.5; //2.5
   float neighbour_threshold =.5;// 1.5;// 1.5
   float sum_threshold = 1.5;//4.5;//4.5


   std::cout<<"chosen range: "<<goodRangeDown<<" to "<<goodRangeUp<<std::endl;
   std::cout<<"correction factor: "<<correction_factor<<std::endl;
   
   bool dead_channels[128] = {false};

   std::stringstream stringstream_threshold;
   stringstream_threshold.str(std::string());
   stringstream_threshold << "_thresh" << int(seed_threshold) << 10*seed_threshold-10*int(seed_threshold) << int(neighbour_threshold) << 10*neighbour_threshold-10*int(neighbour_threshold) << int(sum_threshold) << 10*sum_threshold-10*int(sum_threshold);


   //read pedestal sile and determine offset to be subtracted from the adc-value
   std::cout << "reading pedestals from "<< pedestalFilename.c_str() << " and gains from" << std::endl;

   std::map<int,std::vector<double> > pedestals;
   std::map<int,std::vector<double> > gains;

   for(std::vector<int>::const_iterator uplink = m_uplinkIds.begin(); uplink != m_uplinkIds.end(); ++uplink){
   
     pedestals[*uplink]  = GetPedestals(pedestalFilename, *uplink, channel_range_up);

     std::string currentGainFilename = gainFilename + std::to_string(*uplink) + ".root";
     std::cout <<  currentGainFilename.c_str() << std::endl;     
     gains[*uplink] = GetGains(currentGainFilename, 128);

   }

   std::cout<<"Reading File "<< dataFilename.c_str() << std::endl;
   TFile f(dataFilename.c_str());

   //Set Readout Tree
   TTree * T = nullptr;
   T = (TTree*) f.Get("rawData");
   
   Int_t nEvents = T->GetEntries();
   
   printf("NEntries = %d\n", nEvents);

   //Define channel and adc arrays
   std::map<int,std::vector<float> > adc;
   for(std::vector<int>::const_iterator uplink = m_uplinkIds.begin(); uplink != m_uplinkIds.end(); ++uplink){
      for( int j = channel_range_down; j < channel_range_up; ++j){
        adc[*uplink].push_back(0.);
      }
   }

   float* channel_float = new float[channel_range_up];

   //Set Branch names from ntuple
   for(std::vector<int>::const_iterator uplink = m_uplinkIds.begin(); uplink != m_uplinkIds.end(); ++uplink){     

     for( int j = channel_range_down; j < channel_range_up; ++j){
   
       if(uplink == m_uplinkIds.begin()) channel_float[j] = j+1;

       std::string adc_title;        
       adc_title = "Uplink_" + std::to_string(*uplink) + "_adc_" + std::to_string(j+1);

       T -> SetBranchAddress(adc_title.c_str(), &adc[*uplink][j] ) ;
        
     }
     
   }
   
   
  //read events
  for ( Int_t j = 0 ; j < nEvents ; j++ ) {
    
    T -> GetEntry( j ) ;
    //std::cout<<j<<std::endl;
    //   if (j>11) break;
    m_overall_NumberOfEvents +=1;

    //fill event vector dataVector and 
    std::map<int,std::vector<Channel>> dataVector;

   
    for(std::vector<int>::const_iterator uplink = m_uplinkIds.begin(); uplink != m_uplinkIds.end(); ++uplink){
      //      if(adc[*uplink][0]>1500) break;//veto baseline shifts
      //if(adc[*uplink][120]>1500) break;
      for(int i = channel_range_down; i < channel_range_up; ++i){
	 Channel c;
         //c.ChannelNumber = i+1;
         c.ChannelNumber=channel_range_up-i; //invert channel numbers
	 c.AdcValue = (adc[*uplink][i] - pedestals[*uplink][i]) / gains[*uplink][i]/correction_factor;
         dataVector[*uplink].push_back(c);
	 m_adcHistogram[*uplink]->Fill(128-i, (adc[*uplink][i] - pedestals[*uplink][i])); //inverted!
	 //m_adcHistogram[*uplink]->Fill(i+1, (adc[*uplink][i] - pedestals[*uplink][i]));
         if(c.ChannelNumber==66) m_clusterChannelAdcHistogram_SingleChannelWithRadiation[*uplink]->Fill(c.AdcValue);
	 if(c.ChannelNumber==40) m_clusterChannelAdcHistogram_SingleChannelNoRadiation[*uplink]->Fill(c.AdcValue);
       }
    }

    //search for clusters in the event
    std::map<int,std::vector<Cluster*>> Clusters; //found clusters are stored in here

    for(std::vector<int>::const_iterator uplink = m_uplinkIds.begin(); uplink != m_uplinkIds.end(); ++uplink){
      //if(*uplink==uplink_DUT){
      findClusters(dataVector[*uplink], neighbour_threshold, seed_threshold, sum_threshold, correction_factor, Clusters[*uplink]);//}
    }



    //Show per-event display
    if(perEventDisplay){
       
      for(std::vector<int>::const_iterator uplink = m_uplinkIds.begin(); uplink != m_uplinkIds.end(); ++uplink){      
      
          if(Clusters[*uplink].size() > 0) ShowPerEventDisplay(j, 128, channel_float, dataVector[*uplink], Clusters[*uplink]);                                                                
      }

    }

   
   //do not select events at the gap


    int totalNumberClusters=0;
    double position_source;

    for(std::vector<int>::const_iterator uplink = m_uplinkIds.begin(); uplink != m_uplinkIds.end(); ++uplink){
      totalNumberClusters+=Clusters[*uplink].size();
      //std::cout<<*uplink<<"  "<<Clusters[*uplink].size()<<std::endl;
    }  
    //std::cout<<totalNumberClusters<<std::endl;
    //if(totalNumberClusters!=1 ) continue; //only one cluster in ALL uplinks! (avoid particles out of time)
    if(totalNumberClusters!=1 ) continue; //only one cluster in ALL uplinks that are read out testbeam configuration with 2 SciFi modules

    //from here dont care for other uplinks any more 


    //fill histograms

    
    for(std::vector<int>::const_iterator uplink = m_uplinkIds.begin(); uplink != m_uplinkIds.end(); ++uplink){
      
      //if( *uplink == 8) continue; //light leak in slayer
      if(Clusters[*uplink].size() != 1) continue; ///only single cluster events in uplink which is considered?
      if(Clusters[*uplink].at(0)->GetMaxChannel() < goodRangeDown || Clusters[*uplink].at(0)->GetMaxChannel() > goodRangeUp ) { ///in clean beam range?
          //std::cout<<  goodRangeDown << std::endl;
	continue;
      }
      


      if(*uplink!=uplink_DUT) continue; //only events where we have a cluster in the DUT
      
           //      std::cout<<*uplink<<"  "<<totalNumberClusters<<std::endl;

    for(int cluster = 0; cluster < Clusters[*uplink].size(); ++cluster){

        for(Int_t k = -2; k<= 2; k++){
                              
             if( (Clusters[*uplink].at(cluster)->GetMaxChannel() + k) >= 0 && (Clusters[*uplink].at(cluster)->GetMaxChannel() + k < 128) )
                 m_clusterChannelAdcHistogram[*uplink]->Fill(dataVector[*uplink].at(Clusters[*uplink].at(cluster)->GetMaxChannel() + k).AdcValue);
         }
    
	//std::cout<<j << "  " << Clusters[uplink_DUT].at(cluster)->GetSumOfAdcValues() <<" total number cluster<< "<< totalNumberClusters<< std::endl; //roman test

	//light yield as function of channels
	for(int i=0;i<=nBins;++i) {
	    if( Clusters[*uplink].at(0)->GetChargeWeightedMean() >= m_ranges[i].first && Clusters[*uplink].at(0)->GetChargeWeightedMean() < m_ranges[i].second ){ 
	    //std::cout<<"max "<< Clusters[*uplink].at(0)->GetChargeWeightedMean() <<" in "<<m_ranges[i].first<<","<< m_ranges[i].second<<std::endl;
	    if(*uplink==uplink_DUT) { //check binned charge only for DUT
	    m_collectedChargeBinned[i]->Fill(Clusters[*uplink].at(cluster)->GetSumOfAdcValues());
	    m_clusterSizeBinned[i]->Fill(Clusters[*uplink].at(cluster)->GetClusterSize());
	    m_overallCollectedChargeBinned[i] += Clusters[*uplink].at(cluster)->GetSumOfAdcValues();
	    m_overall_NumberOfClustersBinned[i] += 1;
	    totalNumberClusters_binned += 1; 
	   }
	  }
	  // else std::cout<<"killed :"<<  Clusters[*uplink].at(0)->GetChargeWeightedMean() <<std::endl;
	}
	

       //m_collectedChargeHistogram->Fill(cluster->GetSumOfAdcValues());
       m_collectedChargeHistogram[*uplink]->Fill(Clusters[*uplink].at(cluster)->GetSumOfAdcValues());
       //m_clusterSizeHistogram->Fill(cluster->GetClusterSize());
       m_clusterSizeHistogram[*uplink]->Fill(Clusters[*uplink].at(cluster)->GetClusterSize());
       m_overallCollectedCharge += Clusters[*uplink].at(cluster)->GetSumOfAdcValues();
       m_adcValues.push_back( Clusters[*uplink].at(cluster)->GetSumOfAdcValues() );
       m_overall_NumberOfClusters += 1;
       totalNumberClusters_UNbinned += 1;  
    }

    } 
   
   }


  std::map<int, float> gainCorrection;
  //for(std::vector<int>::const_iterator uplink = m_uplinkIds.begin(); uplink != m_uplinkIds.end(); ++uplink){
   
  double gain_correction = FitPhotopeaks(4, false, gainCorrection[uplink_DUT], m_clusterChannelAdcHistogram[uplink_DUT]);

 // }

  //save files
   std::string name;
  
  //save plots in new folder "plots"
   name = "dominik_plots";
  
  
  fs::path p(name.c_str());
  if (!fs::is_directory(p)) fs::create_directories(p);
  
  
  bool write_OverviewTxtFile = false;
  if(draw){
    for(std::vector<int>::const_iterator uplink = m_uplinkIds.begin(); uplink != m_uplinkIds.end(); ++uplink){
      m_collectedChargeHistogram[*uplink]->Sumw2();

    DrawAndSaveOverview(m_adcHistogram[*uplink], m_clusterChannelAdcHistogram
[*uplink], m_collectedChargeHistogram[*uplink], m_clusterSizeHistogram[*uplink], run_number, *uplink, stringstream_threshold.str(), gainCorrection[*uplink], write_OverviewTxtFile, position);

    double average;
    double sigma; 
    
    for(std::vector<double>::iterator it = m_adcValues.begin(); it!= m_adcValues.end(); ++it) average+=*it;   
    average/= m_adcValues.size();
    
    for(std::vector<double>::iterator it = m_adcValues.begin(); it!= m_adcValues.end(); ++it) sigma+=(average-*it)*(average-*it);
    sigma=pow(sigma/(m_adcValues.size()*(m_adcValues.size()-1)),0.5);
    
    std::cout<<"integrated average collected charge: " <<average<<" +-"<<sigma<<" (with "<<m_adcValues.size()<<" entries)"<<std::endl;
    std::cout<<"total numbwe clusters in bin study :"<< totalNumberClusters_binned << std::endl;
    std::cout<<"total numbwe clusters UNBINNED :"<< totalNumberClusters_UNbinned << std::endl;

    draw_collectedCharge(run_number, *uplink, stringstream_threshold.str());
    


    //for bin per bin study

    for(int i=0;i<nBins;++i){
      std::cout <<"average_charge bin "<<i<<" = "<< m_overallCollectedChargeBinned[i]/m_overall_NumberOfClustersBinned[i]<< "+-"<< m_overallCollectedChargeBinned[i]/pow(m_overall_NumberOfClustersBinned[i],1.5)<<" ("<<m_overall_NumberOfClustersBinned[i]<<" clusters)"<< std::endl;

    }

    }}


}

void DataManager::findClusters(const std::vector<Channel>& dataVector, const float neighbour_threshold, const float seed_threshold, const float sum_threshold, const float correction_factor, std::vector<Cluster*>& Clusters)
{

  //std::cout<<"new data vector.."<<std::endl;
    
  Cluster* currentCluster = nullptr;

    //int i=0;
    for(std::vector<Channel>::const_iterator chan = dataVector.begin(); chan != dataVector.end(); ++chan){

      //std::cout<<i<<" adc values :"<< chan->AdcValue << std::endl;
      //++i;

          if( chan->AdcValue > neighbour_threshold) //look for channels exceeding cluster threshold
            {
              if(currentCluster == nullptr)
                {
		  //std::cout<<" exceeded seed of "<< neighbour_threshold <<" new temp cluster created"<< std::endl;
		 currentCluster = new Cluster();
                 currentCluster->AddChannel(chan->ChannelNumber, chan->AdcValue);
                }
              else
                {
		  //std::cout<<"channel added to temp cluster created"<< std::endl;
		  currentCluster->AddChannel(chan->ChannelNumber, chan->AdcValue);
                }
            }

          if( chan->AdcValue <= neighbour_threshold && currentCluster != nullptr)
            {

	      //std::cout<<"adc vale fall below threshold"<< std::endl;
	      //std::cout<<"maximum of temp cluster: "<<currentCluster->GetMaximumAdcValue() << " sum: "<<currentCluster->GetSumOfAdcValues() << std::endl;
	      if(currentCluster->GetMaximumAdcValue() > seed_threshold && currentCluster->GetSumOfAdcValues() > sum_threshold) {
		//std::cout<<"cluster passed "<< std::endl;
		 Clusters.push_back(currentCluster);
		 }
	      currentCluster = nullptr;
          }

     }
    //std::cout<<"Clusters.sizeof() = "<< Clusters.size()<< std::endl;
    //if(Clusters.size() > 0) std::cout<<"Clusters.at(0).GetChargeWeightedMean() = "<< Clusters.at(0)->GetChargeWeightedMean() << std::endl;
    //if(Clusters.size() > 0) std::cout<<"Clusters.at(0).GetSumOfAdcValues() = "<< Clusters.at(0)->GetSumOfAdcValues() << std::endl;
    //if(Clusters.size() > 0) std::cout<<"Clusters.at(0).GetClusterSize() = "<< Clusters.at(0)->GetClusterSize() << std::endl;
    //getchar();

}

void DataManager::ShowPerEventDisplay(const int j, int number_channels, float* channel_float, const std::vector<Channel>& dataVector, const std::vector<Cluster*>& Clusters){


      std::stringstream canvasname;
      canvasname.str(std::string());
      canvasname << "per_event_" << j;
      TCanvas* per_event_Canvas = NULL;

      float adc_of_channel[128] = {0.};

      for(int l =0; l < number_channels; ++l){
         adc_of_channel[l] = dataVector.at(l).AdcValue;
      }

      per_event_Canvas = new TCanvas(canvasname.str().c_str(), canvasname.str().c_str(), 1200, 900);
      TGraph* per_event_adc = new TGraph(number_channels, channel_float, adc_of_channel);
      //sleep(1);
      per_event_adc->Draw("AB");

         TPaveText *info = new TPaveText(0.65,0.5,0.85,0.85,"brNDC");
         info->AddText(Form("Found clusters: %i\n", int(Clusters.size())));
         for( Int_t l = 0; l < Clusters.size(); l++){
            info->AddText(Form("cluster hit mean %i: %f.1\n", l+1, Clusters.at(l)->GetHitWeightedMean()));
            info->AddText(Form("cluster charge-wighted mean %i: %f.1\n", l+1, Clusters.at(l)->GetChargeWeightedMean()));
            info->AddText(Form("cluster width %i: %i\n", l+1, Clusters.at(l)->GetClusterSize()));
            info->AddText(Form("collected charge of cluster %i: %f.1\n", l+1, Clusters.at(l)->GetSumOfAdcValues()));
         }
         info->Draw("same");
         //
         TLine *seed_threshold_line = new TLine();
         seed_threshold_line->DrawLine(0,2.5,number_channels,2.5);
         TLine *neighbour_threshold_line = new TLine();
         neighbour_threshold_line->DrawLine(0,1.5,number_channels,1.5);

         gPad->Modified();
         per_event_Canvas->Update();
         printf("Hit_multiplicity = %i\n",int(Clusters.size()));
         per_event_Canvas->WaitPrimitive();
         //sleep(3);
         per_event_Canvas->Close();
         //delete adc_of_channel;

}


std::vector<double> DataManager::GetPedestals(std::string fileName, int uplink, int nChannels){

  TFile pedestalFile(fileName.c_str(), "READ");

  if(!pedestalFile.IsOpen()){
    std::cerr << "unable to open pedestal file " << fileName << std::endl;
  }

  TTree* pedestalTree = dynamic_cast<TTree*>(pedestalFile.Get("rawData"));
  if(pedestalTree == nullptr){
    std::cerr << "pedestal tree is nullptr" << std::endl;
  }

  long entries = pedestalTree->GetEntriesFast();

  std::string branchName = "Uplink_" + std::to_string(uplink) + "_adc_";

  std::vector<double> pedestals(nChannels, 0.);
  float* adcVals = new float[nChannels];

  for(int i = 0; i<nChannels; ++i){
  pedestalTree->SetBranchAddress((branchName + std::to_string(i+1)).c_str(), &adcVals[i]);
  }

  for(int i = 0; i < entries; ++i){
    pedestalTree->GetEntry(i);
    for(int j = 0; j < nChannels; ++j){
      pedestals[j] += adcVals[j];
    }
  }

  for(int j = 0; j < nChannels; ++j){
    pedestals[j] /= entries>0. ? double(entries) : 1.;
  }

  delete adcVals;
  pedestalFile.Close();

  return pedestals;
}

std::vector<double> DataManager::GetGains(std::string fileName, int nChannels)
{
  TFile gainFile(fileName.c_str());
  TGraphErrors* gain_Graph =  (TGraphErrors*)gainFile.Get("Graph");

  Double_t* gain_pointer = {gain_Graph->GetY()};

  std::vector<double> gains(nChannels);
  int i = 0;

  for( int i = 0; i < nChannels; i++){
    gains[i] = float(gain_pointer[i]);
  }

  return gains;
}

void DataManager::DrawAndSaveOverview(TH2* adc_vs_channel, TH1* adc_withCluster, TH1* collected_charge_distribution_1, TH1* cluster_size_distribution_1, std::string run_number, int uplink, std::string string_threshold, float gainCorrection, bool write_OverviewTxtFile, std::string position){

    std::stringstream stream;
    TPaveText *info = new TPaveText(0.65,0.55,0.85,0.75,"brNDC");
     info->AddText("Data Gain Correction=");
     info->AddText(Form("%f", gainCorrection));

    std::string canvasname = "overview_uplink" + std::to_string(uplink);
    TCanvas* overviewCanvas = new TCanvas(canvasname.c_str(), canvasname.c_str(), 1200, 900);
    overviewCanvas->Divide(2, 2);

    overviewCanvas->cd(1);
    gPad->SetLogz();
    adc_vs_channel->DrawCopy("COLZ");


    overviewCanvas->cd(2);
    adc_withCluster->SetAxisRange(-1.,15.,"X");
    gPad->SetLogy();
    adc_withCluster->DrawCopy("");
    info->Draw("same");

    overviewCanvas->cd(3);
    collected_charge_distribution_1->DrawCopy("");

    overviewCanvas->cd(4);
    cluster_size_distribution_1->DrawCopy("");

   gPad->Modified();
   overviewCanvas->Update();

   stream.str(std::string());
   stream << "dominik_plots/" << run_number << "_uplink"<< uplink << "_overview" << string_threshold <<".root";
   TFile file(stream.str().c_str(),"RECREATE");
    overviewCanvas->Write();
    adc_withCluster->Write();
    collected_charge_distribution_1->Write();
    adc_vs_channel->Write();
    cluster_size_distribution_1 ->Write();
    
    for(int i=0; i<nBins;++i) {
      m_collectedChargeBinned[i]->Write();
      m_ChargeBins->SetBinContent(i,m_collectedChargeBinned[i]->GetMean());
      m_ChargeBins->SetBinError(i,m_collectedChargeBinned[i]->GetStdDev()/TMath::Sqrt(m_collectedChargeBinned[i]->GetEntries()));
      m_ClustersBins->SetBinContent(i,m_collectedChargeBinned[i]->GetEntries());
      m_ClusterSizeBins->SetBinContent(i,m_clusterSizeBinned[i]->GetMean());
      m_ClusterSizeBins->SetBinError(i,m_clusterSizeBinned[i]->GetStdDev()/TMath::Sqrt(m_clusterSizeBinned[i]->GetEntries()));
    }
    m_clusterChannelAdcHistogram_SingleChannelWithRadiation[uplink_DUT]->Write();
    m_clusterChannelAdcHistogram_SingleChannelNoRadiation[uplink_DUT]->Write();
    m_ClustersBins->Write();
    m_ChargeBins->Write();
    m_ClusterSizeBins->Write();
    file.Close();

  // overviewCanvas->Close();

   //save collected charge mean and gain correction into txtfile 
   if(write_OverviewTxtFile){
      stream.str(std::string());
      stream << "dominik_plots/LightYield_And_ClusterSize_normalAlgorithm_uplink" << uplink << string_threshold << ".txt";

      FILE* resultLog = NULL;
      resultLog = fopen(stream.str().c_str(),"a");

      stream.str(std::string());
      stream << "dominik_plots/"<< run_number << "_uplink" << uplink << "_position_" << position << string_threshold;
      fprintf(resultLog,"%s\t \n",stream.str().c_str());
      fprintf(resultLog,"%s\t %f\t %s\t %f\t %s\t %f\t %s\t %f\t \n","collected_charge_mean", collected_charge_distribution_1->GetMean(), "collected_charge_mean error",
                         collected_charge_distribution_1->GetMeanError(), "gainCorrection", gainCorrection, "collected_charge_mean/gainCorrection",
                         collected_charge_distribution_1->GetMean()/gainCorrection);
      fprintf(resultLog,"%s\t %f\t %s\t %f\t %s\t %f\t \n","collected_charge_mean/gainCorrection error",
              collected_charge_distribution_1->GetMeanError()/gainCorrection, "cluster_size Mean", cluster_size_distribution_1->GetMean(),
              "cluster_size RMS", cluster_size_distribution_1->GetRMS());
      fprintf(resultLog,"%s\t \n","");
      fclose(resultLog);

   }
}

Double_t fpeaks(Double_t *x, Double_t *par){
  
  Double_t result = par[0] + par[1]*x[0];
  for (Int_t p=0;p<7; p++) {
    Double_t norm  = par[p+6];
    Double_t mean  = par[2] + p * par[3];
    Double_t sigma_0 = par[4];
    Double_t sigma = par[5];
    if(p==0) result += norm*TMath::Gaus(x[0],mean,sigma_0);
    else result += norm*TMath::Gaus(x[0],mean,sqrt(pow(sigma_0,2)+p*pow(sigma,2)));

  }
  return result;
}


double DataManager::FitPhotopeaks(int numberPhotopeaks, bool draw, float &gain, TH1* adc_of_clusters)
{

  char tmp[256];
  //TCanvas* pedestalcanvas = new TCanvas("pedestal peak", "adc-Signal", 1600, 1200);

  TCanvas* canvas = new TCanvas("data gain correction", "adc-Signal", 1600, 1200);

  double mean = 0;
  double rms = 0;

  Double_t par[3000];

  //Use TSpectrum to search for peaks
  TSpectrum *s = new TSpectrum(numberPhotopeaks);
  Int_t nfound = s->Search(adc_of_clusters,0.1,"new",0.001);//first float number: sigma of searched peaks(how significant is the peak), second float number: amplitude threshold for smaller second peak relative to highest

  //Get estimated peak positions and define as parameter start values
  auto xpeaks = s->GetPositionX();
  Float_t temp;
     //sorts the peak positions from lowest to highest
     for(int i=0; i< (nfound -1); ++i)
      {
          for(int j = i + 1; j > 0; --j)
          {
              if(xpeaks[j] < xpeaks[j-1]/* && xpeaks[j] > -400*/)
              {
                  //Swaps the values
                  temp = xpeaks[j];
                  xpeaks[j] = xpeaks[j - 1];
                  xpeaks[j - 1] = temp;
              }

          }
     }


      //Define fit start parameters
      for (Int_t p=0;p<numberPhotopeaks;p++) {
           Float_t xp = xpeaks[p];
           Int_t bin =  adc_of_clusters->GetXaxis()->FindBin(xp);
           Float_t yp = adc_of_clusters->GetBinContent(bin);
           par[3*p+4] = yp;
           par[3*p+5] = 5.;
           }

      //Estimate expected gain to define function range by finding maximum peak and dividing by number of peaks
      double expected_gain;
      //check if found peaks look reasonable, else: use 125 which was usually used in the test beam. Except!!! Christian modules
      if((xpeaks[1] - xpeaks[0]> 0.3*(xpeaks[2] - xpeaks[1]) && (xpeaks[1] - xpeaks[0]< 0.7*(xpeaks[2] - xpeaks[0])) && nfound > 1 && (xpeaks[1] - xpeaks[0]) < 2. && (xpeaks[1] - xpeaks[0]) > 0.5)) expected_gain = xpeaks[1] - xpeaks[0];//xpeaks[3] - xpeaks[2];
        else {expected_gain = 1.;
      }

      expected_gain = 1.;
      par[0] = 0.;//potential linear slope
      par[1] = 0.;//potential linear slope
      par[2] = 2.;//xpeaks[2];//14. - nPhotopeaks  - 2.;//xpeaks[0];//position of pedestal peak
      par[3] = fabs(expected_gain);
      par[4] = 0.2;//sigma of pedestal peak
      par[5] = 0.2;//change in sigma for one peak sigma_i = sqrt(sigma_0^2 + i sigma_2)

      std::cout<<"nfound = "<< nfound<< std::endl;
      std::cout<<"expected_gain = "<< expected_gain<< std::endl;
      std::cout<<"2nd peak position = "<< par[2]<< std::endl;

      //Define fitrange
      Double_t fitrange_low;
      Double_t fitrange_high;

      //fitrange_low = par[2]-fabs(expected_gain)/2.;//position of pedestal peak -fabs(expected_gain)/2.-50
      //fitrange_high = par[2] + (numberPhotopeaks-0.5) * fabs(expected_gain);//position of pedestal peak npeaks*fabs(expected_gain)
      
      fitrange_low = 1.5;//par[2]-fabs(expected_gain)/2.;//position of pedestal peak -fabs(expected_gain)/2.-50
      fitrange_high = 6.5;//par[2] + (numberPhotopeaks-0.5) * fabs(expected_gain);//position of pedestal peak npeaks*fabs(expected_gain)
      
      std::cout<<"numberPhotopeaks = "<< numberPhotopeaks << std::endl;
      std::cout<<"fitrange_low = "<< fitrange_low << std::endl;
      std::cout<<"fitrange_high = "<< fitrange_high << std::endl;

      //TF1 *pedestalpeak = new TF1("pedestalpeak", pedpeak, -0.5, 0.5, 3);
      //pedestalpeak->SetParameters(10000., 0., 0.1);
      //pedestalpeak->SetParLimits(0,0.,10000000.);
      //pedestalpeak->SetParLimits(1,-0.5,0.5);
      //pedestalpeak->SetParLimits(2,0.,0.3);

      //TFitResultPtr f = adc_of_clusters->Fit("pedestalpeak","RS");   //Fit
      //f->Print("V");

      //adc_of_clusters->DrawCopy("e");
      //gPad->Modified();
      //pedestalcanvas->Update();
      //pedestalcanvas->Close();


      //Define fitfunction == sum of Gaussians with distance expected_gain; Parameters 0 and 1 for optional linear background
      TF1 *photopeaks = new TF1("photopeaks", fpeaks, fitrange_low, fitrange_high,6+numberPhotopeaks);
           //Set start parameters
           photopeaks->SetParameters(par);
           //photopeaks->FixParameter(0,0.);
           //photopeaks->FixParameter(1,0.);
           //Set Par names
           photopeaks->SetParName(2,"mean_0");
           photopeaks->SetParName(3,"gain");
           photopeaks->SetParName(4,"width_0");
           photopeaks->SetParName(5,"width_p");
           //Set par Limits
           //photopeaks->SetParLimits(2, par[2]-fabs(expected_gain)/3., par[2] + fabs(expected_gain)/3.);//position of pedestal peak
           photopeaks->SetParLimits(2, 0,2);

	   photopeaks->SetParLimits(3, fabs(expected_gain)-fabs(expected_gain)/3, fabs(expected_gain)+fabs(expected_gain)/3./*90.*/);//gain
	   
	   ///	   photopeaks->SetParLimits(4,0.,2);//sigma of pedestal                                                                                                       
	   /// photopeaks->SetParLimits(5,0.,0.3);//change in sigma      
	
	   //photopeaks->SetParLimits(4,0.,fabs(expected_gain)/2.);//sigma of pedestal
           //photopeaks->SetParLimits(5,0.,0.3);//change in sigma

           //Set Parameter Names for norm of peaks
           for (Int_t p=0;p<numberPhotopeaks;p++) {
               std::stringstream norm;
               norm << "norm_" << p;
                   photopeaks->SetParName(p+6,norm.str().c_str());
                   photopeaks->SetParLimits(p+6,10.,1000000.);
                   //if(p>3) photopeaks->SetParLimits(p+6,10.,1000000.);
               }

      //Fit
      TFitResultPtr e = adc_of_clusters->Fit("photopeaks","RS");   //Fit
              e->Print("V");

      //Measure gain
      expected_gain = photopeaks->GetParameter(3);

      std::cout<<"LED-data gain correction ="<<  expected_gain <<std::endl;

      //Draw if "draw"option is set
      TPaveText *info = new TPaveText(0.75,0.55,0.85,0.65,"brNDC");
      info->AddText("Gain =");
      info->AddText(Form("%f", expected_gain));

      if(draw){
         adc_of_clusters->GetXaxis()->SetRangeUser(-1.,15.);
         adc_of_clusters->DrawCopy("e");
         info->Draw("same");
         gPad->Modified();
         canvas->Update();

      }

     canvas->Close();
     gain = expected_gain;
     return gain;
}

void DataManager::draw_collectedCharge(std::string run_number, int uplink, std::string string_threshold)
{

  std::stringstream stream;

  std::string canvasname = "collected_charge_histogram" + std::to_string(uplink);
  TCanvas* Canvas = new TCanvas(canvasname.c_str(), canvasname.c_str(), 1200, 900);

  m_collectedChargeHistogram[uplink]->DrawCopy("e");

  gPad->Modified();
  Canvas->Update();

  stream.str(std::string());
  stream << "/home/scifi_testbeam14/sw/tools/MirrorReflectivity/cluster_analysis_MirrorStudy/histograms/" << run_number << "_uplink"<< uplink << "_collected_charge_histogram_notInvertd" << string_threshold << ".root";
  TFile file(stream.str().c_str(),"RECREATE");
  //Canvas->Write();
  m_collectedChargeHistogram[uplink]->Write();
  file.Close();

}

