//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		Cluster.cpp
//Description:	Contain cluster info
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <Cluster.h>
#define DEBUG 1

Cluster::Cluster() {
	size=0;
	width=0;
	tot=0;
	nDeltaRays=0;
	//Hit container - ready!
	Hits hits;
}

void Cluster::addHit(Hit arg_hit){
	hits.push_back(arg_hit);
}

void Cluster::addHit(unsigned bcid, unsigned col, unsigned row, unsigned tot){
	hits.push_back(Hit(bcid, col, row, tot));
}

void Cluster::findToT(){
	std::list<Hit>::iterator i;
	tot = 0;
	for(i=hits.begin(); i!=hits.end(); ++i)
		tot += i->get_tot();
}

//Getters

std::list<Hit>::iterator Cluster::get_firstHit(){
	return hits.begin();
}

std::list<Hit>::iterator Cluster::get_lastHit(){
	return hits.end();
}


unsigned Cluster::get_size(){
	return hits.size();
}

unsigned Cluster::get_width(){
//TODO
	return width;
}

unsigned Cluster::get_totalToT(){
	return tot;
}

unsigned Cluster::get_nDeltaRays(){
	return nDeltaRays;
}

//Setters

void Cluster::set_ToT(unsigned arg_tot){
	tot = arg_tot;
}

