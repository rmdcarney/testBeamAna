//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		Plot.h
//Description:  Plotting stuff
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#ifndef PLOT_H
#define PLOT_H

//std lib 
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <sstream>

//User-defined
#include "Event.h"
#include "Cluster.h"

//ROOT
#include "TH1F.h"
#include "TH2F.h"
#include "TAxis.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"

using namespace std;

namespace Plot{
	
//*** M E T H O D S *****
	//1D hists
	TH1F* clusterSize(ClusterContainer* myClusters);
	TH1F* clusterToT(ClusterContainer* myClusters);
	TH1F* deltaRays(ClusterContainer* myClusters);
	TH1D* centreOfCharge(ClusterContainer* myClusters);

	//2D hists
	std::map<unsigned,TH2F*> eventClusters(ClusterContainer* myClusters);
	TH2F* cumulativeOccupancy(std::list<Cluster*> allClusters);
	TH2F* eventMasked(Event* myEvent, std::list<std::pair<int,int> > maskedPixels);
	
	//Misc
	void print(TH1F* myTH1F, std::string path);
	void print(TH2F* myTH2F, std::string path);



}

#endif

