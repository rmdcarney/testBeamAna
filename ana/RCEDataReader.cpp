//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		RCEDataReader.cpp
//Description:	Derived from DataReader base
//		Reads rce-framed (cosmicGui) raw data
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <RCEDataReader.h>

#define PRINTOUTS 0

//Inherit base constructor
RCEDataReader::RCEDataReader(std::string arg_filename) : DataReader(arg_filename){
}

//Placeholder destructor
RCEDataReader::~RCEDataReader(){}

//Since all of the getter and setter methods are taken care of in the base class the derived class really only needs to worry about the virtual function. 
void RCEDataReader::m_importData(EventMap* events ){

	if(PRINTOUTS)
		std::cout << "Opening file: " << filename <<std::endl;

	//Read file in binary mode, note bitwise OR 
	std::fstream infile(filename.c_str(), std::fstream::in | std::fstream::binary);

	if(PRINTOUTS)
		std::cout<< "... reading file ..." <<std::endl;

	//Timestamp: 4 bytes
	timestamp = 0;
	infile.read((char*)&timestamp, 4);
	if(PRINTOUTS)
		std::cout<<"Data with timestamp: "<< timestamp << std::endl;

	//Number of rce's: 4 bytes
	num_rces = 0;
	infile.read((char*)&num_rces, 4);
	if(PRINTOUTS)
		std::cout<<"RCE's used: " << num_rces << std::endl;

	//********** E V E N T S **********
	while(infile){

		//Event size: 4 bytes
		event_size = 0;
		infile.read((char*)&event_size, 4);

		//Break here if reached end of file
		if(!infile)
			break;

		//Event number: 4 bytes
		event_number = 0;
		infile.read((char*)&event_number, 4);

		//RCE number: 4 bytes
		rce_number = 0;
		infile.read((char*)&rce_number, 4);

		//Trigger information: 9*4 bytes
		infile.read(trig_info, 9*4);
		//TODO

		event_size -= 12*4; //Subtract the parts of header already read

		//Read FE data
		char *fe_data = new char[event_size];
		infile.read(fe_data, event_size);
		unsigned bcid, link;

		for(unsigned i=0; i<event_size; i+=4){
			//Cast first char to ui, so can tell what type of record it is
			FormattedRecord record(*(unsigned*)&fe_data[i]);
			bcid = 0;
			if(record.isHeader()){
				link = record.get_link();
				//For each new link, we add an EventContainer to the EventMap
				if(events->find(link)==events->end() )
					events->insert(std::pair<unsigned,EventContainer*>(link, new EventContainer));
				//Check if the previous event had any hits, if it didn't remove it from the container:
				else if (events->at(link)->back().get_nHits() == 0)
					events->at(link)->pop_back();
				
				//For a new event (i.e. a new trigger), add an event to the EventContainer
				events->at(link)->push_back(Event(record.get_lv1id()));
				
				//This is used in the Hit info
				bcid = record.get_bcid();
				
				if(PRINTOUTS){
					std::cout<< "DH: "<< record.get_lv1id() <<" "
						<< record.get_bcid() << " "
						<< record.get_link() << std::endl;
				}
			} else if(record.isData()) {
				//Temp var just to keep the code more readable
				Hit tempHit;
				tempHit.set_bcid(bcid);
				tempHit.set_col(record.get_col());
				tempHit.set_row(record.get_row());
				tempHit.set_tot(record.get_tot());
				//Add the hit to the last event at that link
				events->at(link)->back().addHit(tempHit);
				
				if(PRINTOUTS)
					std::cout<< "DR: "<< record.get_col() <<" "
						<< record.get_row() << " "
						<< record.get_tot() << std::endl;

			}
		}
		
		EventMap::iterator it;

		std::cout<<"I get this far" << std::endl;
		for(it = events->begin(); it != events->end(); ++it){
			if((*it).second != NULL){
				if((*it).second->back().get_nHits() == 0)
					(*it).second->pop_back();
			}
		}
		delete fe_data;
	}
}






