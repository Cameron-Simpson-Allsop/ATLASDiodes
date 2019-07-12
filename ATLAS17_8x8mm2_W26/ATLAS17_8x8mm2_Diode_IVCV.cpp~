#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "ReadFile.hpp"
#include "rootlogonATLAS.h"

void ATLAS17_Diode_IVCV()
{
  rootlogonATLAS();
  std::vector<string> filePaths{"ATLAS17_diode_GR_float_CV_1Vac.txt","ATLAS17_diode_GR_float_CV_500mVac.txt","ATLAS17_diode_GR_float_IV.txt","ATLAS17_diode_Pad_Float_IV.txt","ATLAS17_diode_PadGR_common_CV_1Vac.txt","ATLAS17_diode_PadGR_common_CV_500mVac.txt","ATLAS17_diode_PadGR_common_IV.txt"};

  TMultiGraph *IVmg = new TMultiGraph();
  TMultiGraph *CVmg = new TMultiGraph();
  TMultiGraph *CVmglog = new TMultiGraph();
  TMultiGraph *CVmginverse = new TMultiGraph();
  IVmg->GetYaxis()->SetTitle("Current [A]");
  IVmg->GetXaxis()->SetTitle("Bias [V]");
  CVmg->GetYaxis()->SetTitle("Capacitance [F]");
  CVmg->GetXaxis()->SetTitle("Bias [V]");
  CVmglog->GetYaxis()->SetTitle("log Capacitance [ln(F)]");
  CVmglog->GetXaxis()->SetTitle("log Bias [ln(V)]");
  CVmginverse->GetYaxis()->SetTitle("1/Capacitance^{2} [1/F^{2}]");
  CVmginverse->GetXaxis()->SetTitle("Bias [V]");

  TLegend *IVleg = new TLegend(0.15,0.7,0.5,0.9);
  TLegend *CVleg = new TLegend(0.15,0.7,0.5,0.9);
  TLegend *CVleglog = new TLegend(0.15,0.2,0.5,0.5);
  TLegend *CVleginverse = new TLegend(0.15,0.2,0.5,0.5);
  
  for(int i{0}; i<filePaths.size(); ++i)
    {
      Data data;
      std::string filePath{filePaths[i]};
      TString TfilePath{filePaths[i]};
      data = ReadFile(filePath);
      std::size_t CV = filePath.find("CV");
      std::size_t IV = filePath.find("IV");
      if(CV != std::string::npos && IV == std::string::npos)
	{
	  TGraphErrors *g = new TGraphErrors(data.voltage.size(),&(data.voltage[0]),&(data.capacitance[0]),&(data.evoltage[0]),&(data.ecapacitance[0]));
	  TGraphErrors *glog = new TGraphErrors(data.logvoltage.size(),&(data.logvoltage[0]),&(data.logcapacitance[0]),&(data.elogvoltage[0]),&(data.elogcapacitance[0]));
	  TGraphErrors *ginverse = new TGraphErrors(data.voltage.size(),&(data.voltage[0]),&(data.inversecapacitance2[0]),&(data.evoltage[0]),&(data.einversecapacitance2[0]));
	  g->SetMarkerStyle(20);
	  g->SetMarkerSize(0.7);
	  glog->SetMarkerStyle(20);
	  glog->SetMarkerSize(0.7);
	  ginverse->SetMarkerStyle(20);
	  ginverse->SetMarkerSize(0.7);
	  if(i!=4)
	    {
	  g->SetMarkerColor(i+1);
	  g->SetLineColor(i+1);
	  glog->SetMarkerColor(i+1);
	  glog->SetLineColor(i+1);
	  ginverse->SetMarkerColor(i+1);
	  ginverse->SetLineColor(i+1);
	    }
	  else if(i==4)
	    {
	  g->SetMarkerColor(9);
	  g->SetLineColor(9);
	  glog->SetMarkerColor(9);
	  glog->SetLineColor(9);	  
	  ginverse->SetMarkerColor(9);
	  ginverse->SetLineColor(9);
	    }
	  CVmg->Add(g,"p");
	  CVmglog->Add(glog,"p");
	  CVleg->AddEntry(g,TfilePath,"lp");
	  CVleglog->AddEntry(glog,TfilePath,"lp");
	  CVmginverse->Add(ginverse,"p");
	  CVleginverse->AddEntry(ginverse,TfilePath,"lp");
	}
      if(CV == std::string::npos && IV != std::string::npos)
	{
	  TGraphErrors *g = new TGraphErrors(data.voltage.size(),&(data.voltage[0]),&(data.current[0]),&(data.evoltage[0]),&(data.ecurrent[0]));
	  g->SetMarkerStyle(20);
	  g->SetMarkerSize(0.7);
	  if(i!=5)
	    {
	  g->SetMarkerColor(i+1);
	  g->SetLineColor(i+1);
	    }
	  else if(i==5)
	    {
	  g->SetMarkerColor(9);
	  g->SetLineColor(9);
	    }
	  IVmg->Add(g,"p");
	  IVleg->AddEntry(g,TfilePath,"lp");
	}
    }
  TCanvas *can = new TCanvas("IV","IV",600,600);
  TGaxis::SetMaxDigits(2);
  can->Divide(2,2);
  can->cd(1);
  IVmg->Draw("AP");
  IVleg->SetBorderSize(0);
  IVleg->SetFillColor(0);
  IVleg->SetTextSize(0.04);
  IVleg->SetFillStyle(1000);
  IVleg->SetTextFont(42);
  IVleg->SetNColumns(1);
  IVleg->Draw("same");
  can->cd(2);
  CVmg->Draw("AP");
  CVleg->SetBorderSize(0);
  CVleg->SetFillColor(0);
  CVleg->SetTextSize(0.04);
  CVleg->SetFillStyle(1000);
  CVleg->SetTextFont(42);
  CVleg->SetNColumns(1);
  CVleg->Draw("same");
  can->cd(3);
  CVmglog->Draw("AP");
  CVleglog->SetBorderSize(0);
  CVleglog->SetFillColor(0);
  CVleglog->SetTextSize(0.04);
  CVleglog->SetFillStyle(1000);
  CVleglog->SetTextFont(42);
  CVleglog->SetNColumns(1);
  CVleglog->Draw("same");
  can->cd(4);
  CVmginverse->Draw("AP");
  CVleginverse->SetBorderSize(0);
  CVleginverse->SetFillColor(0);
  CVleginverse->SetTextSize(0.04);
  CVleginverse->SetFillStyle(1000);
  CVleginverse->SetTextFont(42);
  CVleginverse->SetNColumns(1);
  CVleginverse->Draw("same");
  //can->SaveAs("ATLAS_diode_IV_CV.pdf");
}
