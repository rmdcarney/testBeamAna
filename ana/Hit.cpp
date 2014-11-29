//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		Hit.cpp
//Description:	Contains hit info
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <Hit.h>
#define DEBUG 1

Hit::Hit() {
	bcid=-1;
	col=0;
	row=0;
	tot=-1;
	tot_overflow = false;
}

Hit::Hit(int arg_bcid, int arg_col, int arg_row, int arg_tot){
	bcid = arg_bcid;
	col = arg_col;
	row = arg_row;
	set_tot(arg_tot);
}

//Getters

int Hit::get_bcid(){
	return bcid;
}

int Hit::get_col(){
	return col;
}

int Hit::get_row(){
	return row;
}

int Hit::get_tot(){
	return tot;
}

//Setters

void Hit::set_bcid(int arg_bcid){
	bcid = arg_bcid;
}

void Hit::set_col(int arg_col){
	col = arg_col;
}

void Hit::set_row(int arg_row){
	row = arg_row;
}

void Hit::set_tot(int arg_tot){
	if(arg_tot > 0){
		if(arg_tot < 14){
			tot = arg_tot;
		} else {
			tot_overflow = true;
			tot = 14;
		}
	} else {
		std::cout<<"\nERROR: ToT = "<<arg_tot
			<<std::endl;
	}
}

