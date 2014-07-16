//this should just plot the phistar changing plot

#include <stdio.h>
#include <iostream>
#include <string>
#include <TFile.h>
#include <TH1.h>
#include "TROOT.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"

int plotPhistar()
{
	gROOT->SetStyle("Plain");	
	gStyle->SetErrorX(0);
	gStyle->SetOptStat(0);
	
	TCanvas* c1 = new TCanvas("C1", "c1", 1200, 900);
	c1->cd();
	c1->SetFillColor(10);
	TLegend *l1 = new TLegend(0.6,0.8,0.9,0.9);
	l1->SetFillColor(10);
	
	//root has been stupid about Draw("same") lately. I am going to try to fool it:
	TH1D *dummy1 = new TH1D("dummy1","",1,0,1);
	TH1D *dummy2 = new TH1D("dummy2","",1,0,1);
	dummy1->Draw();
	dummy2->Draw("same");
	c1->Print("dummmy.png");
	c1->Clear();
	
	
	TFile *f1 = new TFile("file:/local/cms/user/finkel/ZFinder/zfinder_extended_mc/zfinder_extended_mc_merged.root");
	TH1D *temp = (TH1D*)f1->Get("ZFinder/ET-NT Rapidity MC/3 eg_medium AND nt_loose/#phi*");
	TH1D *phiStar = (TH1D*)temp->Rebin(40,"phiStar");
	temp = (TH1D*)f1->Get("ZFinder/ET-NT Rapidity MC/3 eg_medium AND nt_loose/#correctedPhi*");
	TH1D *correctedPhiStar = (TH1D*)temp->Rebin(40,"correctedPhiStar");
	
	phiStar->SetTitle("#phi*;#phi*;Events/bin");
	phiStar->SetLineWidth(4);
	phiStar->SetLineColor(kBlue+2);
	phiStar->Draw("hist");
	
	correctedPhiStar->SetLineWidth(4);
	correctedPhiStar->SetLineColor(kRed+1);
	correctedPhiStar->Draw("same hist");
	
	l1->AddEntry(phiStar,"Reco #phi*","l");
	l1->AddEntry(correctedPhiStar,"Corrected #phi*","l");
	l1->Draw("same");
	
	c1->Print("phiStarShift.png");
	gPad->SetLogy();
	c1->Print("logPhiStarShift.png");
	c1->Close();
	
	return 0;
}
