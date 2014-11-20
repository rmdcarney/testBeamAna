//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		HitContainer.cpp
//Description:	Contains hit info
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <HitContainer.h>
#define DEBUG 1

HitContainer::HitContainer() {
	bcid=-1;
	col=0;
	row=0;
	tot=-1;

}

HitContainer::HitContainer(int arg_bcid, int arg_col, int arg_row, int arg_tot){
	bcid = arg_bcid;
	col = arg_col;
	row = arg_row;
	tot = arg_tot;
}

//Getters

int HitContainer::get_bcid(){
	return bcid;
}

int HitContainer::get_col(){
	return col;
}

int HitContainer::get_row(){
	return row;
}

int HitContainer::get_tot(){
	return tot;
}

//Setters

void HitContainer::set_bcid(int arg_bcid){
	bcid = arg_bcid;
}

void HitContainer::set_col(int arg_col){
	col = arg_col;
}

void HitContainer::set_row(int arg_row){
	row = arg_row;
}

void HitContainer::set_tot(int arg_tot){
	tot = arg_tot;
}

