//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		Event.h
//Description:	Contains hits & timing
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <boost/lexical_cast.hpp>
#include <sstream>

#include "Hit.h"

using namespace std;

class Event{
	public:
		//Constructors, destructors
		Event();
		Event(unsigned arg_lv1id);
		~Event(){};

		//Methods
		void addHit(Hit arg_hits);
		void addHit(unsigned bcid, unsigned col, unsigned row, unsigned tot);
		std::list<Hit>::iterator eraseHit(std::list<Hit>::iterator it);

		//Getters
		std::list<Hit>::iterator get_firstHit();
		std::list<Hit>::iterator get_endOfHits();
		int get_nHits();
		int get_lv1id();
		int get_chipID();
		int get_link();


		//******* Setters ********
		//TODO void setData(std::vector<double> newT, std::vector<double> newY);
		void set_lv1id(unsigned arg_lv1id);
		void set_chipID(unsigned arg_chipID);
		void set_link(unsigned arg_link);

	private:
		unsigned lv1id;
		unsigned chipID;
		unsigned link;
		std::list<Hit> hits;
		
};

typedef std::list<Event> EventContainer;
typedef std::map<unsigned,EventContainer*> EventMap;

#endif


