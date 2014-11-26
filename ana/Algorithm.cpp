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

int Algorithm::sgn(int val, int limit){
	return ((limit  < val) - (val < limit));
}

//TODO: DRAFT ONLY, for short direction
//We're going to modify the events in the algorithm so take a copy of the data
void Algorithm::findClusters(ClusterContainer* clusters, EventMap events){

	//Boundary limits for clusters
	int colLimit=1;
	int rowLimit=2;
	int bcidLimit=1;


	//Make some iterators
	ClusterContainer::iterator cit;
	EventMap::iterator mit;
	EventContainer::iterator i;
	std::list<Hit>::iterator j,k;

	//Temp vars
	int colHigh(-1), colLow(-1), 
	    rowHigh(-1), rowLow(-1),
	    bcidHigh(-1), bcidLow(-1);
	int col(-1),row(-1),bcid(-1);

	bool bcidSet = false;

	//Iterate over each link, event
	for(mit = events.begin(); mit != events.end(); ++mit){
		for(i = mit->second->begin(); i != mit->second->end(); ++i){

			//In each event, look for clusters
			//Make sure there are multiple hits 
			if(i->get_nHits() > clusterMin){
				//iterate over the hits
				for(j = i->get_firstHit(); j != i->get_lastHit(); ++j){

					//Inner loop will reduce in size as stuff is removed (TODO)
					k = i->get_firstHit();
					for(k = i->get_firstHit(); k != i->get_lastHit();  ++k){

						if(k == i->get_firstHit()){

							//Get variables from first hit
							//TODO boundary checks
							colHigh =(int)k->get_col()+colLimit;
							colLow = colHigh-2*colLimit;
							rowHigh = (int)k->get_row()+rowLimit;
							rowLow = rowHigh-2*rowLimit;
							bcidHigh = (int)k->get_bcid()+bcidLimit;
							bcidLow = bcidHigh-2*bcidLimit;

							//Add a new cluster to the container
							clusters->push_back(Cluster());
							clusters->back().addHit(k->get_bcid(), k->get_col(), k->get_row(), k->get_tot());

							//Now we have added this hit to the cluster we can increment the iterator. 
							//Don't delete it from the event data yet because it might not be a real cluster
							++k;
						}

						//Check to see if the current hit fits the boundary conditions
						if(col <= colHigh && col >= colLow){
							if(row <= rowHigh && row >= rowLow){
								if(bcid <= bcidHigh && bcid >= bcidLow){

									//If inside here, the hit fits the criteria to be a cluster
									//(1) Reset limits based on new hit
									//(a) bcid limits change only once
									if(!bcidSet){
										//bcid limit is set per cluster - NB this is designed assuming bcid = +-1
										switch(sgn(bcid, bcidHigh)){
											case 1:
												std::cout<<"ERROR: in boundary conditions bcidHigh" 
													<<std::endl;
												return;

											case 0: 
												//bc = upper limit, set lower limit to 1 less
												bcidLow -= bcidLimit;
												bcidSet = true;
												break;

											case -1:
												//Could be same bc or 1 less, do nothing
												switch(sgn(bcid, bcidLow)){
													case 1:
														//bcid is same as in other hit
														break;
													case 0: 
														//bcid = lower limit, set upper limit to 1 more
														bcidHigh += bcidLimit;
														bcidSet = true;
														break;
													case -1:
														std::cout<<"ERROR: in boundary condition bcidHigh"
															<<std::endl;
														return;
												}
												break;
										}

									}
									//(b) Row limits extend for length of cluster
									switch(sgn(row, rowHigh)){
										case 1: 
											std::cout<<"ERROR: in boundary condition rowHigh"
												<<std::endl;
											return;
										case 0:
											//Row has same value as upper limit, set new upper limit
											rowHigh += rowLimit;
											break;
										case -1:
											//Must be lower, try the lowerbound
											switch(sgn(row, rowLow)){
												case 1: 
													//In bounds, do nothing
													break;
												case 0:
													//Row has same value of lower bound, set new lower limit
													rowLow -= rowLimit;
													break;
												case -1:
													std::cout<<"ERROR: in boundary condition bcidLow"
														<<std::endl;
													return;
											}
											break;
									}

									//With the limits set, add the hit to the cluster
									clusters->back().addHit(k->get_bcid(), k->get_col(), k->get_row(), k->get_tot());

									//Remove hit from event
									i->eraseHit(k);
								}
							}
						}
					}
					//If there were no hits for this cluster remove cluster, 
					//else remove first hit from event
					if(clusters->back().get_size() == 0)
						clusters->pop_back();
					else{
						i->eraseHit(j);
					}
				}
			}
		}
	}
}
