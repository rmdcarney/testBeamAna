//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		RCEDataReader.h
//Description:	Derived from DataReader base
//		Reads rce-framed (cosmicGui) raw data
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#ifndef RCEDATAREADER_H
#define RCEDATAREADER_H

#include <DataReader.h>

class RCEDataReader : public DataReader {
	public: 
		RCEDataReader();
		RCEDataReader(std::string arg_filename);
		~RCEDataReader();

		//Inherited methods
		void m_importData(EventMap*);
		void m_importMask(MaskMap*);
};

#endif
