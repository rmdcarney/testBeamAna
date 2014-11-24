//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		Event.cpp
//Description:	Contains hits & timing
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <Event.h>
#define DEBUG 1

Event::Event() {
	lv1id=0;
	//Hit container - ready!
	Hits hits;
}

Event::Event(unsigned arg_lv1id){
	lv1id = arg_lv1id;
	//Hit container - ready!
	Hits hits;
}


void Event::addHit(Hit arg_hit){
	hits.push_back(arg_hit);
}

void Event::addHit(unsigned bcid, unsigned col, unsigned row, unsigned tot){
	hits.push_back(Hit(bcid, col, row, tot));
}

//Getters

std::list<Hit>::iterator Event::get_firstHit(){
	return hits.begin();
}

std::list<Hit>::iterator Event::get_lastHit(){
	return hits.end();
}


int Event::get_nHits(){
	return hits.size();
}

int Event::get_lv1id(){
	return lv1id;
}

int Event::get_link(){
	return link;
}

int Event::get_chipID(){
	return chipID;
}


//Setters

void Event::set_lv1id(unsigned arg_lv1id){
	lv1id = arg_lv1id;
}

void Event::set_chipID(unsigned arg_chipID){
	chipID = arg_chipID;
}

void Event::set_link(unsigned arg_link){
	link = arg_link;
}


