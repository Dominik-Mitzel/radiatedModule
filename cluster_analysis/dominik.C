#include <TList.h>
#include <TPad.h>
#include <TFile.h>
#include <THStack.h>
#include <TKey.h>
#include <TROOT.h>
#include <TCanvas.h>

#include <iostream>
//#include <T.h>
//#include <T.h>

TList* extractObjectFromPad(TPad* pad, const char* name)
{
  TList* objects = new TList();
  TList* primitivesList = pad->GetListOfPrimitives();
  assert(primitivesList);
  for (int i = 0; i < primitivesList->GetSize(); ++i) {
    TObject* object = primitivesList->At(i);
    std::cout << object->ClassName() << ' ' << object->GetName() << std::endl;
    if (object->InheritsFrom("TPad")) {
      TList* objectsFromPad = extractObjectFromPad(static_cast<TPad*>(object), name);
      for (int j = 0; j < objectsFromPad->GetSize(); ++j)
        objects->Add(objectsFromPad->At(j));
    } else if (object->InheritsFrom("THStack")) {
      TList* hList = (static_cast<THStack*>(object))->GetHists();
      for (int j = 0; j < hList->GetSize(); ++j)
        if (!strcmp(hList->At(j)->GetName(), name)) {
          objects->Add(hList->At(j));
        }
    } else if (!strcmp(object->GetName(), name)) {
      std::cout << "--->" << name << std::endl;
      objects->Add(object);
    }
  }
  return objects;
}

TList* extractObjectFromFile(const char* fileName, const char* name)
{
  TList* objects = new TList();
  TFile file(fileName);
  gROOT->cd();
  TList* keyList = file.GetListOfKeys();
  for (int i = 0; i < keyList->GetSize(); ++i) {
    TKey* key = static_cast<TKey*>(keyList->At(i));
    std::cout<< key->GetName()<< std::endl;
    if (!strcmp(key->GetName(), name)) {
      objects->Add(key->ReadObj()->Clone());
    } else if (!strcmp(key->GetClassName(), "TCanvas")) {
      TCanvas* canvas = static_cast<TCanvas*>(key->ReadObj());
      if (!strcmp(canvas->GetName(), name))
        objects->Add(canvas->Clone());
      TList* objectsFromPad = extractObjectFromPad(canvas, name);
      for (int j = 0; j < objectsFromPad->GetSize(); ++j)
        objects->Add(objectsFromPad->At(j));
    }
  }
  file.Close();
  return objects;
}

void dominik()
{
  TH1* matHistogramRoman = static_cast<TH1*>(extractObjectFromFile("lyRoman.root", "lightYieldProjectionY")->At(0));
  TList* objects = extractObjectFromFile("c.root", "chargeBins");
  TH1* matHistogramDominik = new TH1D("matHistogramDominik", ";channel;light yield / pixels", 512, -0.5, 512-0.5);
  int sipmIt = 0;
  for (int i = 0; i < objects->GetSize(); ++i) {
    TH1* h = static_cast<TH1*>(objects->At(i));
    if (h->GetLineColor() == 8) {
      for (int bin = 1; bin <= 128; ++bin) {
        matHistogramDominik->SetBinContent(512 - (sipmIt * 128 + bin - 1), h->GetBinContent(bin));
        if (h->GetBinError(bin) > 0)
          matHistogramDominik->SetBinError(512 - (sipmIt * 128 + bin - 1), h->GetBinError(bin));
      }
      ++sipmIt;
    }
  }
  TCanvas* c = new TCanvas;
  c->Divide(1, 2);
  c->cd(1);
  matHistogramDominik->Draw();
  matHistogramRoman->Draw("SAME");
  c->cd(2);
  TH1* h = static_cast<TH1*>(matHistogramDominik->Clone());
  h->Add(matHistogramRoman, -1);
  h->Draw();
}
