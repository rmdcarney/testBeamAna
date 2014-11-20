//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		EventContainer.cpp
//Description:	Contains hits & timing
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <EventContainer.h>
#define DEBUG 1

EventContainer::EventContainer() {
	lv1id=0;
	chipID=0;
	link=0;
}

EventContainer::EventContainer(int arg_lv1id, int arg_chipID, int arg_link){
	lv1id = arg_lv1id;
	chipID = arg_chipID;
	link = arg_link;
}


void EventContainer::addHit(HitContainer arg_hit){
	hits.push_back(&arg_hit);
}

void EventContainer::addHit(int bcid, int col, int row, int tot){
	hits.push_back(new HitContainer(bcid, col, row, tot));
}

//Getters

std::vector<HitContainer*> EventContainer::getHits(){
	return hits;
}


int EventContainer::get_nHits(){
	return hits.size();
}

int EventContainer::get_lv1id(){
	return lv1id;
}

int EventContainer::get_link(){
	return link;
}

int EventContainer::get_chipID(){
	return chipID;
}


//Setters

void EventContainer::setData(std::vector<HitContainer*> newHits){
	hits = newHits;
}

void EventContainer::set_lv1id(int arg_lv1id){
	lv1id = arg_lv1id;
}

void EventContainer::set_chipID(int arg_chipID){
	chipID = arg_chipID;
}

void EventContainer::set_link(int arg_link){
	link = arg_link;
}


