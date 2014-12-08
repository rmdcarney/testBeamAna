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
		bool isAtEdge();

		//Getters
		Hits::iterator get_firstHit();
		Hits::iterator get_endOfHits();
		std::pair<double, double> get_centreOfCharge();
		unsigned get_size();
		unsigned get_totalToT();
		unsigned get_width();
		unsigned get_nDeltaRays();
		unsigned get_lv1id();
		unsigned get_length();

		//******* Setters ********
		//TODO void setData(std::vector<double> newT, std::vector<double> newY);
		void set_lv1id(unsigned arg_lv1id);

	private:
		//Vars
		unsigned size;
		unsigned width;
		unsigned tot;
		unsigned length;
		unsigned nDeltaRays;
		unsigned lv1id;
		bool totOverflow;
		bool atEdge;
		bool checkIsAtEdge;
		Hits hits;
		std::pair<double,double> centreOfCharge;

		//Methods
		void find_width();
		void find_length();
		void findToT();
		void findCentreOfCharge();

		//Vars
		void set_centreOfCharge(std::pair<unsigned,unsigned> arg_cOfc);
		void set_ToT(unsigned arg_tot);
		void set_length(unsigned length);
		void set_width(unsigned width);
};

typedef std::list<Cluster> ClusterContainer;
typedef std::map<unsigned,ClusterContainer*> ClusterMap;

#endif


