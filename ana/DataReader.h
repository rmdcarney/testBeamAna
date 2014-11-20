//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		DataReader.h
//Description:	I/o for data into analysis
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#ifndef DATAREADER_H
#define DATAREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <EventContainer.h>

using namespace std;

class DataReader{
	public:
		//Constructors, destructors
		DataReader();
		DataReader(std::string arg_filename);
		~DataReader();

		//Methods
		virtual std::vector<EventContainer> m_importData();
		void m_write_txt(std::string outputFile);
		void m_write_hist(std::string outputFile);

		//Getters
		unsigned get_timestamp();
		unsigned get_num_rces();
		unsigned get_event_size();
		unsigned get_event_number();
		unsigned get_rce_number();

		//Setters

	protected:
		//Member variables
		std::string filename;
		unsigned timestamp;
		unsigned num_rces;
		unsigned event_size;
		unsigned event_number;
		unsigned rce_number;
		char trig_info[9*4];

		//Member class, shamelessly lifted from 
		//Jens Dopke & Matevz Cerv
		class FormattedRecord{
			public: 
				//Record types
				struct Generic{
					unsigned int unused2: 29;
					unsigned int headerkey: 1;
					unsigned int headerRCEkey: 1;
					unsigned int datakey: 1;
				};

				struct Header{
					unsigned int bcid: 13;
					unsigned int lv1id: 12;
					unsigned int link: 4;
					unsigned int key: 1;
					unsigned int unused1: 2;
				};

				struct HeaderRCE{
					unsigned int rce: 8;
					unsigned int unusedRCE: 22;
					unsigned int key: 1;
					unsigned int unused1: 1;
				};

				struct Data{
					unsigned int row: 9;
					unsigned int col: 7;
					unsigned int tot: 8;
					unsigned int chipID: 4;
					unsigned int unused1: 3;
					unsigned int key: 1;
				};

				union Record{
					unsigned int ui;
					Generic generic;
					Header header;
					Data data;
					HeaderRCE headerRCE;
				};

				enum type{HEADER=0x20000000, HEADERTWO=0x40000000, DATA=0x80000000};
				//Constructors
				FormattedRecord(FormattedRecord::type ty);
				FormattedRecord(unsigned& wd);

				//Methods
				bool isHeader();
				bool isHeaderRCE();
				bool isData();

				//Getters
				unsigned get_link();
				unsigned get_bcid();
				unsigned get_lv1id();
				unsigned get_rce();
				unsigned get_chipID();
				
				unsigned get_tot();
				unsigned get_col();
				unsigned get_row();
				
				unsigned get_word();

				//Setters
				void set_link(unsigned arg_link);
				void set_bcid(unsigned arg_bcid);
				void set_lv1id(unsigned arg_lv1id);
				void set_rce(unsigned arg_rce);
				void set_chipID(unsigned arg_chipID);

				void set_tot(unsigned arg_tot);
				void set_col(unsigned arg_col);
				void set_row(unsigned arg_row);
			
			private:
				Record m_record;
		};
};


#endif


