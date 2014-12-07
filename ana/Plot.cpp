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


std::list<TH1F*> Plot::clusterSize(ClusterContainer* myClusters){

	std::list<TH1F*> sizePlots;
	ClusterContainer::iterator i;
	TH1F* sizeHist;
	TH1F* lengthHist;
	TH1F* widthHist;

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
	lengthHist = new TH1F("Cluster_length","Cluster_length", nBins, (double)smallest, (double)largest);
	widthHist = new TH1F("Cluster_width","Cluster_width", nBins, (double)smallest, (double)largest);
	
	//Fill
	for(i = myClusters->begin(); i!= myClusters->end(); ++i){
		sizeHist->Fill(i->get_size());
		lengthHist->Fill(i->get_length());
		widthHist->Fill(i->get_width());
	}

	//Add labels
	sizeHist->SetXTitle("Cluster size [pixels]");
	sizeHist->SetYTitle("# of clusters");
	sizeHist->SetFillColor(cadetBlue);
	sizeHist->SetOption("TEXT00HIST");

	lengthHist->SetXTitle("Cluster length [pixels along row]");
	lengthHist->SetYTitle("# of clusters");
	lengthHist->SetFillColor(chatreuse);
	lengthHist->SetOption("TEXT00HIST");
	
	widthHist->SetXTitle("Cluster width [pixels along column]");
	widthHist->SetYTitle("# of clusters");
	widthHist->SetFillColor(deepSkyBlue);
	widthHist->SetOption("TEXT00HIST");
	
	//Add plots to list
	sizePlots.push_back(sizeHist);
	sizePlots.push_back(lengthHist);
	sizePlots.push_back(widthHist);

	return sizePlots;

}

TH1F* Plot::clusterToT(ClusterContainer* myClusters){

	ClusterContainer::iterator i;
	TH1F* totHist;

	int smallest(1), largest(100);
	int nBins = (largest-smallest)+1; //To ensure any rounding down is taken care of 

	//Initialise th1
	totHist = new TH1F("Cluster_tot","Cluster_tot", nBins, (double)smallest, (double)largest);

	//Fill
	for(i = myClusters->begin(); i!= myClusters->end(); ++i)
		totHist->Fill(i->get_totalToT());

	//Add labels
	totHist->SetXTitle("Cluster tot [bc]");
	totHist->SetYTitle("# of clusters");
	totHist->SetFillColor(turquoise);
	totHist->SetOption("HIST");

	return totHist;

}

std::pair<TH1F*,TH1F*> Plot::centreOfCharge(ClusterContainer* myClusters){

	ClusterContainer::iterator i;
	TH1F* cofcHistx;
	TH1F* cofcHisty;
	std::pair<TH1F*,TH1F*> histPair;
	std::pair<double, double> temp;

	int smallest(1), largest(100);
	int nBins = ((largest-smallest)+1)/5; //To ensure any rounding down is taken care of 

	//Initialise th1
	cofcHistx = new TH1F("Centre_of_charge_col","Centre_of_charge_col", nBins, (double)smallest, (double)largest);
	cofcHisty = new TH1F("Centre_of_charge_row","Centre_of_charge_row", nBins, (double)smallest, (double)largest);

	//Fill
	for(i = myClusters->begin(); i!= myClusters->end(); ++i){
		temp = i->get_centreOfCharge();
		cofcHistx->Fill(temp.first);
		cofcHisty->Fill(temp.second);
	}

	//Add labels
	cofcHistx->SetXTitle("Centre of charge [\% of size]");
	cofcHistx->SetYTitle("# of clusters");
	cofcHisty->SetXTitle("Centre of charge [\% of size]");
	cofcHisty->SetYTitle("# of clusters");

	cofcHistx->SetFillColor(blueViolet);
	cofcHisty->SetFillColor(orange);
	cofcHistx->SetOption("HIST");
	cofcHisty->SetOption("HIST");

	histPair.first = cofcHistx;
	histPair.second = cofcHisty;
	return histPair;

}



std::map<unsigned,TH2F*> Plot::eventClusters(ClusterContainer* myClusters){

	std::map<unsigned,TH2F*> plots;
	std::map<unsigned,unsigned> weight;
	ClusterContainer::iterator i;
	std::list<Hit>::iterator j;
	std::stringstream ss;

	unsigned lv1id(-1), current_lv1id(-1), counter(1);
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
			
			current_lv1id = lv1id;
			
			//See if the event exists
			if(plots.find(lv1id) == plots.end()){
				
				weight.insert(std::pair<unsigned,unsigned>(lv1id,1));
				ss << current_lv1id;
				title = base + ss.str();
				//Clear ss
				ss.str("");

				plots.insert(std::pair<unsigned,TH2F*>(lv1id, new TH2F(title.c_str(), title.c_str(), nCols, min, nCols, nRows, min, nRows)));

				plots[lv1id]->SetXTitle(xLabel.c_str());
				plots[lv1id]->SetYTitle(yLabel.c_str());
				plots[lv1id]->SetZTitle(zLabel.c_str());
				plots[lv1id]->SetOption("COLZ");
				title = "";
			} else {
				weight[lv1id] += 1;
			}
		}

		counter = weight[lv1id];
		//Loop over hits in cluster, each new cluster gets a different weight
		//and hence a different colour
		for(j = i->get_firstHit(); j != i->get_endOfHits(); ++j){

			plots[lv1id]->Fill(j->get_col(), j->get_row(), counter);
		}
		counter++;
	}

	return plots;
}

std::map<unsigned,TH2F*> Plot::eventToT(ClusterContainer* myClusters){

	std::map<unsigned,TH2F*> plots;
	ClusterContainer::iterator i;
	std::list<Hit>::iterator j;
	std::stringstream ss;

	unsigned lv1id(-1), current_lv1id(-1), counter(1);
	std::string base = "eventToT_";
	std::string title = "";
	std::string xLabel = "Column [pixel]";
	std::string yLabel = "Row [Pixel]";
	std::string zLabel = "ToT";

	for(i = myClusters->begin(); i != myClusters->end(); ++i){
		//Get the event associated with this cluster
		lv1id = i->get_lv1id();

		//If this is a new event, start a new hist
		if(lv1id != current_lv1id){
			
			current_lv1id = lv1id;
			
			//See if the event exists: if not add it to plots
			if(plots.find(lv1id) == plots.end()){
				
				ss << current_lv1id;
				title = base + ss.str();
				//Clear ss
				ss.str("");

				plots.insert(std::pair<unsigned,TH2F*>(lv1id, new TH2F(title.c_str(), title.c_str(), nCols, min, nCols, nRows, min, nRows)));

				plots[lv1id]->SetXTitle(xLabel.c_str());
				plots[lv1id]->SetYTitle(yLabel.c_str());
				plots[lv1id]->SetZTitle(zLabel.c_str());
				plots[lv1id]->SetOption("COLZ");
				title = "";
			} 
		}

		//Loop over hits in cluster, each new cluster gets a different weight
		//and hence a different colour
		for(j = i->get_firstHit(); j != i->get_endOfHits(); ++j)
			plots[lv1id]->Fill(j->get_col(), j->get_row(),j->get_tot());	
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

