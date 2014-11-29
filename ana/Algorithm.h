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

	void findClusters_iterative(ClusterMap* clusters, EventMap events);
	int sgn(int val, int limit);
	void resetBcidLimits(int bcid, int* bcidHigh, int* bcidLow, bool* bcidSet);
	void resetRowLimits(int row, int* rowHigh, int* rowLow); 
	void resetColLimits(int col, int* colHigh, int* colLow); 
}

#endif

