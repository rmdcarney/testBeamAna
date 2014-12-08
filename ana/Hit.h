//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		Hit.h
//Description:	Contains hit info
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#ifndef HIT_H
#define HIT_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <sstream>

using namespace std;

class Hit{
	public:
		//Constructors, destructors
		Hit();
		Hit(int arg_bcid, int arg_col, int arg_row, int arg_tot);
		~Hit(){};

		//Methods
		bool compare_rows(const Hit& lhs, const Hit& rhs);
		bool compare_cols(const Hit& lhs, const Hit& rhs);

		//Getters
		//TODO vector<Hit> getHits();
		int get_bcid() const;
		int get_col() const;
		int get_row() const;
		int get_tot() const;

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
		bool tot_overflow;
		//TODO std::vector<Hit> hits;
		
};

typedef std::list<Hit> Hits;
#endif


