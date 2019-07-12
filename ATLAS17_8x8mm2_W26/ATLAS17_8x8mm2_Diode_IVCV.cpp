#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "ReadFile.hpp"
#include "rootlogonATLAS.h"

void ATLAS17_8x8mm2_Diode_IVCV()
{
  rootlogonATLAS();
  std::vector<string> filePaths{"ATLAS17_8x8mm2_diode_GR_Pad_common_1Vac_CV.txt","ATLAS17_8x8mm2_diode_GR_Pad_common_500mVac_CV.txt","ATLAS17_8x8mm2_diode_GR_Pad_common_IV.txt","ATLAS17_8x8mm2_diode_GR_Pad_diffground_IV.txt","ATLAS17_8x8mm2_diode_GR_Pad_float_IV.txt","ATLAS17_8x8mm2_diode_Pad_GR_diffground_1Vac_CV.txt","ATLAS17_8x8mm2_diode_Pad_GR_diffground_500mVac_CV.txt","ATLAS17_8x8mm2_diode_Pad_GR_diffground_IV.txt","ATLAS17_8x8mm2_diode_Pad_GR_float_1Vac_CV.txt","ATLAS17_8x8mm2_diode_Pad_GR_float_500mVac_CV.txt","ATLAS17_8x8mm2_diode_Pad_GR_float_IV.txt"};

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
  int iIV{1};
  int iCV{1};
  for(int i{0}; i<filePaths.size(); ++i)
    {
      Data data;
      std::string filePath{filePaths[i]};
      std::string fileName = filePath;
      fileName.erase(0,21);
      fileName.erase(fileName.size()-7,7);
      TString TfilePath = fileName;
      //      TString TfilePath{filePaths[i]};
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
	  if(iCV!=5)
	    {
	      g->SetMarkerColor(iCV);
	      g->SetLineColor(iCV);
	      glog->SetMarkerColor(iCV);
	      glog->SetLineColor(iCV);
	      ginverse->SetMarkerColor(iCV);
	      ginverse->SetLineColor(iCV);
	      ++iCV;
	    }
	  else if(iCV==5||iCV==10)
	    {
	      g->SetMarkerColor(iCV+1);
	      g->SetLineColor(iCV+1);
	      glog->SetMarkerColor(iCV+1);
	      glog->SetLineColor(iCV+1);	  
	      ginverse->SetMarkerColor(iCV+1);
	      ginverse->SetLineColor(iCV+1);
	      ++iCV;++iCV;
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
	  if(iIV!=5)
	    {
	      g->SetMarkerColor(iIV);
	      g->SetLineColor(iIV);
	      ++iIV;
	    }
	  else if(iIV==5)
	    {
	      g->SetMarkerColor(iIV+1);
	      g->SetLineColor(iIV+1);
	      ++iIV;++iIV;
	    }
	  IVmg->Add(g,"p");
	  IVleg->AddEntry(g,TfilePath,"lp");
	}
    }
  TCanvas *can = new TCanvas("ATLAS17_8x8mm2_Diode_IVCV_W26","ATLAS17_8x8mm2_Diode_IVCV_W26",600,600);
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
