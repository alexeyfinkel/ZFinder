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
	TLegend *l1 = new TLegend(0.6,0.7,0.9,0.9);
	l1->SetFillColor(10);
	
	//root has been stupid about Draw("same") lately. I am going to try to fool it:
	TH1D *dummy1 = new TH1D("dummy1","",1,0,1);
	TH1D *dummy2 = new TH1D("dummy2","",1,0,1);
	dummy1->Draw();
	dummy2->Draw("same");
	c1->Print("dummmy.png");
	c1->Clear();
	
	
	TFile *f1 = new TFile("file:/local/cms/user/finkel/ZFinder/NTphiCorrection/analytic/zfinder_extended_mc_merged.root");
	TH1D *temp = (TH1D*)f1->Get("ZFinder/ET-NT Rapidity MC/3 eg_medium AND nt_loose/#phi*");
	TH1D *phiStarTruth = (TH1D*)temp->Rebin(40,"phiStarTruth");
	temp = (TH1D*)f1->Get("ZFinder/ET-NT Rapidity MC/3 eg_medium AND nt_loose/#correctedPhi*");
	TH1D *correctedPhiStar = (TH1D*)temp->Rebin(40,"correctedPhiStar");
	temp = (TH1D*)f1->Get("ZFinder/ET-NT Rapidity Reco/3 eg_medium AND nt_loose/#phi*");
	TH1D *phiStarReco = (TH1D*)temp->Rebin(40,"phiStarReco");
	
	phiStarTruth->SetTitle("#phi*;#phi*;Events/bin");
	phiStarTruth->SetLineWidth(4);
	phiStarTruth->SetLineColor(kRed+1);
	phiStarTruth->GetYaxis()->SetRangeUser(0.1,4e3);
	phiStarTruth->GetXaxis()->SetRangeUser(1e-2,3);
	phiStarTruth->Draw("hist");
	
	phiStarReco->SetLineWidth(4);
	phiStarReco->SetLineColor(kGreen+2);
	phiStarReco->Draw("same hist");
	
	correctedPhiStar->SetLineWidth(4);
	correctedPhiStar->SetLineColor(kBlue+1);
	correctedPhiStar->Draw("same hist");
	
	l1->AddEntry(phiStarTruth,"Truth #phi*","l");
	l1->AddEntry(phiStarReco,"Reco #phi*","l");
	l1->AddEntry(correctedPhiStar,"Corrected reco #phi*","l");
	l1->Draw("same");
	
	c1->Print("phiStarShift.png");
	gPad->SetLogy();
	gPad->SetLogx();
	phiStarTruth->GetYaxis()->SetRangeUser(0.1,1e4);
	c1->Print("logPhiStarShift.png");
	c1->Close();
	
	return 0;
}
