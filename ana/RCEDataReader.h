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

class RCEDataReader:protected DataReader{
	public: 
		RCEDataReader();
		RCEDataReader(std::string arg_filename):DataReader(std::string arg_filename);
		~RCEDataReader();

		//Overloaded methods

};

#endif
