#include <fstream>
#include <algorithm>    
#include <vector>       
#include <ctime>        
#include <cstdlib>  
#include <cmath>
#include <stdio.h> 
#include <stdlib.h>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <iterator>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	FILE *fp=fopen("myfile", "w");
    ftruncate(fileno(fp), 1024);
    fclose(fp);
    
    long int num_blocks = 1024;
    int block_size = 128;
    string s = to_string(num_blocks) + '\n' + to_string(block_size) + '\n';
    
    
    FILE *cont;
    cont = fopen("myfile", "r+");
    fseek(cont, 0, SEEK_SET);
    fputs(s.c_str(), cont);
    fclose(cont);
}

void read(string filename, int start_byte, int num_bytes){
int i, j;
	File fileToDisplay;
	vector<File> files = disk.getFiles();
	for (i = 0; i < 256; i++){
		if (files[i].getFilename() == filename){
			fileToDisplay = files[i];
			break;
		}
	}
	
	if (i == 256){
		cout << "File does not exist" << endl;
		return;
	}
	char readDataBuffer[1];
	string fileData;
	
	ifstream fin(disk.diskname,ifstream::binary); 
	if(fin.is_open()) 
	{
		int seek_position;
		int limit;
		for(int x = 0; x < 12; x++){
			//no data to read
			if(fileToDisplay.dbps[x] == -1){
				break;
			}else {
				seek_position = (fileToDisplay.dbps[x]*disk.block_size)+(257*disk.block_size);
				limit = (fileToDisplay.dbps[x]*disk.block_size)+(257*disk.block_size) + disk.block_size;
		//		cout << fileToDisplay.dbps[x] << " ";
				fin.seekg(seek_position, ios::beg);
				while (fin.tellg() != limit && readDataBuffer != '\0'){
					fin.get(readDataBuffer[0]);
					if (readDataBuffer[0] != '\0'){
						fileData.push_back( readDataBuffer[0]);
					} else {
						break;
					}
				}
					
			}
		}
//		cout << endl;
		for(int x = 0; x < fileToDisplay.ibp_num->dbps.size(); x++){
			//if -1, that means its empty and thus no data left just break
		if (fileToDisplay.ibp_num->block_num == -1 || fileToDisplay.ibp_num->dbps[x] == -1){ 
			break;
		} else {
			seek_position = (fileToDisplay.ibp_num->dbps[x]*disk.block_size)+(257*disk.block_size);
			limit = (fileToDisplay.ibp_num->dbps[x]*disk.block_size)+(257*disk.block_size) + disk.block_size;
		//	cout << fileToDisplay.ibp_num->dbps[x] << endl;
			fin.seekg(seek_position, ios::beg);
			while(fin.tellg() != limit && readDataBuffer[0] != '\0'){
				fin.get(readDataBuffer[0]);
				if (readDataBuffer[0] != '\0'){
						fileData.push_back( readDataBuffer[0]);
					} else {
						break;
					}
				}
			}
		}
		
//		cout << endl;
		
		for(int x = 0; x < fileToDisplay.dibp_num->ibps.size(); x++){
		//check if dibp initialized
		if(fileToDisplay.dibp_num->block_num == -1){
			break;
		} else {
			for( int k = 0; k < fileToDisplay.dibp_num->ibps[x]->dbps.size(); k++){
				//check if ibps is initialized
				if(fileToDisplay.dibp_num->ibps[x]->block_num == -1 || fileToDisplay.dibp_num->ibps[x]->dbps[k] == -1){
					break;
				} else {
					seek_position = (fileToDisplay.dibp_num->ibps[x]->dbps[k]*disk.block_size)+(257*disk.block_size);
					limit = (fileToDisplay.dibp_num->ibps[x]->dbps[k]*disk.block_size)+(257*disk.block_size)+disk.block_size;
					fin.seekg(seek_position, ios::beg);
					while(fin.tellg() != limit && readDataBuffer[0] != '\0'){
						fin.get(readDataBuffer[0]);
						if (readDataBuffer[0] != '\0'){
								fileData.push_back( readDataBuffer[0]);
							} else {
								break;
							}
						}
					}
				}
			}
		}
		for(int i = start_byte-1; i < start_byte + num_bytes-1; i++){
	    cout << fileData[i] << endl;
	}
//	cout << endl;	
	}
	else //file could not be opened
	{
		cout << "File could not be opened." << endl;
	}
	
	
	
}