//this should just plot the phistar changing plot

#include <stdio.h>
#include <iostream>
#include <string>
#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include "TROOT.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"


int plotPhi()
{
	gROOT->SetStyle("Plain");	
	gStyle->SetErrorX(0);
	gStyle->SetOptStat(0);
	
	TCanvas* c1 = new TCanvas("C1", "c1", 1200, 900);
	c1->cd();
	c1->SetFillColor(10);
	TLegend *l1 = new TLegend(0.6,0.6,0.9,0.9);
	l1->SetFillColor(10);
	
	TF1 *fit = new TF1("fit","gaus(0)+gaus(3)",-0.05,0.05);
	fit->SetLineWidth(3);
	
	char line[256];
	
	//root has been stupid about Draw("same") lately. I am going to try to fool it:
	TH1D *dummy1 = new TH1D("dummy1","",1,0,1);
	TH1D *dummy2 = new TH1D("dummy2","",1,0,1);
	dummy1->Draw();
	dummy2->Draw("same");
	c1->Print("dummmy.png");
	c1->Clear();
	
	
	TFile *f1 = new TFile("file:/local/cms/user/finkel/ZFinder/NTphiCorrection/naive/zfinder_extended_mc_merged.root");
	TH1D *deltaPhi1 = (TH1D*)f1->Get("ZFinder/ET-NT Rapidity MC/3 eg_medium AND nt_loose/deltaPhi1");
	TFile *f2 = new TFile("file:/local/cms/user/finkel/ZFinder/NTphiCorrection/analytic/zfinder_extended_mc_merged.root");
	TH1D *CorrDeltaPhi1 = (TH1D*)f2->Get("ZFinder/ET-NT Rapidity MC/3 eg_medium AND nt_loose/deltaPhi1");
	
	CorrDeltaPhi1->SetTitle("NT Electron #phi_{gen}-#phi_{reco};#delta#phi;Events/bin");
	CorrDeltaPhi1->SetLineWidth(2);
	CorrDeltaPhi1->SetLineColor(kBlue+2);
	CorrDeltaPhi1->GetYaxis()->SetRangeUser(0.1,1e3);
	CorrDeltaPhi1->Draw("hist");
	
	deltaPhi1->SetLineWidth(2);
	deltaPhi1->SetLineColor(kRed+1);
	deltaPhi1->Draw("same hist");
	
	fit->SetParameter(0,1e3);
	fit->SetParameter(1,1e-2);
	fit->SetParameter(2,1e-3);
	//fit->SetParLimits(2,1e-3,3e-3);
	fit->SetParameter(3,0);
	fit->SetParameter(4,1e-2);
	fit->SetParameter(5,10);
	fit->SetParLimits(5,0,1e-2);
	deltaPhi1->Fit(fit,"MN","",0.002,0.02);
	fit->SetLineColor(kRed+1);
	fit->DrawClone("same");
	sprintf(line, "No Correction: #sigma_{core}=%f",min( fit->GetParameter(2),fit->GetParameter(5) ));	
	l1->AddEntry(deltaPhi1,line,"l");

	fit->SetParameter(0,1e3);
	fit->SetParameter(1,0);
	fit->SetParameter(2,0.00142);
	fit->SetParLimits(2,5e-4,3e-3);
	fit->SetParameter(3,0);
	fit->SetParameter(4,0);
	fit->SetParameter(5,0.01);
	fit->SetParLimits(5,0,3e-2);
	CorrDeltaPhi1->Fit(fit,"MN","",-0.015,0.008);
	fit->SetLineColor(kBlue+2);
	fit->DrawClone("same");
	sprintf(line, "Analytic Correction: #sigma_{core}=%f",std::min( fit->GetParameter(2),fit->GetParameter(5) ));	
	l1->AddEntry(CorrDeltaPhi1,line,"l");

	l1->Draw("same");
	
	c1->Print("NTdeltaPhi.png");
	
	c1->Close();
	f1->Close();
	f2->Close();
	
	return 0;
}
