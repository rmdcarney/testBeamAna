//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		Algorithm.cpp
//Description:	Clustering stuff
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Includes
#include <Algorithm.h>

#define DEBUG 0
#define PRINTOUTS 0

#define clusterMin 0
#define colLimit 1
#define rowLimit 2
#define bcidLimit 1

#define nRows 336
#define nCols 80

#define nRepeatedTriggers 16

int Algorithm::sgn(int val, int limit){
	return ((limit  < val) - (val < limit));
}

void Algorithm::resetBcidLimits(int bcid, int* bcidHigh, int* bcidLow, bool* bcidSet){

	switch(sgn(bcid, *bcidHigh)){
		case 1:
			std::cout<<"ERROR: in boundary conditions bcidHigh" 
				<<std::endl;
			return;

		case 0: 
			//bc = upper limit, set lower limit to 1 more
			if(bcid != 0){
				if(*bcidLow + bcidLimit <= nRepeatedTriggers)
					*bcidLow += bcidLimit;
				*bcidSet = true;
			}
			break;

		case -1:
			//Could be same bc or 1 less, do nothing
			switch(sgn(bcid, *bcidLow)){
				case 1:
					//bcid is same as in other hit
					break;
				case 0: 
					//bcid = lower limit, set upper limit to 1 less
					if(*bcidHigh != nRepeatedTriggers && (*bcidHigh-bcidLimit) != *bcidLow){
						*bcidHigh -= bcidLimit;
					}
					*bcidSet = true;
					break;
				case -1:
					std::cout<<"ERROR: in boundary condition bcidHigh"
						<<std::endl;
					return;
			}
			break;
	}

}

void Algorithm::resetRowLimits(int row, int* rowHigh, int* rowLow){

	int rowDiff = -1;
	switch(sgn(row, *rowHigh)){
		case 1: 
			std::cout<<"ERROR: in boundary condition row High"
				<<std::endl;
			return;
		case 0:
			//Row has same value as upper limit, set new upper limit
			*rowHigh += rowLimit;
			break;
		case -1:
			//Must be lower, try the lowerbound
			switch(sgn(row, *rowLow)){
				case 1: 
					//See which bound it is closer to
					if(abs(row - *rowLow) > abs(row - *rowHigh)){
						rowDiff = *rowHigh - row; 
						if(rowDiff <= rowLimit)		//Closer to upper limit
							*rowHigh = row+colLimit;
					} else if(abs(row - *rowLow) < abs(row - *rowHigh)) { //closer to lower limit
						rowDiff = row - *rowLow;
						if(rowDiff <= rowLimit)
							*rowLow = row- rowLimit;
					}
					break;
				case 0:
					*rowLow -= rowLimit;
					break;

				case -1:
					std::cout<<"ERROR: in boundary condition row/colLow"
						<<std::endl;
					return;
			}
			break;
	}

}

void Algorithm::resetColLimits(int col, int* colHigh, int* colLow){

	int colDiff = -1;
	switch(sgn(col, *colHigh)){
		case 1: 
			std::cout<<"ERROR: in boundary condition col High"
				<<std::endl;
			return;
		case 0:
			//Row has same value as upper limit, set new upper limit
			*colHigh += colLimit;
			break;
		case -1:
			//Must be lower, try the lowerbound
			switch(sgn(col, *colLow)){
				case 1: 
					//See which bound it is closer to
					if(abs(col - *colLow) > abs(col - *colHigh)){
						colDiff = *colHigh - col; 
						if(colDiff <= colLimit)		//Closer to upper limit
							*colHigh = col+colLimit;
					} else if(abs(col - *colLow) < abs(col - *colHigh)) { //closer to lower limit
						colDiff = col - *colLow;
						if(colDiff <= colLimit)
							*colLow = col- colLimit;
					}
					break;
				case 0:
					*colLow -= colLimit;
					break;

				case -1:
					std::cout<<"ERROR: in boundary condition colLow"
						<<std::endl;
					return;
			}
			break;
	}

}


void Algorithm::checkHitFitsBoundaryConditions(int* colHigh, int* colLow, int* rowHigh, int* rowLow, int* bcidHigh, int* bcidLow, bool* bcidSet, int col, int row, int bcid, int tot, EventContainer::iterator* i, std::list<Hit>::iterator* k, ClusterMap::iterator* cit){

	//Check to see if the current hit fits the boundary conditions
	if(col <= *colHigh && col >= *colLow){
		if(row <= *rowHigh && row >= *rowLow){
			if(bcid <= *bcidHigh && bcid >= *bcidLow){

				//If inside here, the hit fits the criteria to be a cluster
				if(DEBUG)
					std::cout<<"This hit fits the boundary conditions" << std::endl;

				//(1) Reset limits based on new hit
				//(a) bcid limits change only once
				if(DEBUG)
					std::cout<<"bcidLimits before: ("<< *bcidHigh << " , " << *bcidLow
						<<"): limitSet = " <<*bcidSet<<std::endl;

				if(!*bcidSet){

					//bcid limit is set per cluster - NB this is designed assuming bcid = +-1
					resetBcidLimits(bcid, bcidHigh, bcidLow, bcidSet);
				}   

				if(DEBUG)
					std::cout<<"bcidLimits after: ("<< *bcidHigh << " , " << *bcidLow
						<<"): limitSet = " << *bcidSet << std::endl;


				//(b) Row limits extend for length of cluster

				if(DEBUG)
					std::cout<<"rowLimits before: ("<< *rowHigh << " , " << *rowLow
						<<")"<<std::endl;
				resetRowLimits(row, rowHigh, rowLow);


				if(DEBUG)
					std::cout<<"rowLimits after: ("<< *rowHigh << " , " << *rowLow
						<<")"<<std::endl;

				//(b) Col limits extend for length of cluster

				if(DEBUG)
					std::cout<<"colLimits before: ("<< *colHigh << " , " << *colLow
						<<")"<<std::endl;
				resetColLimits(col, colHigh, colLow);


				if(DEBUG)
					std::cout<<"colLimits after: ("<< *colHigh << " , " << *colLow
						<<")"<<std::endl;

				//With the limits set, add the hit to the cluster
				(*cit)->second->back().addHit(bcid, col, row, tot);

				//Remove hit from event - iterator safe
				*k = (*i)->eraseHit(*k);
				*k--;
			}   
		}   
	}   

}

//TODO: DRAFT ONLY
//We're going to modify the events in the algorithm so take a copy of the data
void Algorithm::findClusters_iterative(ClusterMap* clusters, EventMap events){


	//Make some iterators
	ClusterMap::iterator cit;
	EventMap::iterator mit;
	EventContainer::iterator i;
	std::list<Hit>::iterator k;

	//Temp vars
	int colHigh(-1), colLow(-1), 
	    rowHigh(-1), rowLow(-1),
	    bcidHigh(-1), bcidLow(-1);
	int col(-1),row(-1),bcid(-1),tot(-1);

	bool bcidSet = false;

	//Iterate over each link, event TODO; get rid of second condition
	for(mit = events.begin(); mit !=events.end(); ++mit){
		if(DEBUG){
			std::cout<<"================================"<<std::endl;
			std::cout<<"Starting new loop over link "<<mit->first<<std::endl;
			std::cout<<"================================"<<std::endl;
		}

		//Switch into the correct link for the cluster too
		if(clusters->find(mit->first)== clusters->end() )
			clusters->insert(std::pair<unsigned,ClusterContainer*>(mit->first, new ClusterContainer));
		cit = clusters->find(mit->first);

		//Event counter
		int counter1 =0;

		//Loop over event
		for(i = mit->second->begin(); i!= mit->second->end(); ++i){
			if(DEBUG)
				std::cout<<"\n&&&&&&&& N E W    E V E N T &&&&&&&&&&&\n"<<std::endl;
			
			//Cluster all the hits!
			while(i->get_nHits() > 0){
				//In each event, look for clusters
				//Make sure there are multiple hits 
				if(i->get_nHits() > clusterMin){
					//iterate over the hits

					if(DEBUG)
						std::cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
							<<"The number of hits in this event are: "<<
							i->get_nHits()<<" at place " <<counter1<<"\n" << std::endl;

					if(DEBUG)
						std::cout<<"\n------------- Hit loop ----------------\n" <<std::endl;
					
					//Reset bcid check
					bcidSet = false;
					//Hit iterator counter
					int counter =0;
					
					//Loop over hits
					for(k = i->get_firstHit(); k != i->get_endOfHits();  ++k){

						//First hit operations
						if(counter==0){
							if(DEBUG)
								std::cout<<"\niteration: "<<counter<<std::endl;
							
							//Boundary checks
							colHigh =(int)k->get_col()+colLimit;
							colLow = colHigh-2*colLimit;
							rowHigh = (int)k->get_row()+rowLimit;
							rowLow = rowHigh-2*rowLimit;
							bcidHigh = (int)k->get_bcid()+bcidLimit;
							bcidLow = bcidHigh-2*bcidLimit;

							//Vars
							bcid = k->get_bcid();
							col = k->get_col();
							row = k->get_row();
							tot = k->get_tot();

							//Check assigned values
							if(DEBUG){
								std::cout<<"First hit ....." <<std::endl;
								std::cout<<"\nbcid: " <<bcid
									<<"\ncol: " <<col
									<<"\nrow: "<<row
									<<"\ntot: "<<tot
									<<"\ncolHigh: " <<colHigh <<", colLow: " <<colLow
									<<"\nrowHigh: "<<rowHigh<<", rowLow: " <<rowLow
									<<"\nbcidHigh: "<<bcidHigh<<", bcidLow: " <<bcidLow
									<<std::endl;
							}

							//Boundary checks
							if(colHigh > nCols)
								colHigh = nCols;
							if(colLow < 0)
								colLow = 0;
							if(rowHigh > nRows)
								rowHigh = nRows;
							if(rowLow < 0)
								rowLow = 0;
							if(bcid < 0){
								std::cout<<"ERROR: bcid <0"<<std::endl;
								return;
							}
							if(bcid > nRepeatedTriggers){
								std::cout<<"ERROR: bcid out of range"<<std::endl;
								return;
							}
							if(bcidHigh > nRepeatedTriggers){
								bcidHigh = nRepeatedTriggers;
							}
							if(bcidLow < 0){
								bcidLow = 0;
							}


							//Check assigned values after boundary checks
							if(DEBUG){
								std::cout<<"Assigned values after boundary checks:" <<std::endl;
								std::cout<<"colHigh: " <<colHigh <<", colLow: " <<colLow
									<<"\nrowHigh: "<<rowHigh<<", rowLow: " <<rowLow
									<<"\nbcidHigh: "<<bcidHigh<<", bcidLow: " <<bcidLow
									<<std::endl;
							}
							
							//Add a new cluster to the container
							cit->second->push_back(Cluster());
							cit->second->back().addHit(bcid, col, row, tot);
							cit->second->back().set_lv1id(i->get_lv1id());

							//Remove hit from event and increment by 1.
							k = i->eraseHit(k);
							//Now we have added this hit to the cluster we can increment the iterator. 
							counter++;
							//Finally, if this was a 1-hit event, break.
							if(i->get_nHits() == 0)
								break;
						}

						if(PRINTOUTS)
							std::cout<<"\nIteration: "<<counter<<std::endl;
						
						//Get vars from hit
						bcid = k->get_bcid();
						col = k->get_col();
						row = k->get_row();
						tot = k->get_tot();

						if(DEBUG){
							std::cout<<"\nNext HIT *****" <<std::endl;
							std::cout<<"bcid: " <<bcid
								<<"\ncol: " <<col
								<<"\nrow: " <<row
								<<"\ntot: " <<tot <<std::endl;
						}
						
						//Check to see if this hit should be added to the cluster, if yes: add it and remove it from event
						checkHitFitsBoundaryConditions(&colHigh, &colLow, &rowHigh, &rowLow, &bcidHigh, &bcidLow, &bcidSet, col, row, bcid, tot, &i, &k, &cit);

						counter++;
					}
					
					//If there is more than 1 hit in the cluster, and if there are still hits in the event
					if(cit->second->back().get_size() > 1 && i->get_nHits()>0){
						//iterate through the list again to check that no hits were missed
						//with the final bounds

						//This is the while loop break condition, if, after an iteration the cluster size hasn't increased 
						//None of the remaining hits belong in the cluster
						int clusterSizeOld = cit->second->back().get_size();
						int clusterSizeNew = 0;

						//Second break condition: run out of hits
						while(i->get_nHits()>0){

							if(DEBUG){
								std::cout<<"Iterated through event. Now cross-checking hits with current cluster"<<std::endl;
								counter = 0;
							}

							//If no new hits have been added to the cluster, we have them all
							if(clusterSizeOld == clusterSizeNew)
								break;

							clusterSizeOld = clusterSizeNew;

							//Iterate through remainign hits
							for(k = i->get_firstHit(); k != i->get_endOfHits(); ++k){

								//Get vars from hit
								bcid = k->get_bcid();
								col = k->get_col();
								row = k->get_row();
								tot = k->get_tot();

								if(DEBUG){
									std::cout<<"\nNext HIT *****" <<std::endl;
									std::cout<<"bcid: " <<bcid
										<<"\ncol: " <<col
										<<"\nrow: " <<row
										<<"\ntot: " <<tot <<std::endl;
								}

								//Check to see if this hit should be added to the cluster, if yes: add it and remove it from event
								checkHitFitsBoundaryConditions(&colHigh, &colLow, &rowHigh, &rowLow, &bcidHigh, &bcidLow, &bcidSet, col, row, bcid, tot, &i, &k, &cit);
							}
							
							//Check cluster size after iteration
							clusterSizeNew = cit->second->back().get_size(); 

						} //while loop
					} //if statement

				} //Outer if statment

				counter1++;
			} //while(hits in event) 
		} //Event loop
	} //link loop
}
