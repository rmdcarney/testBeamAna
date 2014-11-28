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

	void findClusters(ClusterContainer* clusters, EventMap events);
	int sgn(int val, int limit);
	void resetBcidLimits(int bcid, int* bcidHigh, int* bcidLow, bool* bcidSet);
	void resetXYLimits(int colOrRow, int* colOrRowHigh, int* colOrRowLow, char cOrr); 
}

#endif

