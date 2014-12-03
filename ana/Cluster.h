//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		Cluster.h
//Description:	Contains cluster info
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#ifndef CLUSTER_H
#define CLUSTER_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <sstream>

#include "Hit.h"

using namespace std;

class Cluster{
	public:
		//Constructors, destructors
		Cluster();
		~Cluster(){};

		//Methods
		void addHit(Hit arg_hits);
		void addHit(unsigned bcid, unsigned col, unsigned row, unsigned tot);
		void findToT();
		void findCentreOfCharge();

		//Getters
		std::list<Hit>::iterator get_firstHit();
		std::list<Hit>::iterator get_endOfHits();
		std::pair<double, double> get_centreOfCharge();
		unsigned get_size();
		unsigned get_totalToT();
		unsigned get_width();
		unsigned get_nDeltaRays();
		unsigned get_lv1id();
		
		//******* Setters ********
		//TODO void setData(std::vector<double> newT, std::vector<double> newY);
		void set_ToT(unsigned arg_lv1id);
		void set_width(unsigned arg_chipID);
		void set_lv1id(unsigned arg_lv1id);
		void set_centreOfChagrge(std::pair<unsigned,unsigned> arg_cOfc);

	private:
		unsigned size;
		unsigned width;
		unsigned tot;
		unsigned nDeltaRays;
		unsigned lv1id;
		bool totOverflow;
		std::list<Hit> hits;
		std::pair<double,double> centreOfCharge; 
		
};

typedef std::list<Cluster> ClusterContainer;
typedef std::map<unsigned,ClusterContainer*> ClusterMap;

#endif


