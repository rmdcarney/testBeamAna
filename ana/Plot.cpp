//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project:	High Eta TB Analysis
//Author:	RMD Carney
//Contact:	rcarney@lbl.gov
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//File:		Plot.cpp
//Description:	Plotting stuff
//Date: 	11/14
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <Plot.h>

#define DEBUG 1
#define PRINTOUTS 1
#define SAVE 1

#define nRows 336
#define nCols 80

//*** V A R S *****
int crimson = TColor::GetColor(220,20,60);
int darkGreen = TColor::GetColor(0,128,0);
int navy = TColor::GetColor(0,0,205);
int fuscia = TColor::GetColor(199,21,133);
int turquoise = TColor::GetColor(30,144,255);
int orange = TColor::GetColor(255,165,0);
int blueViolet = TColor::GetColor(138,43,266);
int saddleBrown = TColor::GetColor(139, 69, 19);
int cadetBlue = TColor::GetColor(95,158,160);
int chatreuse = TColor::GetColor(127,255,0);
int deepSkyBlue = TColor::GetColor(0,191,255);
int yellow = TColor::GetColor(255,255,0);
int violet = TColor::GetColor(238,130,238);
int slateGrey = TColor::GetColor(112,128,144);
int tomato = TColor::GetColor(255,99,71);
int cyan = TColor::GetColor(64,224,208);


TH1F* Plot::clusterSize(ClusterContainer* myClusters){


	ClusterContainer::iterator i;
	TH1F* sizeHist;
	TCanvas* c1;

	int largest(-1), smallest(1e5), size(-1);

	//Find the largest and smallest sizes
	for(i= myClusters->begin(); i!= myClusters->end(); ++i){
		size = i->get_size();
		if(size > largest)
			largest = size;
		else if(size < smallest)
			smallest = size;
	}

	int nBins = (largest-smallest)+2; //To ensure any rounding down is taken care of 

	//Initialise th1
	sizeHist = new TH1F("Cluster_size","Cluster_size", nBins, (double)smallest, (double)largest);

	//Fill
	for(i = myClusters->begin(); i!= myClusters->end(); ++i)
		sizeHist->Fill(i->get_size());

	//Add labels
	sizeHist->SetXTitle("Cluster size [pixels]");
	sizeHist->SetYTitle("# of clusters");
	sizeHist->SetFillColor(crimson);
	sizeHist->SetOption("TEXT00HIST");

	return sizeHist;

}

void Plot::print(TH1F* myTH1F, std::string path){

	std::string title = myTH1F->GetTitle();

	std::string filenameRoot = path + title + ".root";
	std::string filenameEps = path + title + ".eps";
	std::string filenamePng = path + title + ".png";

	TCanvas* c1 = new TCanvas( title.c_str(), title.c_str() );

	myTH1F->Draw();
	c1->Update();

	c1->Print(filenameRoot.c_str());
	c1->Print(filenameEps.c_str());	
	c1->Print(filenamePng.c_str());
}



