#include <iostream>
#include "Hit.h"
#include "Event.h"
#include "RCEDataReader.h"

int main(int argc, char* argv[]){

	if(argc != 2){
		std::cout<< "Run like: ./bin/main file_to_be_analysed" <<std::endl;
		return 1;
	}
	std::string filename = argv[1];
	//Try reading the data
	RCEDataReader reader(filename);

	EventMap events;

	//Import the data into the map. Check to see if PRINTOUTS = 1 or not. 
	reader.m_importData(&events);
	
	//Check that the data got added to the map correctly
	std::cout<< "There is data in the map from: "
		<<events.size() << " links." << std::endl;
	std::cout<<"*Link*\t*# of hits*" << std::endl;

	unsigned numHits(0), total(0), numEvents(0);
	EventMap::iterator i;
	for(i=events.begin(); i!=events.end(); ++i){
		for(unsigned j=0; j<i->second->size(); j++){
			numHits += i->second->at(j).get_nHits();
		}
		numEvents += i->second->size();
		std::cout << i->first << ":\t"
			<< numHits << std::endl;
		total += numHits;
		numHits = 0;
	}
	std::cout << "====================\nTotal:\t"<<total
		<< "\n====================" <<std::endl;
	std::cout <<"\nOut of " <<  numEvents << " events." <<std::endl; 

}
