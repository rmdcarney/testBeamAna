#include <iostream>
#include "HitContainer.h"
#include "EventContainer.h"

int main(){

//Instantiate user-defined objects
HitContainer hit;

//Try getter/setter
hit.set_bcid(1);
hit.set_col(336);
hit.set_row(80);
hit.set_tot(10);

EventContainer event(123, 3304030, 0);

//Check
std::cout<< "An event happened. The event has LV1ID: " << event.get_lv1id() 
	<<", from chip: " << event.get_chipID() 
	<<", at link: " <<event.get_link() <<std::endl;

std::cout<< "There was also a hit! The hit has bcid: " << hit.get_bcid() 
	<<", at (col, row): " << hit.get_col() << ", " << hit.get_row()
	<<", with ToT " << hit.get_tot() << std::endl;

EventContainer anotherEvent;
anotherEvent.set_lv1id(123);
anotherEvent.set_chipID(3304031);
anotherEvent.set_link(1);
anotherEvent.addHit(hit);
anotherEvent.addHit(2, 21, 1, 8);

std::cout << "Then there was another event. This one had LV1ID, chip, and link: \n"
	<< anotherEvent.get_lv1id() <<" " << anotherEvent.get_chipID() << " " 
	<< anotherEvent.get_link() << std::endl;

std::cout<< "It had a bunch of hits, including:\n" 
	<< "*bicd*\t *col*\t *row*\t *tot*"<<std::endl;

for(unsigned int i=0; i<anotherEvent.get_nHits(); i++)
	std::cout<< anotherEvent.getHits()[i]->get_bcid()<<"\t " 
		<< anotherEvent.getHits()[i]->get_col()<<"\t "
		<< anotherEvent.getHits()[i]->get_row()<<"\t "
		<< anotherEvent.getHits()[i]->get_tot()<<"\t "
		<<std::endl;




}
