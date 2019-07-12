#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "ReadFile.hpp"

void ATLAS12_Diode_IV()
{
  std::string filePrefix = "ATLAS12_diode_";
  std::vector<string> fileDiff = {"GR_float","Pad_float","PadGR_common"};
  std::string fileSuffix = "_IV.txt";

  TMultiGraph *mg = new TMultiGraph();
  mg->GetXaxis()->SetTitle("Bias [V]");
  mg->GetYaxis()->SetTitle("Current [A]");

  TLegend *legend = new TLegend(0.2,0.75,0.3,0.85);
  
  for(int i{0}; i<fileDiff.size(); ++i)
    {
      std::string filePath = filePrefix+fileDiff[i]+fileSuffix;
      TString TlegName = filePrefix+fileDiff[i];
      Data data = ReadFile(filePath);

      TGraphErrors *g = new TGraphErrors(data.voltage.size(), &(data.voltage[0]), &(data.current[0]), &(data.evoltage[0]), &(data.ecurrent[0]));
      g->SetMarkerColor(i+1);
      g->SetLineColor(i+1);
      g->SetMarkerStyle(20);
      mg->Add(g,"p");
      legend->AddEntry(g,TlegName,"lp");
      // std::cout<<"====================================================================="<<std::endl;
      // for(int n{0}; n<data.voltage.size(); ++n)
      // 	{
      // 	  std::cout<<data.voltage[n]<<" +/- "<<data.evoltage[n]<<"\t"<<data.current[n]<<" +/- "<<data.ecurrent[n]<<std::endl;
      // 	}
      // std::cout<<"====================================================================="<<std::endl;
    }

  TCanvas *canvas = new TCanvas("canvas","canvas",600,600);
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->SetTextSize(0.03);
  legend->SetFillStyle(1000);
  legend->SetTextFont(42);
  legend->SetNColumns(1);
  canvas->SetLeftMargin(0.15);
  mg->Draw("AP");
  legend->Draw("same");
  canvas->SaveAs("ATLAS12_8x8mm2_IV.pdf");
}
