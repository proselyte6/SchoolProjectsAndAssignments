#include <string>
#include <vector>
#include "Block.h"

using namespace std;

Block:: Block();

Block:: Block(int block_num, int block_size){
    this->block_num = block_num;
    this->block_size = block_size;
}

int Block::getBlockNum(){
    return this->block_num;
}

void Block:: addByte(char byte){
    this->bytes.push_back(byte);
}

bool Block:: full(){
    if(this->bytes.size() >= this->block_size){
        return true;
    }
    else{
        return false;
    }
}

void Block:: overwriteByte(int index, char byte){
    this->bytes[index] = byte;
}

vector<char> getBytes(){
    return this->bytes();
}