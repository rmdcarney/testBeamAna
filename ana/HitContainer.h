//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		HitContainer.h
//Description:	Contains hit info
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#ifndef HITCONTAINER_H
#define HITCONTAINER_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <sstream>

using namespace std;

class HitContainer{
	public:
		//Constructors, destructors
		HitContainer();
		HitContainer(int arg_bcid, int arg_col, int arg_row, int arg_tot);
		~HitContainer(){};

		//Methods
		
		//Getters
		//TODO vector<Hit> getHits();
		int get_bcid();
		int get_col();
		int get_row();
		int get_tot();

		//******* Setters ********
		//TODO void setData(std::vector<double> newT, std::vector<double> newY);
		void set_bcid(int arg_bcid);
		void set_col(int arg_col);
		void set_row(int arg_row);
		void set_tot(int arg_tot);


	private:
		int bcid;
		int col;
		int row;
		int tot;

		//TODO std::vector<Hit> hits;
		
};


#endif


