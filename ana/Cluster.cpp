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
#define nCols 80
#define nRows 336
#define minCol 0
#define minRow 0

Cluster::Cluster() {
	//Attributes
	lv1id=0;
	//TODO
	nDeltaRays=0;

	//Flags
	totOverflow = false;
	atEdge = false;
	checkIsAtEdge = false;

	//Calculated
	size=0;
	width=0;
	length=0;
	tot=0;
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


//******* finders - calculate properties of the cluster ********

//Compare functions for sortin hit list
bool compare_cols(const Hit& lhs, const Hit& rhs){
	
	if(lhs.get_col() > rhs.get_col())
		return false;
	else{
		return true;
	}
}

bool compare_rows(const Hit& lhs, const Hit& rhs){
	
	if(lhs.get_row() > rhs.get_row())
		return false;
	else{
		return true;
	}
}

//Find the width of cluster in units of pixels in a column
void Cluster::find_width(){

	//Sort by col
	hits.sort(compare_cols);

	//Then take the difference of the first and last values
	set_width(hits.back().get_col() - hits.front().get_col() + 1);
}

//Find length of a cluster in units of pixels in a row
void Cluster::find_length(){

	//Sort by row
	hits.sort(compare_rows);
	
	//Then take the difference of the first and last values
	set_length(hits.back().get_row() - hits.front().get_row() + 1);
}

//Tot of whole cluster: sum
void Cluster::findToT(){
	
	Hits::iterator i;
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

//Mean tot in cluster position
void Cluster::findCentreOfCharge(){

	//Find mean position relative to cluster length
	Hits::iterator i;
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

//Checks to see if the cluster is at the edge of the chip
bool Cluster::isAtEdge(){

	Hits::iterator it;
	//Check that the cluster has hits and 
	//that the is at edge has been checked already
	if(hits.size() == 0)
		std::cout<<"ERROR - tried to check if empty cluster is at edge! Fill cluster before checking. "
			<<std::endl;

	//Have we calculated this already? If yes, return the result 
	if(checkIsAtEdge == false){
	
		for(it = hits.begin(); it != hits.end(); ++it){
			
			//If any of the hits are on the first/last col/row, flag the
			//cluste as being atEdge. 
			if(it->get_col() == nCols || it->get_col() == minCol){
				atEdge = true;
				checkIsAtEdge = true;
				return atEdge;
			} else if (it->get_row() == nRows || it->get_row() == minRow){
					atEdge = true;
					checkIsAtEdge = true;
					return atEdge;
			}
		}
		//You've checked.
		checkIsAtEdge = true;
	}	
	return atEdge;
}
				


//************* Getters ***************

Hits::iterator Cluster::get_firstHit(){
	return hits.begin();
}

Hits::iterator Cluster::get_endOfHits(){
	return hits.end();
}

unsigned Cluster::get_lv1id(){
	return lv1id;
}

unsigned Cluster::get_size(){
	return hits.size();
}

unsigned Cluster::get_width(){
	if(width == 0){
		if(DEBUG)
			std::cout<<"I am starting to caluclate the width"
				<<std::endl;
		find_width();
	}
	return width;
}

unsigned Cluster::get_length(){
	if(length == 0){
		if(DEBUG)
			std::cout<<"I am starting to caluclate the length"
				<<std::endl;
		find_length();
}
	return length;
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

void Cluster::set_length(unsigned arg_length){
	length = arg_length;
}

void Cluster::set_width(unsigned arg_width){
	width = arg_width;
}



