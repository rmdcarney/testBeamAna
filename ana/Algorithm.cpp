//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		Algorithm.cpp
//Description:	Clustering stuff
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <Algorithm.h>
#define DEBUG 1
#define clusterMin 1

//We're going to modify the events in the algorithm so take a copy of the data
void Algorithm::findClusters(ClusterContainer* clusters, EventMap events){

	//Make some iterators
	ClusterContainer::iterator cit;
	EventMap::iterator mit;
	EventContainer::iterator i;
	std::list<Hit>::iterator j,k;

	//Temp vars
	Hit tempHit;

	//Iterate over each link, event
	for(mit = events.begin(); mit != events.end(); ++mit){
		for(i = mit->second->begin(); i != mit->second->end(); ++i){
			
			//In each event, look for clusters
			//Make sure there are multiple hits 
			if(i->get_nHits() > clusterMin){
				//iterate over the hits
				for(j = i->get_firstHit(), j= i->get_lastHit(); ++j){
					
					tempHit(j->get_bcid(), j->get_col(), j->get_row(), j->get_tot());
					k = i->get_firstHit();
					for(k = i->get_firstHit(); k< i->get_lastHit();  ++k){

					
				
			}
				

	//TODO
	int a = 12;
	a-3;
}
