#include <string>
#include <vector>
#include "IBP.h"


using namespace std;

IBP:: IBP(){}

IBP:: IBP(int block_size){
    this->block_num = -1;
    this->dbps = vector<int>(block_size/4, -1);
    for(int i = 0; i < block_size/4; i++){
        this->dbps[i] = -1;
    }
}

IBP:: IBP(int block_num, int block_size){
    this->block_num = block_num;
    this->block_size = block_size;
    this->dbps = vector<int>(block_size/4, -1);
}

int IBP:: getBlockNum(){
    return this->block_num;
}

vector<int> IBP::getDBPS(){
    return this->dbps;
}

void IBP:: setDBP(int index, int val){
    this->dbps[index] = val;
}
