#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <bitset>
#include <cstdlib>
#include <string>

using namespace std;

//branch for data structure elements that holds the address and the state
struct branch{
	unsigned long long addr;
	unsigned int state; //1 (taken) or 0 (not taken)
};

class Predictor{
	public:
        Predictor();
		void processInput(string inputFile);
		void alwaysTaken();
		void alwaysNotTaken();
		void bimodalPredictorSingleBit(int tableSize);
		void bimodalPredictorTwoBits(int tableSize);
		void gsharePredictor(int ghrBits);
		void tournament();
		void processOutput(string outputFile);
	private: //vectors chosen since they grow dynamically and we dont know how many branches there could be
		unsigned int totalBranches; //keep track of total number of branches
		vector<branch> branches; //data structure to be populated and traversed
		vector<unsigned int> predictions; //data structutre to hold number of correct predictions per predictor
};
#endif
