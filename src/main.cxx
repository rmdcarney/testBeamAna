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

	reader.m_importData(&events);

}
