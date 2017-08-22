#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "Predictor.h"

using namespace std;

//constructor
Predictor::Predictor() {
    totalBranches = 0;
}

/** Processes the input file and populate the vector branches
 * @params inputFile - the name of the input file to process
 */
void Predictor::processInput(string inputFile){
    string behavior, line;
    ifstream infile(inputFile.c_str());
    
    while(getline(infile, line)){
        stringstream ss(line);
        branch tmp;
        totalBranches++;
        ss >> hex >> tmp.addr >> behavior;
        cout << tmp.addr << endl;
        
        if(behavior == "T") {
            tmp.state = 1;
        } else{
            tmp.state = 0;
        }
        
        branches.push_back(tmp);
        
    }
    
    infile.close();

}

/** always taken predictor just counts the number of taken branches as the prediction
 */
void Predictor::alwaysTaken(){
	unsigned int takenCount = 0;
	for(unsigned int i = 0; i < branches.size(); i++){
		if(branches[i].state == 1)
			takenCount++;
	}
	

	predictions.push_back(takenCount);
}

/** always taken predictor just counts the number of taken branches as the prediction
 */
void Predictor::alwaysNotTaken(){
	unsigned int notTakenCount = 0;
	for(unsigned int i = 0; i < branches.size(); i++){
		if(branches[i].state == 0)
			notTakenCount++;
	}


	predictions.push_back(notTakenCount);
}

/**
 * the bimodal single bit predictor, that indexes into the prediction 
 * counter table by address mod table size and records past
 * branch values
 * @params tableSize - 16, 32, 128, 256, 512, 1024, 2048
 */
void Predictor::bimodalPredictorSingleBit(int tableSize){
	unsigned int correctPredictions = 0;
	vector<unsigned int> predictorTable(tableSize, 1); //initial state of all prediction counters is taken

	for(unsigned int i = 0; i < branches.size(); i++){
		int index;
		index = branches[i].addr % tableSize; //always mod with table size
		
        if(predictorTable[index] == branches[i].state) {
			correctPredictions++;
        } else {
			predictorTable[index] = branches[i].state; //update table
        }
	}

	predictions.push_back(correctPredictions);
}

/**
 * the bimodal two bit predictor, that indexes into the prediction
 * counter table by address mod table size and records past
 * branch values as such:
 * strongly not taken = 00 -> 0
 * not taken = 01 -> 1
 * taken = 10 -> 2
 * strongly taken = 11 -> 3
 * @params tableSize - 16, 32, 128, 256, 512, 1024, 2048
 */
void Predictor::bimodalPredictorTwoBits(int tableSize){
	vector<unsigned int> predictorTable(tableSize, 3); //set all prediction counters to strongly taken
    unsigned int correctPredictions = 0;
    
	for(unsigned int i = 0; i < branches.size(); i++){
        int index;
		index = branches[i].addr % tableSize;
		unsigned int st = predictorTable[index];
		
		if((branches[i].state << 1) == (st & 2)){
			correctPredictions++;
		}
	
		if(branches[i].state == 1){
			
            if(st != 3) {st++;}
	
		}else{
		
            if(st != 0) {st--;}
		}
		
        predictorTable[index] = st;
		
        }
    
        predictions.push_back(correctPredictions);
}

/**
 * the gshare predictor, that indexes into the prediction
 * counter table by XORing with the global history bits
 * branch values as such:
 * strongly not taken = 00 -> 0
 * not taken = 01 -> 1
 * taken = 10 -> 2
 * strongly taken = 11 -> 3
 * @params ghrbits - bit history from 3 to 11
 */
void Predictor::gsharePredictor(int ghrBits){
    unsigned long long correctPrediction = 0;
    int tableSize = 2048;
    unsigned long long ghr = 0; //global history register
	unsigned int ghrSize = (int) pow(2, ghrBits) - 1; //glbal history register size
	vector<unsigned int> predictorTable(tableSize, 3);

	for(unsigned int i = 0; i < branches.size(); i++){
		//PC is XORed
		int index = (branches[i].addr ^ (ghr & ghrSize)) % tableSize;

		unsigned int st = predictorTable[index];
		//update state
		if((branches[i].state << 1) == (st &2))
			correctPrediction++;
		//taken
		if(branches[i].state == 1){
			//not strongly Taken
			if(st != 3)
				st++;
		//not Taken
		}else{
			//not strongly Not Taken
			if(st != 0)
				st--;
		}
		
		ghr <<= 1;
		ghr |= branches[i].state; //update global history reg
		predictorTable[index] = st;
	}

	
	predictions.push_back(correctPrediction);
}

/**
 * the tournament predictor, that indexes into the prediction
 * counter table by XORing with the global history bits
 * branch values as such:
 * prefer bimodal = 00 -> 0
 * weakly prefer bimodal = 01 -> 1
 * weakly prefer gshare = 10 -> 2
 * prefer gshare = 11 -> 3
 * @params ghrbits - bit history from 3 to 11
 */
void Predictor::tournament(){
    int tableSize = 2048;
	unsigned long long correctPrediction = 0;
	unsigned int ghrSize = (int) pow(2, 11) -1; //11 bits of global history
	unsigned long long ghr = 0; //global history register
    
    vector<unsigned int> gshareCounter (tableSize, 3);
	vector<unsigned int> bimodalCounter (tableSize, 3);
	vector<unsigned int> tournamentCounter (tableSize, 3);
    
	for(unsigned int i = 0; i < branches.size(); i++){
        
        //tournament and bimodal are moduloed to index into the table
		int tournamentIndex = branches[i].addr % tableSize;
		int bimodalIndex = branches[i].addr % tableSize;
		int gshareIndex = (branches[i].addr ^ (ghr & ghrSize)) % tableSize; //gshare index stil XORed
        
		unsigned int bimodalState = bimodalCounter[bimodalIndex];	
		unsigned int gshareState = gshareCounter[gshareIndex];
		unsigned int tournamentState = tournamentCounter[tournamentIndex];
		
        //2nd least significant bit determines the prediction
		unsigned int bimodalPredictedValue = bimodalState & 2;
		unsigned int gsharePredictedValue = gshareState & 2;
	
		//taken branch for both bimodal and share
		if(branches[i].state == 1){
			//not in strongly taken for both
			if(gshareState != 3)
				gshareState++;
			if(bimodalState != 3)
				bimodalState++;
		//branch is not taken
		}else{
			//not in strongly not taken for both
			if(gshareState != 0)
				gshareState--;
			if(bimodalState != 0)
				bimodalState--;
		}
        
		//update global history register
		ghr <<= 1;
		ghr |= branches[i].state;
        
		gshareCounter[gshareIndex] = gshareState;
		bimodalCounter[bimodalIndex] = bimodalState;
		
		if(gsharePredictedValue == bimodalPredictedValue){
			if((branches[i].state << 1) == gsharePredictedValue){
				correctPrediction++;
			}
		}
		else{
			//taking gshare prediction
			if((tournamentState & 2) == 2){
				//gshare prediction is correct
				if((branches[i].state << 1) == gsharePredictedValue){
					correctPrediction++;
					
					if(tournamentState != 3)
						tournamentState++;
				}
				//gshare prediction is incorrect
				else{
					if(tournamentState != 0)
						tournamentState--;
				}
			}
			//taking bimodal prediction
			else{
				//bimodal prediction is correct
				if((branches[i].state << 1)== bimodalPredictedValue){
					correctPrediction++;
					if(tournamentState != 0)
						tournamentState--;
				}
				//bimodal prediction is incorrect
				else{
					if(tournamentState != 3)
						tournamentState++;
				}
			}
		}
		tournamentCounter[tournamentIndex] = tournamentState;
	}


	predictions.push_back(correctPrediction);
}

/**
 * writing to the output file the same format as specified in the descriptio
 * parses the input at certain locations so the file prints a new line
 * at the results of each new predictor
 * @param outputFile - the file to write the results to.
 */
void Predictor::processOutput(string outputFile){
	ofstream outFile(outputFile.c_str());
	
	for(unsigned int i = 0; i < predictions.size(); i++){
        if (i < 2 || i == 8 || i == 15 || i ==24){
            outFile << predictions[i] << "," << totalBranches << ";" << endl; //is putting the two spaces
        } else {
            outFile << predictions[i] << "," << totalBranches << "; ";
        }
        
	}
}
