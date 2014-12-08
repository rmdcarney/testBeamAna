//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		Algorithm.h
//Description:	Clustering stuff
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <sstream>

#include "Event.h"
#include "Cluster.h"


using namespace std;

namespace Algorithm{

	//Clustering algorithm
	void findClusters_iterative(ClusterMap* clusters, EventMap events);
	void maskedPixel_clustering(ClusterMap* clusters, std::vector<std::pair<int, int> > maskedPixels);

	//***** Boundary and limits *******
	//Comparator function for boundaries
	int sgn(int val, int limit);
	//Limit changinf functions
	void resetBcidLimits(int bcid, int* bcidHigh, int* bcidLow, bool* bcidSet);
	void resetRowLimits(int row, int* rowHigh, int* rowLow); 
	void resetColLimits(int col, int* colHigh, int* colLow);
	//Within boundaries
	void checkHitFitsBoundaryConditions(int* colHigh, int* colLow, int* rowHigh, int* rowLow, int* bcidHigh, int* bcidLow, bool* bcidSet, int col, int row, int bcid, int tot, EventContainer::iterator* i, Hits::iterator* k, ClusterMap::iterator* cit);
	


}

#endif

