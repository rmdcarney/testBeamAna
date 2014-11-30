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
#define min 1

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

TH1F* Plot::clusterToT(ClusterContainer* myClusters){

	ClusterContainer::iterator i;
	TH1F* totHist;

	int largest(-1), smallest(1e5), size(-1);

	//Find the largest and smallest sizes
	for(i= myClusters->begin(); i!= myClusters->end(); ++i){
		size = i->get_totalToT();
		if(size > largest)
			largest = size;
		else if(size < smallest)
			smallest = size;
	}

	int nBins = (largest-smallest)+2; //To ensure any rounding down is taken care of 

	//Initialise th1
	totHist = new TH1F("Cluster_tot","Cluster_tot", nBins, (double)smallest, (double)largest);

	//Fill
	for(i = myClusters->begin(); i!= myClusters->end(); ++i)
		totHist->Fill(i->get_totalToT());

	//Add labels
	totHist->SetXTitle("Cluster tot [bc]");
	totHist->SetYTitle("# of clusters");
	totHist->SetFillColor(turquoise);
	totHist->SetOption("TEXT00HIST");

	return totHist;

}

std::list<TH2F*> eventClusters(ClusterContainer* myClusters){

	std::list<TH2F*> plots;
	ClusterContainer::iterator i;
	std::list<Hit>::iterator j;
	std::stringstream ss;

	unsigned lv1id(-1), current_lv1id(-1), counter(0);
	std::string base = "eventClusters_";
	std::string title = "";
	std::string xLabel = "Column [pixel]";
	std::string yLabel = "Row [Pixel]";
	std::string zLabel = "Cluster #";

	for(i = myClusters->begin(); i != myClusters->end(); ++i){
		//Get the event associated with this cluster
		lv1id = i->get_lv1id();

		//If this is a new event, start a new hist
		if(lv1id != current_lv1id){
			//reset values
			counter = 0;
			current_lv1id = lv1id;
			ss << current_lv1id;
			title = base + ss.str();
			//Clear ss
			ss.str("");

			//Make new hist
			plots.push_back(new TH2F(title.c_str(), title.c_str(), nCols, min, nCols, nRows, min, nRows));
			plots.back()->SetXTitle(xLabel.c_str());
			plots.back()->SetYTitle(yLabel.c_str());
			plots.back()->SetZTitle(zLabel.c_str());
			plots.back()->SetOption("COLZ");
			title = "";
		}

		//Loop over hits in cluster, each new cluster gets a different weight
		//and hence a different colour
		for(j = i->get_firstHit(); j != i->get_endOfHits(); ++j){

			plots.back()->Fill(j->get_col(), j->get_row(), counter);
		}
		counter++;
	}

	return plots;
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

void Plot::print(TH2F* myTH2F, std::string path){

	std::string title = myTH2F->GetTitle();

	std::string filenameRoot = path + title + ".root";
	std::string filenameEps = path + title + ".eps";
	std::string filenamePng = path + title + ".png";

	TCanvas* c1 = new TCanvas( title.c_str(), title.c_str() );

	myTH2F->Draw();
	c1->Update();

	c1->Print(filenameRoot.c_str());
	c1->Print(filenameEps.c_str());	
	c1->Print(filenamePng.c_str());
}

