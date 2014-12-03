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
#define DEBUG 0

Cluster::Cluster() {
	size=0;
	width=0;
	tot=0;
	nDeltaRays=0;
	lv1id=0;
	totOverflow = false;
	centreOfCharge.first = -1;
	centreOfCharge.second = -1;
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
	if(!hits.empty() && hits.size()>1){
		for(i=hits.begin(); i!=hits.end(); ++i){
			if(i->get_tot()<14){
				tot += i->get_tot();
			} else {
				tot = 0;
				totOverflow = true;
				break;
			}
		}
	}
}

void Cluster::findCentreOfCharge(){

	//Find mean position relative to cluster length
	std::list<Hit>::iterator i;
	centreOfCharge.first = -1;
	centreOfCharge.second = -1;
	unsigned sumx(0),sumy(0), toti(0);
	unsigned bigx(0), smallx(1e5), bigy(0), smally(1e5);
	double pcx(0.), pcy(0.);
	unsigned row(0), col(0);
	double range(0.), diffMean(0.);

	//Check that the cluster tot has been calculated, if not, 
	//calculate it
	//Overflow, cannot calculate centre of charge
	if(totOverflow == true)
			return;
	//Not yet been calculated
	else if(tot == 0)
		findToT();

	//If it still can't calculate tot, quit
	if(tot ==0)
		return;
	
	//Iterate over hits
	if(!hits.empty() && hits.size()>1){
		for(i = hits.begin(); i!=hits.end(); ++i){
			row = i->get_row();
			col = i->get_col();
			//Find the biggest and smallest
			if(row > bigy)
				bigy = row;
			if(row < smally)
				smally = row;
			if(col > bigx)
				bigx = col;
			if(col < smallx)
				smallx = col;

			toti = i->get_tot();
			sumx += (col*toti);
			sumy += (row*toti);
		}
	}

	//Now we want the percentage
	pcx = (double)sumx;
	pcx /= ((double)tot);
	
	range = bigx - smallx +1;
	diffMean = pcx - smallx +1;
	pcx = diffMean/range;

	pcy = (double)sumy;
	pcy /= ((double)tot);
	
	range = bigy - smally +1;
	diffMean = pcy - smally +1;
	pcy = diffMean/range;
	
	centreOfCharge.first = (pcx*100.);
	centreOfCharge.second = (pcy*100.);
}


//Getters

std::list<Hit>::iterator Cluster::get_firstHit(){
	return hits.begin();
}

std::list<Hit>::iterator Cluster::get_endOfHits(){
	return hits.end();
}

unsigned Cluster::get_lv1id(){
	return lv1id;
}

unsigned Cluster::get_size(){
	return hits.size();
}

unsigned Cluster::get_width(){
//TODO
	return width;
}

unsigned Cluster::get_totalToT(){
	if(tot == 0 && totOverflow == false)
		findToT();
	return tot;
}

unsigned Cluster::get_nDeltaRays(){
	return nDeltaRays;
}

std::pair<double,double> Cluster::get_centreOfCharge(){
	if(centreOfCharge.first == -1 && centreOfCharge.second == -1 && totOverflow == false)
		findCentreOfCharge();
	return centreOfCharge;
}


//Setters

void Cluster::set_ToT(unsigned arg_tot){
	tot = arg_tot;
}

void Cluster::set_lv1id(unsigned arg_lv1id){
	lv1id = arg_lv1id;
}

