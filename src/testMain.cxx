#include <iostream>
#include "Hit.h"
#include "Event.h"
#include "RCEDataReader.h"
#include "Algorithm.h"

int main(int argc, char* argv[]){

	if(argc != 2){
		std::cout<< "Run like: ./bin/main file_to_be_analysed" <<std::endl;
		return 1;
	}
	std::string filename = argv[1];
	//Try reading the data
	
	RCEDataReader reader(filename);

	EventMap events;
	ClusterMap clusters;

	//Import the data into the map. Check to see if PRINTOUTS = 1 or not. 
	std::cout<<"Starting..."<<std::endl;
	std::cout<<"Reading data file...."<<std::endl;
	reader.m_importData(&events);
	
	//Check that the data got added to the map correctly
	std::cout<<"*********************************"<<std::endl;
	std::cout<< "There is data in the map from: "
		<<events.size() << " links." << std::endl;
	std::cout<<"*********************************"<<std::endl;
	
	std::cout<<"*Link*\t*# of hits*" << std::endl;
	
	unsigned numHits(0), total(0), numEvents(0);
	EventMap::iterator i;
	EventContainer::iterator j;

	for(i=events.begin(); i!=events.end(); ++i){
		for(j=i->second->begin(); j != i->second->end(); ++j){
			numHits += j->get_nHits();
		}
		numEvents += i->second->size();
		std::cout << i->first << ":\t"
			<< numHits << std::endl;
		total += numHits;
		numHits = 0;
	}
	std::cout << "====================\nTotal:\t"<<total <<"  hits"
		<< "\n====================" <<std::endl;
	std::cout <<"Out of " <<  numEvents << " events.\n\n" <<std::endl; 

	//Add the links to the ClusterMap
	for(i=events.begin(); i!=events.end(); ++i){
		clusters.insert(std::pair<unsigned,ClusterContainer*>(i->first, new ClusterContainer));
	}

	Algorithm::findClusters_iterative(&clusters, events);

}
