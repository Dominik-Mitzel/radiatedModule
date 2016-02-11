#include "gainAnalysis.h"


void setRootStyle()
{
  //gStyle->SetOptStat(1111);
  gStyle->SetOptFit(0);//1111 Default
  gStyle->SetCanvasColor(10);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameLineWidth(1);
  gStyle->SetFrameFillColor(10);
  gStyle->SetPadColor(10);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTopMargin(0.15);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPadGridX(true);
  gStyle->SetPadGridY(true);
  gStyle->SetStatColor(10);
  gStyle->SetStatX(.8);
  gStyle->SetStatY(.8);
  gStyle->SetStatH(.09);
  gStyle->SetHistLineWidth(1);
  gStyle->SetFuncWidth(1);
  gStyle->SetMarkerStyle(20);
  gStyle->SetTitleOffset(1.5, "y");

  gStyle->SetLineScalePS(3.0);
  gStyle->SetTextFont(42);
  gStyle->SetTitleFont(42, "X");
  gStyle->SetTitleFont(42, "Y");
  gStyle->SetTitleFont(42, "Z");
  gStyle->SetLabelFont(42, "X");
  gStyle->SetLabelFont(42, "Y");
  gStyle->SetLabelFont(42, "Z");
  gStyle->SetLabelSize(0.03, "X");
  gStyle->SetLabelSize(0.03, "Y");
  gStyle->SetLabelSize(0.03, "Z");

  int NRGBs = 5;
  int NCont = 255;
  double stops[] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  double red[]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    double green[] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    double blue[]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
  }

//IMPORTANT: Set number of photopeaks you want to fit!!
int nPhotopeaks = 3;


//Define photopeaks function which consists of Gaussian peaks with the distance = gain
Double_t fpeaks(Double_t *x, Double_t *par){
  Double_t result = par[0] + par[1]*x[0];
  for (Int_t p=0;p<nPhotopeaks;p++) {
    Double_t norm  = par[p+6];
    Double_t mean  = par[2] + p * par[3];
    Double_t sigma_0 = par[4];
    Double_t sigma = par[5];
    if(p==0)result += norm*TMath::Gaus(x[0],mean,sigma_0);
    else result += norm*TMath::Gaus(x[0],mean,sqrt(pow(sigma_0,2)+p*pow(sigma,2)));

  }
  return result;
}

void gainAnalysis(TString filename, TString gainname, int uplink){

  char tmp[256];
  
  if(uplink == 31 || uplink ==34) nPhotopeaks = 7;
  if(uplink == 36) nPhotopeaks = 4;
 if(uplink == 10) nPhotopeaks = 6;
  if(uplink == 38) nPhotopeaks = 3;

  //studies of radiated module
  if(uplink == 10) nPhotopeaks = 4;//4
  if(uplink ==11 || uplink==12 || uplink==13) nPhotopeaks = 4;//4

  

  //Load LEDfile
  TFile f(filename.Data());

  //Set Readout Tree
   TTree * T = NULL;
   T = (TTree*) f.Get("rawData");

   Int_t nEvents = T->GetEntries();

   printf("NEntries = %d\n", nEvents);

   //Define array which will be filled with the adc data
   Float_t adc[384];
   TString adc_title("");
   Float_t channel[384];
   TString channel_title("");

   //instead of pedestal-subtracting, just subtract an arbitrary value!!
   int arbitrary_offset = 400;
   //if(uplink == 32 || uplink == 33) arbitrary_offset = 450;
   if(uplink == 35) arbitrary_offset = 500;
   if(uplink == 37) arbitrary_offset = 450;

  int channel_range_down = 0;
  int channel_range_up = 128;
  //if(uplink ==31 || uplink == 34) {
  //    channel_range_down = 128;
  //    channel_range_up = 256;
  //}

  //2D Histogram of the data
  TH2D* adc_vs_channel = new TH2D("adc_vs_channel", ";channel;adc", 128, channel_range_down + 1, channel_range_up +1, 500, 0., 1000.);

  //define which branch of the datatree will be readout
  for( Int_t i = channel_range_down; i < channel_range_up; i++){
    //The name of the branches is: Uplink_<uplinkNumber>_adc_<channel>
    adc_title.Clear();
    adc_title.Append("Uplink_");
    adc_title.Append(std::to_string(uplink));
    adc_title.Append("_adc_");
    adc_title.Append(std::to_string(i+1));

    T -> SetBranchAddress(adc_title.Data(), &adc[i] ) ;
    channel[i] = float(i+1);

  }

  //read the data from the branches and fill the 2D histogram
  for ( Int_t j = 0 ; j < nEvents ; j++ ) {
     T -> GetEntry( j ) ;

     for( Int_t i = channel_range_down; i < channel_range_up; i++){
          adc_vs_channel->Fill(channel[i], adc[i] - arbitrary_offset);
     }
  }

  //Save 2D histogram to check if the data looks right
  TFile RootFile("adc_vs_channel_temporary.root", "RECREATE");
  adc_vs_channel->Write();
  RootFile.Close();

  float gain[128];
  TH1* histograms[128];

  //!!You have two options: Fit only one single channel(selectChannel) by executing FitPhotopeaks or
  // fit all channels to determine the gain of the whole array by executing GainMeasurement
  int selectChannel = 17;
  //FitPhotopeaks(nPhotopeaks, uplink, selectChannel, true, gain, histograms, adc_vs_channel);
  GainMeasurement(nPhotopeaks, uplink, gainname.Data(), true, adc_vs_channel);
}

void FitPhotopeaks(int numberPhotopeaks, int uplink, int channel, bool draw, float* gain, TH1** histograms, TH2* adc_vs_channel)
{

  char tmp[256];
  TCanvas* canvas = NULL;
  TH1* YProjection;

  double mean = 0;
  double rms = 0;

  //channel 118 and 120 often exhibit a strange behavior with small gain
  //if(channel==53 || uplink ==33) numberPhotopeaks = 4;
  //if(uplink == 34 && channel > 50 && channel < 54) numberPhotopeaks = 10;


  canvas = new TCanvas("ProjectionY", "adc-Signal", 1600, 1200);
  sprintf(tmp,"uplink%d_chan%d",uplink,channel);

  //Create the YProjection histogram of the 2D data at channel
  YProjection = adc_vs_channel->ProjectionY(tmp,adc_vs_channel->GetXaxis()->FindBin(channel),adc_vs_channel->GetXaxis()->FindBin(channel));


  Double_t par[3000];

  //Use TSpectrum to search for peaks
  TSpectrum *s = new TSpectrum(numberPhotopeaks);
  Int_t nfound = s->Search(YProjection,0.1,"new",0.01);//first float number: sigma of searched peaks(how significant is the peak), second float number: amplitude threshold for smaller second peak relative to highest

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
       Int_t bin = YProjection->GetXaxis()->FindBin(xp);
       Float_t yp = YProjection->GetBinContent(bin);
       par[3*p+4] = yp;
       par[3*p+5] = 5.;
       }

  //Estimate expected gain to define function range by finding maximum peak and dividing by number of peaks
  ///double expected_gain = xpeaks[1] - xpeaks[0];
  double expected_gain = 51; //added for november testbeam 
  std::cout<<"xpeaks[1] - xpeaks[0] = "<< expected_gain<< std::endl;
  //check if found peaks look reasonable, else: use 125 which was usually used in the test beam. Except!!! Christian modules
  

  //if((xpeaks[1] - xpeaks[0]> 0.3*(xpeaks[2] - xpeaks[0]) && (xpeaks[1] - xpeaks[0]< 0.65*(xpeaks[2] - xpeaks[0])) && nfound > 1 && (xpeaks[1] - xpeaks[0]) < 150. && (xpeaks[1] - xpeaks[0]) > 30.)) expected_gain = xpeaks[1] - xpeaks[0];
  // else {expected_gain = 40;//Important: Choose reasonable gain as start parameter!!!!
  //    if((channel == 76/* || channel == 78*/) && uplink == 10) expected_gain = 23;
     //    if((uplink == 32 || uplink ==33) && (channel == 58 || channel == 60)) expected_gain = 55.;//28;
  //}
  //if(expected_gain > 70) expected_gain = 60;
  par[0] = 0.;//potential linear slope
  par[1] = 0.;//potential linear slope
  par[2] = xpeaks[0];//position of pedestal peak
  //if((uplink == 32 || uplink ==33) && (channel == 58 || channel == 60)) par[2] = 80.;//position of pedestal peak
  par[3] = fabs(expected_gain);
  par[4] = 6.;//sigma of pedestal peak
  par[5] = 3.;//change in sigma for one peak sigma_i = sqrt(sigma_0^2 + i sigma_2)

  std::cout<<"nfound = "<< nfound<< std::endl;
  std::cout<<"expected_gain = "<< expected_gain<< std::endl;
  std::cout<<"0th peak position = "<< par[2]<< std::endl;

  //Define fitrange
  Double_t fitrange_low;
  Double_t fitrange_high;

  fitrange_low = par[2]-fabs(expected_gain)/2.-50;//position of pedestal peak -fabs(expected_gain)/2.-50
  fitrange_high = (numberPhotopeaks-0.5) * fabs(expected_gain)+ par[2];//position of pedestal peak npeaks*fabs(expected_gain)


  //Define fitfunction == sum of Gaussians with distance expected_gain; Parameters 0 and 1 for optional linear background
  TF1 *photopeaks = new TF1("photopeaks", fpeaks, fitrange_low, fitrange_high,6+numberPhotopeaks);
  //Set start parameters
  photopeaks->SetParameters(par);
  photopeaks->FixParameter(0,0.);
  photopeaks->FixParameter(1,0.);
  //Set Par names
  photopeaks->SetParName(2,"mean_0");
  photopeaks->SetParName(3,"gain");
  photopeaks->SetParName(4,"width_0");
  photopeaks->SetParName(5,"width_p");
  //Set par Limits
  photopeaks->SetParLimits(2, par[2]-fabs(expected_gain)/4., par[2] + fabs(expected_gain)/4.);//position of pedestal peak
  //photopeaks->SetParLimits(3, fabs(expected_gain)-fabs(expected_gain)/6, fabs(expected_gain)+fabs(expected_gain)/6/*90.*/);//gain
  photopeaks->SetParLimits(3,35,65/*90.*/);//gain (45-65) before DAC setting 
  if(uplink==11) photopeaks->SetParLimits(3,40,65/*90.*/);//gain  

//if(uplink == 21 && channel == 73) photopeaks->SetParLimits(3, 0., /*fabs(expected_gain)-fabs(expected_gain)/3, fabs(expected_gain)+fabs(expected_gain)/3.*/67.);//gain
  //if(channel==118 || channel==120)photopeaks->SetParLimits(3, fabs(expected_gain)-fabs(expected_gain)/4, 170.);//gain
  photopeaks->SetParLimits(4,1.,fabs(expected_gain)/3.);//sigma of pedestal
  photopeaks->SetParLimits(5,0.5,15.);//change in sigma

  //Set Parameter Names for norm of peaks
  for (Int_t p=0;p<numberPhotopeaks;p++) {
     std::stringstream norm;
     norm << "norm_" << p;
         photopeaks->SetParName(p+6,norm.str().c_str());

     }

  //Fit
  TFitResultPtr e = YProjection->Fit("photopeaks","RS");   //Fit
           e->Print("V");

  //Measure gain
	  
  expected_gain = photopeaks->GetParameter(3);
  //if(uplink == 13 && ( channel == 4 || channel ==6) expected_gain = tempGain;//43.68/1.980;  
   
 

  std::cout<<"GAIN ="<<  expected_gain <<std::endl;
  //expected_gain *= 100;
  //expected_gain = int(expected_gain);
  //expected_gain = double(expected_gain)/100;

  
  //Draw if "draw"option is set
  TPaveText *info = new TPaveText(0.75,0.55,0.85,0.65,"brNDC");
  info->AddText("Gain =");
  info->AddText(std::to_string(expected_gain).substr(0, 4).c_str());

  
  if(draw){
     gStyle->SetOptStat(0);
     YProjection->GetXaxis()->SetRangeUser(-50.,1500.);
     YProjection->DrawCopy("e");
     info->Draw("same");
     gPad->Modified();
     canvas->Update();

     TFile RootFile("fit_photopeaks_temporary.root", "RECREATE");
     YProjection->Write();
     RootFile.Close();

  }
  else{
     canvas->Close();
  }

  gain[channel-1] = expected_gain;  
  
  //exceptions for gain measurements
  //suspicious channels
  if(uplink == 13 && ( channel == 4 || channel ==6 || channel ==55 ||channel==57 )) gain[channel-1]= gain[channel-2] ;  //take value of previous channel for suspicious channels
  if(uplink == 12 && ( channel == 21 || channel ==23 )) gain[channel-1]= gain[channel-2] ;  //take value of previous channel for suspicious channels              
  //dead channels
  if(uplink == 10 && ( channel == 103 )) gain[channel-1]= gain[channel-2] ;  //take value of previous channel for suspicious channels              
  if(uplink == 12 && ( channel == 59 || channel ==41 || channel ==39 )) gain[channel-1]= gain[channel-2] ;  //take value of previous channel for suspicious channels              



  histograms[channel-1] = YProjection;

}

void GainMeasurement(int selectNumberPeaks_Gain, int uplink, const char*pathToGain, bool ShowAllPlots, TH2* adc_vs_channel)
{

  int channel_range_down = 0;
  int channel_range_up = 128;
  //if(uplink ==31 || uplink == 34) {
  //    channel_range_down = 128;
  //    channel_range_up = 256;
  //}

  char tmp[256];
  float gain[channel_range_up];
  float channel[channel_range_up];
  TH1* histograms[channel_range_up];

  TCanvas* canvas_Gain = NULL;
  FILE* resultLog = NULL;

  //We also want to save the calculated gain distribution into a txtFile: ".root" from path and replace by .txt
  TString filename("");
  filename.Append(pathToGain);
  filename.ReplaceAll(".root",".txt");
  std::cout<<"filename = "<< filename.Data()<< std::endl;


  for (int chan = 0; (chan < channel_range_up); ++chan) {
      channel[chan] = float(chan+1);
      gain[chan] = -1;
  }
  //Loop over all channels, fit Photopeaks and calculate gain
  for (int chan = channel_range_down; (chan < channel_range_up); ++chan) {
      FitPhotopeaks(selectNumberPeaks_Gain, uplink, chan+1, false, gain, histograms, adc_vs_channel);
      if(gain[chan] < -2 || gain[chan] > 1000) gain[chan] = -1.;//remove wrongly determined gain
  }

  //Plot gain distribution as TGraph
  TGraph* gain_measurement = new TGraph(channel_range_up, channel, gain);
  
  
  canvas_Gain = new TCanvas("Gain", "Gain", 900, 600);
  gStyle->SetOptStat(0);
  gain_measurement->GetHistogram()->SetYTitle("Gain [adc/peak]");
  gain_measurement->GetHistogram()->SetXTitle("Channel");
  gain_measurement->GetHistogram()->SetTitle("");
  gain_measurement->Draw("AP");

  TFile RootFile(pathToGain, "RECREATE");
  gain_measurement->Write();
  RootFile.Close();

  //canvas_Gain->Clear();
  //canvas_Gain->Close();


  //save gain values into txtfile
  resultLog = fopen(filename.Data(),"w");
  fprintf(resultLog,"-----Gain Measurement of --------\n\n");
  fprintf(resultLog,"%s\t \n",pathToGain);
  fprintf(resultLog,"channel\t gain\t \n");

  for (int chan = 1; (chan < 257); ++chan) {
      fprintf(resultLog,"%d\t %f\t \n",chan,gain[chan-1]);
  }

  fclose(resultLog);

  //Create Canvases with plots of all channels with fits if option "ShowAllPlots" is set
  TCanvas* canvas_Plots = NULL;
  int xPadNum = 4;
  int yPadNum = 4;
  int padPerCanvas = xPadNum*yPadNum;
  int canvasindex = 0;
  filename.ReplaceAll(".txt","_Canvas");

  //Plot YProjection of every channel if wanted. 16 are printed into one canvas
  if(ShowAllPlots){
    for(int chan=channel_range_down; chan<channel_range_up; ++chan){
      if(chan%padPerCanvas ==0){

          if(canvasindex>0){
              TFile RootFile_Canvas(filename.Data(), "RECREATE");
              canvas_Plots->Write();
              //canvas_Plots->Close();
              filename.Remove(filename.Sizeof()-7, 7);
          }


          sprintf(tmp,"uplink%d_canvas%d",uplink,canvasindex+1);
          canvas_Plots = new TCanvas(tmp,tmp,1000,900);
          gStyle->SetOptStat(0);
          canvas_Plots->Divide(xPadNum,yPadNum);
          canvasindex += 1;

          char integer_string[32];
          sprintf(integer_string, "%d", canvasindex);

          filename.Append(integer_string);
          filename.Append(".root");

      }

      //write gain into plots
      TPaveText *info = new TPaveText(0.7,0.5,0.9,0.7,"brNDC");
      info->AddText("Gain =");
      info->AddText(Form("%f", gain[chan]));

      std::stringstream  title;
      title << "Channel " << chan+1 ;
      canvas_Plots->cd(chan%padPerCanvas+1);
      histograms[chan]->GetXaxis()->SetRangeUser(-50.,1500.);
      histograms[chan]->GetYaxis()->SetRangeUser(-1.,300.);
      histograms[chan]->SetTitle(title.str().c_str());
      histograms[chan]->DrawCopy("");
      info->Draw("same");

      gPad->Modified();
      canvas_Plots->Update();

    }
    TFile RootFile_Canvas(filename.Data(), "RECREATE");
    canvas_Plots->Write();
    //canvas_Plots->Close();
  }
  //getchar();
}
