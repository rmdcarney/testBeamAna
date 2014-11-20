//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		DataReader.cpp
//Description:	I/o for data into analysis
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <DataReader.h>
#define DEBUG 1

DataReader::DataReader(){}

DataReader::DataReader(std::string arg_filename){
	filename = arg_filename;
}

DataReader::~DataReader(){}

//Getters
unsigned DataReader::get_timestamp(){
	return timestamp;
}

unsigned DataReader::get_num_rces(){
	return num_rces;
}

unsigned DataReader::get_event_size(){
	return event_size;
}

unsigned DataReader::get_event_number(){
	return event_number;
}

unsigned DataReader::get_rce_number(){
	return rce_number;
}

// ============= Nested class implementation ============

DataReader::FormattedRecord::FormattedRecord(FormattedRecord::type ty){
	m_record.ui=ty;
}

DataReader::FormattedRecord::FormattedRecord(unsigned& wd){
	m_record.ui=wd;
}

//******** Struct definitions ********
//TODO is there a way around this??
/*
struct DataReader::FormattedRecord::Generic{
	unsigned int unused2: 29;
	unsigned int headerkey: 1;
	unsigned int headerRCEkey: 1;
	unsigned int datakey: 1;
};

struct DataReader::FormattedRecord::Header{
	unsigned int bcid: 13;
	unsigned int lv1id: 12;
	unsigned int link: 4;
	unsigned int key: 1;
	unsigned int unused1: 2;
};

struct DataReader::FormattedRecord::HeaderRCE{
	unsigned int rce: 8;
	unsigned int unusedRCE: 22;
	unsigned int key: 1;
	unsigned int unused1: 1;
};

struct DataReader::FormattedRecord::Data{
	unsigned int row: 9;
	unsigned int col: 7;
	unsigned int tot: 8;
	unsigned int chipID: 4;
	unsigned int unused1: 3;
	unsigned int key: 1;
};

union DataReader::FormattedRecord::Record{
	unsigned int ui;
	Generic generic;
	Header header;
	Data data;
	HeaderRCE headerRCE;
};

*/
//********** Methods **********

bool DataReader::FormattedRecord::isHeader(){
	return m_record.generic.headerkey;
}

bool DataReader::FormattedRecord::isHeaderRCE(){
	return m_record.generic.headerRCEkey;
}

bool DataReader::FormattedRecord::isData(){
	return m_record.generic.datakey;
}

//********* Getters **********

unsigned DataReader::FormattedRecord::get_link(){
	return m_record.header.link;
}

unsigned DataReader::FormattedRecord::get_bcid(){
	return m_record.header.bcid;
}

unsigned DataReader::FormattedRecord::get_lv1id(){
	return m_record.header.lv1id;
}

unsigned DataReader::FormattedRecord::get_rce(){
	return m_record.headerRCE.rce;
}

unsigned DataReader::FormattedRecord::get_chipID(){
	return m_record.data.chipID;
}

unsigned DataReader::FormattedRecord::get_tot(){
	return m_record.data.tot;
}

unsigned DataReader::FormattedRecord::get_col(){
	return m_record.data.col;
}

unsigned DataReader::FormattedRecord::get_row(){
	return m_record.data.row;
}

unsigned DataReader::FormattedRecord::get_word(){
	return m_record.ui;
}

//********* Setters ***********

void DataReader::FormattedRecord::set_link(unsigned arg_link){
	m_record.header.link = arg_link;
}

void DataReader::FormattedRecord::set_bcid(unsigned arg_bcid){
	m_record.header.bcid = arg_bcid;
}

void DataReader::FormattedRecord::set_lv1id(unsigned arg_lv1id){
	m_record.header.lv1id = arg_lv1id;
}

void DataReader::FormattedRecord::set_rce(unsigned arg_rce){
	m_record.headerRCE.rce = arg_rce;
}

void DataReader::FormattedRecord::set_chipID(unsigned arg_chipID){
	m_record.data.chipID = arg_chipID;
}

void DataReader::FormattedRecord::set_tot(unsigned arg_tot){
	m_record.data.tot = arg_tot;
}

void DataReader::FormattedRecord::set_col(unsigned arg_col){
	m_record.data.col = arg_col;
}

void DataReader::FormattedRecord::set_row(unsigned arg_row){
	m_record.data.row = arg_row;
}

