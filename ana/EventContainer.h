//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		EventContainer.h
//Description:	Contains hits & timing
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#ifndef EVENTCONTAINER_H
#define EVENTCONTAINER_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <sstream>

#include "HitContainer.h"

using namespace std;

class EventContainer{
	public:
		//Constructors, destructors
		EventContainer();
		EventContainer(int arg_lv1id, int arg_chipID, int arg_link);
		~EventContainer(){};

		//Methods
		void addHit(HitContainer arg_hits);
		void addHit(int bcid, int col, int row, int tot);

		//Getters
		vector<HitContainer*> getHits();
		int get_nHits();
		int get_lv1id();
		int get_chipID();
		int get_link();


		//******* Setters ********
		//TODO void setData(std::vector<double> newT, std::vector<double> newY);
		void set_lv1id(int arg_lv1id);
		void set_chipID(int arg_chipID);
		void set_link(int arg_link);
		void setData(std::vector<HitContainer*> newHits);

	private:
		int lv1id;
		int chipID;
		int link;
		std::vector<HitContainer*> hits;
		
};


#endif


