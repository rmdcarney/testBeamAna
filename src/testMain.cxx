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
	std::cout << "====================\nTotal:\t"<<total
		<< "\n====================" <<std::endl;
	std::cout <<"\nOut of " <<  numEvents << " events." <<std::endl; 

	//Try and access some hits and print them
	std::list<Hit>::iterator hitIt;
	unsigned bcid=100000000;
	unsigned sizeOfHits = 10000000;
	//for(hitIt = events[0]->at(0).getHits().begin(); hitIt != events[0]->at(0).getHits().end(); ++hitIt){
	
//	sizeOfHits = events[0]->front().get_nHits();
	unsigned counter=0;
	//Iterate over link 0 and see where there are actually hits!
	/*for(j=events[0]->begin(); j!= events[0]->end(); ++j){
		std::cout<< counter << "\t" << j->get_nHits()<<std::endl;
		counter++;
	}
*///	bcid = events[0]->at(12).getHits().back().get_row();
	unsigned a=0;
//Try and look at the information in one of the hits
	
	j = events[0]->begin();
	++j;
	++j;
	++j;

	//Check the access is working (tick!)
	for(hitIt = j->get_firstHit(); hitIt != j->get_lastHit(); ++hitIt){
		std::cout<<a<<" ";
		a++;
		bcid = (*hitIt).get_tot();//events[0]->at(0).getHits().back().get_tot();
		std::cout<<"bcid: " <<bcid<<std::endl;
	}

}
