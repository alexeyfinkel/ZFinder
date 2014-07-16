//this should be a very basic script that adds phiStar and delta phi hists from a bunch of MC files and compares reco to reco-but-gen-NT to see the effects of bending etc. in the high-eta region

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <TFile.h>
#include <TH1.h>
#include "TROOT.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"


int deltaPhiStar()
{
	gROOT->SetStyle("Plain");	
	gStyle->SetErrorX(0);
	gStyle->SetOptStat(0);
	
	TCanvas* c1 = new TCanvas("C1", "c1", 1200, 900);
	c1->cd();
	
	TH1D *phiStar = new TH1D("phiStar","#phi*",50, 0, 1);
	TH1D *correctedPhiStar = new TH1D("correctedPhiStar","Corrected #phi*",50, 0, 1);
	TH1D *deltaPhi = new TH1D("deltaPhi","#phi_{1,reco}-#phi_{1,gen} (signed)",50, 0, 1);
	TH1D *temp;
	
	//TFile *file =new TFile();
	
	const int nFiles = 40;
	char fileName[256];
	
	for(int i=0;i<nFiles;i++)
	{
		sprintf(fileName, "file:/local/cms/user/finkel/ZFinder/zfinder_extended_mc/zfinder_extended_mc_%.3d.root", i);
		TFile *file = new TFile(fileName);
		if( file->IsZombie() )
		{
			std::cout<<"File number "<<i<<" is missing!"<<std::endl;
			continue;			
		}
		//std::cout<<"Ping "<<i<<"!"<<std::endl;
		temp = (TH1D*)file->Get("ZFinder/ET-NT Rapidity MC/3 eg_medium AND nt_loose/deltaPhi1");
		deltaPhi->Add(temp);
		temp = (TH1D*)file->Get("ZFinder/ET-NT Rapidity MC/3 eg_medium AND nt_loose/#phi*");
		phiStar->Add(temp);
		temp = (TH1D*)file->Get("ZFinder/ET-NT Rapidity MC/3 eg_medium AND nt_loose/#correctedPhi*");
		correctedPhiStar->Add(temp);
		
	}

	c1->Close();
	return 0;
}

//***This script is no longer needed, since hadd can be told to ignore roodatasets!***//










