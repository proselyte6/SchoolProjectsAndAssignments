#include "Predictor.h"

using namespace std;

int main(int argc, char **argv){
    
	if(argc != 3){
		cout << "ERROR! Wrong format of arguments!" << endl;
		exit(1);
	}

	
	int tableSizes[] = {16, 32, 128, 256, 512, 1024, 2048};
	
	Predictor p;
	p.processInput(argv[1]); //parses input file and populates data structure
	
	/**p.alwaysTaken();
	p.alwaysNotTaken();

    //bimodal predictor single bit for all table sizes
	for(int i = 0; i < 7; i++){
		p.bimodalPredictorSingleBit(tableSizes[i]);
	}

    //bimodal predictor two bits for all table sizes
	for(int i = 0; i < 7; i++){
		p.bimodalPredictorTwoBits(tableSizes[i]);
	}

    //gshare predictor with history length of 3 to 11 bits
	for(int i = 3; i <= 11; i++){
		p.gsharePredictor(i);
	}
	
	p.tournament();
	
	p.processOutput(argv[2]); //writes the results to the output file
     */
    
	return 0;
}
