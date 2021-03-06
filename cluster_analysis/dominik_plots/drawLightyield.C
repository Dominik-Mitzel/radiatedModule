#include <TF1.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TString.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TFile.h>
#include <TH1.h>
#include <TROOT.h>
//#include "/work/mitzel/D2Kmunu/Code/Thesis/chapter_04/NeutrinoRec/dcastyle.C"

void drawLightyield(bool drawRatio=false) {

  gStyle->SetOptStat(0);

  TFile *f1= new TFile("1029X.txt_uplink10_overview_thresh150515.root","OPEN");
  TFile *f2= new TFile("1129X.txt_uplink11_overview_thresh150515.root","OPEN");
  TFile *f3= new TFile("1229X.txt_uplink12_overview_thresh150515.root","OPEN");
  TFile *f4= new TFile("1329X.txt_uplink13_overview_thresh150515.root","OPEN");
  
  //slayer
  TFile *fs1= new TFile("slayer4.txt_uplink5_overview_thresh150515.root","OPEN");
  TFile *fs2= new TFile("slayer3.txt_uplink6_overview_thresh150515.root","OPEN");
  TFile *fs3= new TFile("slayer2.txt_uplink7_overview_thresh150515.root","OPEN");
  TFile *fs4= new TFile("slayer1.txt_uplink8_overview_thresh151515.root","OPEN");
 
  //octolayer
  TFile *fo1= new TFile("slayer4.txt_uplink1_overview_thresh150515.root","OPEN");
  TFile *fo2= new TFile("slayer3.txt_uplink2_overview_thresh150515.root","OPEN");
  TFile *fo3= new TFile("slayer2.txt_uplink3_overview_thresh150515.root","OPEN");
  TFile *fo4= new TFile("slayer1.txt_uplink4_overview_thresh150515.root","OPEN");


  //no mirror 
  TFile *f1nM= new TFile("1030X.txt_uplink10_overview_thresh150515.root","OPEN");
  TFile *f2nM= new TFile("1130X.txt_uplink11_overview_thresh150515.root","OPEN");
  TFile *f3nM= new TFile("1231X.txt_uplink12_overview_thresh150515.root","OPEN");
  TFile *f4nM= new TFile("1330X.txt_uplink13_overview_thresh150515.root","OPEN");
 
  TFile *f5= new TFile("/home/scifi_testbeam14/radiatedModule/led_gain/btsoftware_10292_calib_led_gain_uplink10.root","OPEN");
  TFile *f6= new TFile("/home/scifi_testbeam14/radiatedModule/led_gain/btsoftware_11292_calib_led_gain_uplink11.root","OPEN");
  TFile *f7= new TFile("/home/scifi_testbeam14/radiatedModule/led_gain/btsoftware_12292_calib_led_gain_uplink12.root","OPEN");
  TFile *f8= new TFile("/home/scifi_testbeam14/radiatedModule/led_gain/btsoftware_13292_calib_led_gain_uplink13.root","OPEN");

  TFile *f9= new TFile("2026X.txt_uplink10_overview_thresh150515.root","OPEN");
  TFile *f10= new TFile("2126X.txt_uplink11_overview_thresh150515.root","OPEN");
  TFile *f11= new TFile("2226X.txt_uplink12_overview_thresh150515.root","OPEN");
  TFile *f12= new TFile("2326X.txt_uplink13_overview_thresh150515.root","OPEN");

  TFile *f13= new TFile("3026X.txt_uplink10_overview_thresh150515.root","OPEN");
  TFile *f14= new TFile("3126X.txt_uplink11_overview_thresh150515.root","OPEN");
  TFile *f15= new TFile("3226X.txt_uplink12_overview_thresh150515.root","OPEN");
  TFile *f16= new TFile("3326X.txt_uplink13_overview_thresh150515.root","OPEN");

  TFile *f17= new TFile("4026X.txt_uplink10_overview_thresh150515.root","OPEN");
  TFile *f18= new TFile("4126X.txt_uplink11_overview_thresh150515.root","OPEN");
  TFile *f19= new TFile("4226X.txt_uplink12_overview_thresh150515.root","OPEN");
  TFile *f20= new TFile("4326X.txt_uplink13_overview_thresh150515.root","OPEN");


  TH1* h1_charge_10 =(TH1D*) f1->Get("chargeBins");
  TH1* h1_cluster_10 =(TH1D*) f1->Get("clustersBins");

  TH1* h1_charge_11 =(TH1D*) f2->Get("chargeBins");
  TH1* h1_cluster_11 =(TH1D*) f2->Get("clustersBins");

  TH1* h1_charge_12 =(TH1D*) f3->Get("chargeBins");
  TH1* h1_cluster_12 =(TH1D*) f3->Get("clustersBins");

  TH1* h1_charge_13 =(TH1D*) f4->Get("chargeBins");
  TH1* h1_cluster_13 =(TH1D*) f4->Get("clustersBins");

  //no mirror 
  TH1* h1_charge_10nM =(TH1D*) f1nM->Get("chargeBins");
  TH1* h1_cluster_10nM =(TH1D*) f1nM->Get("clustersBins");

  TH1* h1_charge_11nM =(TH1D*) f2nM->Get("chargeBins");
  TH1* h1_cluster_11nM =(TH1D*) f2nM->Get("clustersBins");

  TH1* h1_charge_12nM =(TH1D*) f3nM->Get("chargeBins");
  TH1* h1_cluster_12nM =(TH1D*) f3nM->Get("clustersBins");

  TH1* h1_charge_13nM =(TH1D*) f4nM->Get("chargeBins");
  TH1* h1_cluster_13nM =(TH1D*) f4nM->Get("clustersBins");
  //

  //slayer test beam 

  TH1* h1_charge_s10 =(TH1D*) fs1->Get("chargeBins");
  TH1* h1_cluster_s10 =(TH1D*) fs1->Get("clustersBins");

  TH1* h1_charge_s11 =(TH1D*) fs2->Get("chargeBins");
  TH1* h1_cluster_s11 =(TH1D*) fs2->Get("clustersBins");

  TH1* h1_charge_s12 =(TH1D*) fs3->Get("chargeBins");
  TH1* h1_cluster_s12 =(TH1D*) fs3->Get("clustersBins");

  TH1* h1_charge_s13 =(TH1D*) fs4->Get("chargeBins");
  TH1* h1_cluster_s13 =(TH1D*) fs4->Get("clustersBins");

  //octo test beam 

  TH1* h1_charge_o10 =(TH1D*) fo1->Get("chargeBins");
  TH1* h1_cluster_o10 =(TH1D*) fo1->Get("clustersBins");

  TH1* h1_charge_o11 =(TH1D*) fo2->Get("chargeBins");
  TH1* h1_cluster_o11 =(TH1D*) fo2->Get("clustersBins");

  TH1* h1_charge_o12 =(TH1D*) fo3->Get("chargeBins");
  TH1* h1_cluster_o12 =(TH1D*) fo3->Get("clustersBins");

  TH1* h1_charge_o13 =(TH1D*) fo4->Get("chargeBins");
  TH1* h1_cluster_o13 =(TH1D*) fo4->Get("clustersBins");



  TH1* h1_charge_210 =(TH1D*) f9->Get("chargeBins");
  TH1* h1_cluster_210 =(TH1D*) f9->Get("clustersBins");

  TH1* h1_charge_211 =(TH1D*) f10->Get("chargeBins");
  TH1* h1_cluster_211 =(TH1D*) f10->Get("clustersBins");

  TH1* h1_charge_212 =(TH1D*) f11->Get("chargeBins");
  TH1* h1_cluster_212 =(TH1D*) f11->Get("clustersBins");

  TH1* h1_charge_213 =(TH1D*) f12->Get("chargeBins");
  TH1* h1_cluster_213 =(TH1D*) f12->Get("clustersBins");




  TH1* h1_charge_310 =(TH1D*) f13->Get("chargeBins");
  TH1* h1_cluster_310 =(TH1D*) f13->Get("clustersBins");

  TH1* h1_charge_311 =(TH1D*) f14->Get("chargeBins");
  TH1* h1_cluster_311 =(TH1D*) f14->Get("clustersBins");

  TH1* h1_charge_312 =(TH1D*) f15->Get("chargeBins");
  TH1* h1_cluster_312 =(TH1D*) f15->Get("clustersBins");

  TH1* h1_charge_313 =(TH1D*) f16->Get("chargeBins");
  TH1* h1_cluster_313 =(TH1D*) f16->Get("clustersBins");



  TH1* h1_charge_410 =(TH1D*) f17->Get("chargeBins");
  TH1* h1_cluster_410 =(TH1D*) f17->Get("clustersBins");

  TH1* h1_charge_411 =(TH1D*) f18->Get("chargeBins");
  TH1* h1_cluster_411 =(TH1D*) f18->Get("clustersBins");

  TH1* h1_charge_412 =(TH1D*) f19->Get("chargeBins");
  TH1* h1_cluster_412 =(TH1D*) f19->Get("clustersBins");

  TH1* h1_charge_413 =(TH1D*) f20->Get("chargeBins");
  TH1* h1_cluster_413 =(TH1D*) f20->Get("clustersBins");


  TGraph* gain_10 = (TGraph*) f5->Get("Graph");
  TGraph* gain_11 = (TGraph*) f6->Get("Graph");
  TGraph* gain_12 = (TGraph*) f7->Get("Graph");
  TGraph* gain_13 = (TGraph*) f8->Get("Graph");
  //dcastyle();

  h1_charge_10->GetYaxis()->SetRangeUser(0,30);
  h1_charge_11->GetYaxis()->SetRangeUser(0,30);
  h1_charge_12->GetYaxis()->SetRangeUser(0,30);
  h1_charge_13->GetYaxis()->SetRangeUser(0,30);

  h1_charge_10->GetYaxis()->SetTitle("charge [pe]");
  h1_charge_11->GetYaxis()->SetTitle("charge [pe]");
  h1_charge_12->GetYaxis()->SetTitle("charge [pe]");
  h1_charge_13->GetYaxis()->SetTitle("charge [pe]");

  h1_charge_s10->GetYaxis()->SetRangeUser(0,30);
  h1_charge_s11->GetYaxis()->SetRangeUser(0,30);
  h1_charge_s12->GetYaxis()->SetRangeUser(0,30);
  h1_charge_s13->GetYaxis()->SetRangeUser(0,30);

  h1_charge_s10->GetYaxis()->SetTitle("charge [pe]");
  h1_charge_s11->GetYaxis()->SetTitle("charge [pe]");
  h1_charge_s12->GetYaxis()->SetTitle("charge [pe]");
  h1_charge_s13->GetYaxis()->SetTitle("charge [pe]");
   

  h1_charge_o10->GetYaxis()->SetRangeUser(0,30);
  h1_charge_o11->GetYaxis()->SetRangeUser(0,30);
  h1_charge_o12->GetYaxis()->SetRangeUser(0,30);
  h1_charge_o13->GetYaxis()->SetRangeUser(0,30);

  h1_charge_o10->GetYaxis()->SetTitle("charge [pe]");
  h1_charge_o11->GetYaxis()->SetTitle("charge [pe]");
  h1_charge_o12->GetYaxis()->SetTitle("charge [pe]");
  h1_charge_o13->GetYaxis()->SetTitle("charge [pe]");



  //  h1_charge_10->GetXaxis()->SetRangeUser(64,128);
  //h1_charge_11->GetXaxis()->SetRangeUser(0,64);
  //h1_charge_12->GetXaxis()->SetRangeUser(64,128);
  //h1_charge_13->GetXaxis()->SetRangeUser(0,64);
 
  h1_charge_10->GetXaxis()->SetTitle("channel");
  h1_charge_11->GetXaxis()->SetTitle("channel");
  h1_charge_12->GetXaxis()->SetTitle("channel");
  h1_charge_13->GetXaxis()->SetTitle("channel");
 
  h1_cluster_10->GetYaxis()->SetTitle("#cluster");
  h1_cluster_11->GetYaxis()->SetTitle("#cluster ");
  h1_cluster_12->GetYaxis()->SetTitle("#cluster");
  h1_cluster_13->GetYaxis()->SetTitle("#cluster");
  
 
  h1_cluster_10->GetYaxis()->SetRangeUser(0,3500);
  h1_cluster_11->GetYaxis()->SetRangeUser(0,3500);
  h1_cluster_12->GetYaxis()->SetRangeUser(0,3500);
  h1_cluster_13->GetYaxis()->SetRangeUser(0,3500);
 
  h1_charge_s10->GetXaxis()->SetTitle("channel");
  h1_charge_s11->GetXaxis()->SetTitle("channel");
  h1_charge_s12->GetXaxis()->SetTitle("channel");
  h1_charge_s13->GetXaxis()->SetTitle("channel");
 
  h1_cluster_s10->GetYaxis()->SetTitle("#cluster");
  h1_cluster_s11->GetYaxis()->SetTitle("#cluster ");
  h1_cluster_s12->GetYaxis()->SetTitle("#cluster");
  h1_cluster_s13->GetYaxis()->SetTitle("#cluster");
  
 
  h1_cluster_s10->GetYaxis()->SetRangeUser(0,3500);
  h1_cluster_s11->GetYaxis()->SetRangeUser(0,3500);
  h1_cluster_s12->GetYaxis()->SetRangeUser(0,3500);
  h1_cluster_s13->GetYaxis()->SetRangeUser(0,3500);

  //h1_cluster_10->GetXaxis()->SetRangeUser(64,128);
  //h1_cluster_11->GetXaxis()->SetRangeUser(0,64);
  //h1_cluster_12->GetXaxis()->SetRangeUser(64,128);
  //h1_cluster_13->GetXaxis()->SetRangeUser(0,64);
 
  h1_cluster_10->GetXaxis()->SetTitle("channel");
  h1_cluster_11->GetXaxis()->SetTitle("channel");
  h1_cluster_12->GetXaxis()->SetTitle("channel");
  h1_cluster_13->GetXaxis()->SetTitle("channel");
 

  h1_charge_10->SetTitle("light yield Uplink10");
  h1_charge_11->SetTitle("light yield Uplink11");
  h1_charge_12->SetTitle("light yield Uplink12");
  h1_charge_13->SetTitle("light yield Uplink13");

  h1_charge_s10->SetTitle("light yield Uplink10");
  h1_charge_s11->SetTitle("light yield Uplink11");
  h1_charge_s12->SetTitle("light yield Uplink12");
  h1_charge_s13->SetTitle("light yield Uplink13");


  h1_charge_10->SetLineWidth(2.);
  h1_charge_11->SetLineWidth(2.);
  h1_charge_12->SetLineWidth(2.);
  h1_charge_13->SetLineWidth(2.);
  h1_charge_210->SetLineWidth(2.);
  h1_charge_211->SetLineWidth(2.);
  h1_charge_212->SetLineWidth(2.);
  h1_charge_213->SetLineWidth(2.);
  h1_charge_310->SetLineWidth(2.);
  h1_charge_311->SetLineWidth(2.);
  h1_charge_312->SetLineWidth(2.);
  h1_charge_313->SetLineWidth(2.);
  h1_charge_410->SetLineWidth(2.);
  h1_charge_411->SetLineWidth(2.);
  h1_charge_412->SetLineWidth(2.);
  h1_charge_413->SetLineWidth(2.);

  TFile* target = new TFile("lightYield.root","RECREATE");
 
  TCanvas *c1 = new TCanvas("c","c",700,600);
  
 
  c1->Divide(4,2,0.,0.);
  
  c1->cd(1)->SetRightMargin(0.01);

  h1_charge_10->Draw();
  ///h1_charge_210->Draw("SAME");
  h1_charge_210->SetLineColor(2);
  h1_charge_310->SetLineColor(1);
  //h1_charge_310->Draw("SAME");
  h1_charge_410->SetLineColor(8);
  //h1_charge_410->Draw("SAME");
  h1_charge_s10->SetLineColor(8);
  h1_charge_s10->Draw("SAME");
  


  TLatex *t1 = new TLatex();                                                                                                                                                            
  t1->SetNDC();                                                                                                                                                                         
  t1->SetTextAlign(13);                                                                                                                                                                 
  t1->SetTextFont(63);                                                                                                                                                                  
  t1->SetTextSizePixels(10);                                                                                                                                                            
  
  t1->DrawLatex(0.50,0.90,"#color[4]{Lab measurement}");
  t1->DrawLatex(0.50,0.85,"#color[8]{November testbeam}");                                                                                                                                

  //t1->DrawLatex(0.50,0.90,"#color[4]{0 cm from mirror}");                                                                                                                                
  //t1->DrawLatex(0.50,0.85,"#color[2]{20 cm from mirror}");                                                                                                                             
  //t1->DrawLatex(0.50,0.80,"#color[1]{50 cm from mirror}");                                                                                                                             
  //t1->DrawLatex(0.50,0.75,"#color[8]{150 cm from mirror}");                                                                                                                             
 
  c1->cd(1)->SetGridy();



  c1->cd(2)->SetLeftMargin(0.001);
  c1->cd(2)->SetRightMargin(0.01);
  h1_charge_11->Draw();
  //h1_charge_211->Draw("SAME");
  h1_charge_211->SetLineColor(2);
  h1_charge_311->SetLineColor(1);
  //  h1_charge_311->Draw("SAME");
  h1_charge_411->SetLineColor(8);
  //h1_charge_411->Draw("SAME");
  h1_charge_s11->SetLineColor(8);
  h1_charge_s11->Draw("SAME");
 
  c1->cd(2)->SetGridy();




  c1->cd(3)->SetLeftMargin(0.001);
  c1->cd(3)->SetRightMargin(0.01);
  h1_charge_12->Draw();
  //h1_charge_212->Draw("SAME");
  h1_charge_212->SetLineColor(2);
  h1_charge_312->SetLineColor(1);
  //h1_charge_312->Draw("SAME");
  h1_charge_412->SetLineColor(8);
  //h1_charge_412->Draw("SAME");
  h1_charge_s12->SetLineColor(8);
  h1_charge_s12->Draw("SAME");
 
  c1->cd(3)->SetGridy();


  c1->cd(4)->SetLeftMargin(0.001);
  c1->cd(4)->SetRightMargin(0.01);
  h1_charge_13->Draw();
  //h1_charge_213->Draw("SAME");
  h1_charge_213->SetLineColor(2);
  h1_charge_313->SetLineColor(1);
  //h1_charge_313->Draw("SAME");
  h1_charge_413->SetLineColor(8);
  //h1_charge_413->Draw("SAME");
  h1_charge_s13->SetLineColor(8);
  h1_charge_s13->Draw("SAME");

  c1->cd(4)->SetGridy();


  c1->cd(5)->SetRightMargin(0.01);
  h1_cluster_10->Draw(); 
  //h1_cluster_210->Draw("SAME");
  h1_cluster_210->SetLineColor(2);
  h1_cluster_310->SetLineColor(1);
  //h1_cluster_310->Draw("SAME");
  h1_cluster_410->SetLineColor(8);
  //h1_cluster_410->Draw("SAME");
  h1_cluster_s10->SetLineColor(8);
  h1_cluster_s10->Draw("SAME");


  c1->cd(6)->SetLeftMargin(0.001);
  c1->cd(6)->SetRightMargin(0.01);
  h1_cluster_11->Draw(); 
  //h1_cluster_211->Draw("SAME");
  h1_cluster_211->SetLineColor(2);
  h1_cluster_311->SetLineColor(1);
  //h1_cluster_311->Draw("SAME");
  h1_cluster_411->SetLineColor(8);
  //h1_cluster_411->Draw("SAME");
  h1_cluster_s11->SetLineColor(8);
  h1_cluster_s11->Draw("SAME");
  

  c1->cd(7)->SetLeftMargin(0.001);
  c1->cd(7)->SetRightMargin(0.01);
  h1_cluster_12->Draw(); 
  //h1_cluster_212->Draw("SAME");
  h1_cluster_212->SetLineColor(2);
  h1_cluster_312->SetLineColor(1);
  //h1_cluster_312->Draw("SAME");
  h1_cluster_412->SetLineColor(8);
  //h1_cluster_412->Draw("SAME");
  h1_cluster_s12->SetLineColor(8);
  h1_cluster_s12->Draw("SAME");


  c1->cd(8)->SetLeftMargin(0.001);
  c1->cd(8)->SetRightMargin(0.01);
  h1_cluster_13->Draw()  ;
  //h1_cluster_213->Draw("SAME");
  h1_cluster_213->SetLineColor(2);
  h1_cluster_313->SetLineColor(1);
  //h1_cluster_313->Draw("SAME");
  h1_cluster_413->SetLineColor(8);
  //h1_cluster_413->Draw("SAME");
  h1_cluster_s13->SetLineColor(8);
  h1_cluster_s13->Draw("SAME");
  /*

  //c1->cd(9)->SetLeftMargin(0.001);
  c1->cd(9)->SetRightMargin(0.01);
  gain_10->Draw()  ;

  //c1->cd(10)->SetLeftMargin(0.001);
  c1->cd(10)->SetRightMargin(0.01);
  gain_11->Draw()  ;
  
  //c1->cd(11)->SetLeftMargin(0.001);
  c1->cd(11)->SetRightMargin(0.01);
  gain_12->Draw()  ;
  
  //c1->cd(12)->SetLeftMargin(0.001);
  c1->cd(12)->SetRightMargin(0.01);
  gain_13->Draw()  ;

  */

  c1->Write();
  

  h1_cluster_10->Write();
  h1_cluster_11->Write();
  h1_cluster_12->Write();
  h1_cluster_13->Write();
  h1_charge_10->Write();
  h1_charge_11->Write();
  h1_charge_12->Write();
  h1_charge_13->Write();
  gain_10->Write();
  gain_11->Write();
  gain_12->Write();
  gain_13->Write();
  
  if(drawRatio){

    TCanvas* b = new TCanvas();
    b->Divide(4,1,0,0);
    b->cd(1);
    h1_charge_10->Divide(h1_charge_s10);
    h1_charge_10->GetYaxis()->SetRangeUser(0,4);
    h1_charge_10->GetYaxis()->SetTitle("labMeasurement/Testbeam");
    h1_charge_10->Draw();
    b->cd(2);
    h1_charge_11->Divide(h1_charge_s11);
    h1_charge_11->GetYaxis()->SetRangeUser(0,4); 
    h1_charge_11->Draw();
    b->cd(3);
    h1_charge_12->Divide(h1_charge_s12);
    h1_charge_12->GetYaxis()->SetRangeUser(0,4);
    h1_charge_12->Draw();
    b->cd(4);
    h1_charge_13->Divide(h1_charge_s13);
    h1_charge_13->GetYaxis()->SetRangeUser(0,4);
    h1_charge_13->Draw();
  }

   
  TCanvas *c2 = new TCanvas("e","e",700,600);
  
 
  c2->Divide(4,0.,0.);
  
  c2->cd(1)->SetRightMargin(0.01);

  h1_charge_s10->Draw();
  //h1_charge_210->Draw("SAME");
  h1_charge_o10->SetLineColor(1);
  h1_charge_o10->Draw("SAME");


  TLatex *t2 = new TLatex();
  t2->SetNDC();
  t2->SetTextAlign(13);
  t2->SetTextFont(63);
  t2->SetTextSizePixels(10);

  t2->DrawLatex(0.50,0.90,"#color[1]{octo layer test beam}");
  t2->DrawLatex(0.50,0.85,"#color[8]{six layer test beam}");

  
  c2->cd(1)->SetGridy();

  c2->cd(2)->SetLeftMargin(0.001);
  c2->cd(2)->SetRightMargin(0.01);
  h1_charge_s11->Draw();
  h1_charge_o11->SetLineColor(1);
  h1_charge_o11->Draw("SAME");
 
  c2->cd(2)->SetGridy();

  c2->cd(3)->SetLeftMargin(0.001);
  c2->cd(3)->SetRightMargin(0.01);
  h1_charge_s12->Draw();
  h1_charge_o12->SetLineColor(1);
  h1_charge_o12->Draw("SAME");
 
  c2->cd(3)->SetGridy();
  
  c2->cd(4)->SetGridy();
  c2->cd(4)->SetLeftMargin(0.001);
  c2->cd(4)->SetRightMargin(0.01);
  h1_charge_s13->Draw();
  h1_charge_o13->SetLineColor(1);
  h1_charge_o13->Draw("SAME");

 
   
  c2->Write();

  TCanvas *c3 = new TCanvas("d","d",700,600);
  
  c3->Divide(4,0.,0.);
  
  c3->cd(1)->SetRightMargin(0.01);

  h1_charge_10->Draw();
  //h1_charge_210->Draw("SAME");
  h1_charge_10nM->SetLineColor(6);
  h1_charge_10nM->Draw("SAME");

  TLatex *t3 = new TLatex();
  t3->SetNDC();
  t3->SetTextAlign(13);
  t3->SetTextFont(63);
  t3->SetTextSizePixels(10);

  t3->DrawLatex(0.40,0.90,"#color[4]{with morror}");
  t3->DrawLatex(0.40,0.85,"#color[6]{mirror partially removed}");

  
  c3->cd(1)->SetGridy();

  c3->cd(2)->SetLeftMargin(0.001);
  c3->cd(2)->SetRightMargin(0.01);
  h1_charge_11->Draw();
  h1_charge_11nM->SetLineColor(6);
  h1_charge_11nM->Draw("SAME");
 
  c3->cd(2)->SetGridy();

  c3->cd(3)->SetLeftMargin(0.001);
  c3->cd(3)->SetRightMargin(0.01);
  h1_charge_12->Draw();
  h1_charge_12nM->SetLineColor(6);
  h1_charge_12nM->Draw("SAME");
 
  c3->cd(3)->SetGridy();
  
  c3->cd(4)->SetGridy();
  c3->cd(4)->SetLeftMargin(0.001);
  c3->cd(4)->SetRightMargin(0.01);
  h1_charge_13->Draw();
  h1_charge_13nM->SetLineColor(6);
  h1_charge_13nM->Draw("SAME");
  c1->cd(4)->SetGridy();

   
  c3->Write();
 


  TCanvas *c4 = new TCanvas("f","f",700,600);
  
 
  c4->Divide(4,2,0.,0.);
  c4->cd(1)->SetRightMargin(0.01);

  //  h1_charge_s10->SetLineColor(8);
  h1_charge_s10->Draw("SAME");
  
  c4->cd(1)->SetGridy();

  c4->cd(2)->SetLeftMargin(0.001);
  c4->cd(2)->SetRightMargin(0.01);
  //h1_charge_s11->SetLineColor(8);
  h1_charge_s11->Draw("SAME");
 
  c4->cd(2)->SetGridy();
  c4->cd(3)->SetLeftMargin(0.001);
  c4->cd(3)->SetRightMargin(0.01);
  // h1_charge_s12->SetLineColor(8);
  h1_charge_s12->Draw("SAME");
 
  c4->cd(3)->SetGridy();
  c4->cd(4)->SetLeftMargin(0.001);
  c4->cd(4)->SetRightMargin(0.01);
  //h1_charge_s13->SetLineColor(8);
  h1_charge_s13->Draw("SAME");

  c4->cd(4)->SetGridy();


  c4->cd(5)->SetRightMargin(0.01);
  //h1_cluster_s10->SetLineColor(8);
  h1_cluster_s10->Draw("SAME");

  c4->cd(6)->SetLeftMargin(0.001);
  c4->cd(6)->SetRightMargin(0.01);
  //h1_cluster_s11->SetLineColor(8);
  h1_cluster_s11->Draw("SAME");
  
  c4->cd(7)->SetLeftMargin(0.001);
  c4->cd(7)->SetRightMargin(0.01);
  //h1_cluster_s12->SetLineColor(8);
  h1_cluster_s12->Draw("SAME");

  c4->cd(8)->SetLeftMargin(0.001);
  c4->cd(8)->SetRightMargin(0.01);
  //h1_cluster_s13->SetLineColor(8);
  h1_cluster_s13->Draw("SAME");



  c4->Write();



  TCanvas *c5 = new TCanvas("g","g",700,600);
   
  c5->Divide(4,2,0.,0.);
  c5->cd(1)->SetRightMargin(0.01);
  h1_charge_10->Draw("SAME"); 
  //  h1_charge_s10->SetLineColor(8);
    c5->cd(1)->SetGridy();

  c5->cd(2)->SetLeftMargin(0.001);
  c5->cd(2)->SetRightMargin(0.01);
  //h1_charge_s11->SetLineColor(8);
  h1_charge_11->Draw("SAME");
 
  c5->cd(2)->SetGridy();
  c5->cd(3)->SetLeftMargin(0.001);
  c5->cd(3)->SetRightMargin(0.01);
  // h1_charge_s12->SetLineColor(8);
  h1_charge_12->Draw("SAME");
 
  c5->cd(3)->SetGridy();
  c5->cd(4)->SetLeftMargin(0.001);
  c5->cd(4)->SetRightMargin(0.01);
  //h1_charge_s13->SetLineColor(8);
  h1_charge_13->Draw("SAME"); 

  c5->cd(4)->SetGridy();
  c5->cd(5)->SetRightMargin(0.01);
  //h1_cluster_s10->SetLineColor(8);
  h1_cluster_10->Draw("SAME");

  c5->cd(6)->SetLeftMargin(0.001);
  c5->cd(6)->SetRightMargin(0.01);
  //h1_cluster_s11->SetLineColor(8);
  h1_cluster_11->Draw("SAME");
  
  c5->cd(7)->SetLeftMargin(0.001);
  c5->cd(7)->SetRightMargin(0.01);
  //h1_cluster_s12->SetLineColor(8);
  h1_cluster_12->Draw("SAME");

  c5->cd(8)->SetLeftMargin(0.001);
  c5->cd(8)->SetRightMargin(0.01);
  //h1_cluster_s13->SetLineColor(8);
  h1_cluster_13->Draw("SAME");

v
  c5->Write();

   
}
