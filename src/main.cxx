#include <iostream>
#include "Hit.h"
#include "Event.h"
#include "RCEDataReader.h"

int main(){

	std::string filename = "~/Documents/Work_careers/LBNL/data/cosmic_000024_000000.dat";
	//Try reading the data
	RCEDataReader reader(filename);

	EventMap events;

	reader.m_importData(&events);

}
