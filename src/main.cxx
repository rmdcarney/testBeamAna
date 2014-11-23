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

	//Try and access some hits and print them
	std::list<Hit>::iterator hitIt;
	unsigned bcid=100000000;
	unsigned sizeOfHits = 10000000;
	//for(hitIt = events[0]->at(0).getHits().begin(); hitIt != events[0]->at(0).getHits().end(); ++hitIt){
	
	sizeOfHits = events[0]->at(0).get_nHits();

	//Iterate over link 0 and see where there are actually hits!
//	for(unsigned j=0; j<events[0]->size(); j++)
//		std::cout<< j << "\t" << events[0]->at(j).get_nHits()<<std::endl;
	
//	bcid = events[0]->at(10).getHits().back().get_row();
//	std::cout<<"bcid: " << bcid <<std::endl;
	unsigned a=0;
//Try and look at the information in one of the hits
	for(hitIt = events[0]->at(10).getHits().begin(); hitIt != events[0]->at(10).getHits().end(); ++hitIt){
		std::cout<<a<<std::endl;
		a++;
		//bcid = (*hitIt).get_col();//events[0]->at(0).getHits().back().get_tot();
		//std::cout<<"bcid: " <<bcid<<std::endl;
	}

/*
	//Check functionality of pop_back
	std::vector<int> testArr;
	testArr.push_back(1);
	testArr.push_back(2);
	testArr.push_back(3);
	
	for(int i=0; i<testArr.size(); i++)
	std::cout<<"Vector is: "<<testArr[i] << "\t";

	testArr.pop_back();
	std::cout<<""<<std::endl;

	for(int i=0; i<testArr.size(); i++)
	std::cout<<"Vector is: "<<testArr[i] << "\t";
*/	
	

	
}
