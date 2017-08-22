#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>    
#include <vector>       
#include <ctime>        
#include <cstdlib>  
#include <cmath>
#include <stdio.h> 
#include <stdlib.h>
#include <map>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <iterator>
#include <sstream>
#include <pthread.h>
#include <queue>
#include "timer.h"
#include "File.h"
#include "Disk.h"
#include "DIBP.h"
#include "IBP.h"


using namespace std;

int ssfs(int argc, char *argv[]);
long int fileSize(string fileName);

bool create(string filename);
void import(string filename, string unixname);
void cat(string filename);
void del(string filename);
void file_write(string filename, char character, int byte, int num_bytes);
void read(string filename, int start_byte, int num_bytes);
void shutdown();
void list();
void disk_write();
void disk_init(string filename);
void put(string value);
string get();
void *producer(void* numbers);
void consumer();


long int DISK_SIZE;
Disk disk;
std::queue<string> buffer;
pthread_cond_t full;
pthread_mutex_t mutex, addThread;
int numproducers = -1;
vector<string> threadFiles;
const char * filename;
bool toShutdown = false;

int main(int argc, char *argv[]){
	string filepath = argv[0];
	string input, command;
	if(filepath.find("ssfs_mkdsk") != std::string::npos){
		string diskname;
		long int num_blocks = atol(argv[1]);
		int block_size = atoi(argv[2]);
		
		if(block_size < 128 || block_size > 512 || num_blocks < 1024 || num_blocks > 128000){
			cerr << "Too big or small of a size for num_blocks and/or block_size. Please try again." << endl;
			return 1;
		}
		else if(block_size%2 == 1 || num_blocks%2 == 1){
			cerr << "The block size or number of blocks specified is not a power of 2. Please try again." << endl;
		}
		
		if(argc == 3){
			diskname = "DISK";
		}
		else if(argc == 4){
			diskname = argv[3];
		}
		
		
		
		DISK_SIZE = num_blocks * block_size;
		//cout << DISK_SIZE << endl;
		FILE *fp = fopen(diskname.c_str(), "w");
		ftruncate(fileno(fp), num_blocks * block_size);
		fclose(fp);
		
//		string s = to_string(num_blocks) + " " + to_string(block_size) + '\n'; 
		string s = " ";
		FILE *cont;
		cont = fopen(diskname.c_str(), "r+");
		
		for(int i = 0; i < num_blocks*block_size;i++){
			fseek(cont, i, SEEK_SET);
			fputs(s.c_str(), cont);
		}
		
		fclose(cont);
		
		
		disk = Disk(diskname, num_blocks, block_size);
		for(int i = 0; i < 256; i++){
			disk.files[i] = File(block_size);
		}
		
		disk_write();
		
	    //ofstream outfile;
		//outfile.open((diskname).c_str(), std::ios::app);
		//outfile << num_blocks << endl << block_size << endl;
		//outfile.close(); 
		//DISK_SIZE = DISK_SIZE - fileSize(diskname.c_str());
		//cout << DISK_SIZE << endl;
	
		return 0;
	}
	else{
		return ssfs(argc, argv);
	}
	
	
}

void put(string value){
	buffer.push(value);
}

string get() {
	if (buffer.empty() == false) {
		string atFront = buffer.front();
		buffer.pop();
		return atFront;
	} else {
		return NULL;
	}
}

//Thread
//Using queue, no max buffer
void *producer(void* numbers) {
	ifstream fp;
	string process;
//	cout << "Got here 3" << endl;
	//const char* const nameFile = static_cast<const char* const>(fileName);
	pthread_mutex_lock(&addThread);
//	cout << "Got here 5" << endl;
	fp.open(threadFiles.back());
//	cout << "Got here 6" << endl;
	if (fp.is_open() == true) {
		
		threadFiles.pop_back();
		pthread_mutex_unlock(&addThread);
		while (!fp.eof()) {
			pthread_mutex_lock(&mutex);
			getline(fp, process);
			if(process != ""){
				put(process);
			}
			pthread_cond_signal(&full);
			pthread_mutex_unlock(&mutex);
		}
	} else {
		cerr << "file did not open" << endl;
		pthread_mutex_unlock(&addThread);
	}
//	cout << "File closing" << endl;
	fp.close();
//	cout << "Got here 4" << endl;
}

void shutdown() {
	//Check to see if this is last command in buffer.
	//Otherwise, ignore (because producer thread closes once it writes it's entire contents to buffer)
	//If it is last command in buffer write to disk
//	cout << "got to shutdown" << endl;
	if (buffer.empty()) {
		disk_write();
		exit(0);
	} else {
		toShutdown = true;
	}
}

//Disk Controller
void consumer() {
	string process;
	string current;
	pthread_mutex_lock(&mutex);
	while (buffer.empty()) {
		pthread_cond_wait(&full, &mutex);
	}
	//gets command from front of queue
	current = get();
	cout << current << endl;
	//SENDS VALUE OF CURRENT TO DISK AND PROCESS IT. Parse current
	istringstream  ss(current);
	vector<string> parts;
	string tmp;
	
	while( ss >> tmp){
		parts.push_back(tmp);
	}
	
	if(parts[0] == "CREATE"){
//		cout << "Got to CREATE" << endl;
		create(parts[1]);
	} else if(parts[0] == "IMPORT"){
		import(parts[1], parts[2]);
	} else if(parts[0] == "CAT"){
		cat(parts[1]);
	} else if(parts[0] == "DELETE"){
		del(parts[1]);
	} else if(parts[0] == "WRITE"){
		char x = parts[2][0];
		file_write(parts[1], x, atoi(parts[3].c_str()), atoi(parts[4].c_str()));
	} else if(parts[0] == "READ"){
		read(parts[1],atoi(parts[2].c_str()),atoi(parts[3].c_str()));
	} else if (parts[0] == "LIST"){
		list();
	} else if (parts[0] == "SHUTDOWN"){
		shutdown();
	}
	pthread_mutex_unlock(&mutex);
}



int ssfs(int argc, char *argv[]){
	
	
	
	//vector<DiskOpThread> dots;

	string disk_file_name;
//	vector<string> threadFiles;
	
	if(argc <= 2 || argc > 6){
		cerr << "Wrong Number of arguments!" << endl;
		return 1;
	}
	disk_file_name = argv[1];
	
	disk_init(disk_file_name);
	
	
//	cout << "Got here" << endl;
	
	for(int i = 2; i < argc; i++){
		//create vector of threads
		threadFiles.push_back(argv[i]);
	}
//	cout << "Got here 1" << endl;
	
	string *myThread;
	pthread_t *p;
	if(argc == 3){
		//Make 1 consumer thread and 1 producer thread
		numproducers = 1;
		p= new pthread_t[numproducers];
		pthread_create(&p[0], NULL, producer, myThread);
		
		pthread_join(p[0], NULL);
	}
	else if(argc == 4){
		//Make 1 consumer thread and 2 producer threads
		numproducers = 2;
		p = new pthread_t[numproducers];
		pthread_create(&p[0], NULL, producer, myThread);
		pthread_create(&p[1], NULL, producer, myThread);
		
		pthread_join(p[0], NULL);
		pthread_join(p[1], NULL);
	}
	else if(argc == 5){
		//Make 1 consumer thread and 3 producer threads
		numproducers = 3;
		p = new pthread_t[numproducers];
		pthread_create(&p[0], NULL, producer, myThread);
		pthread_create(&p[1], NULL, producer, myThread);
		pthread_create(&p[2], NULL, producer, myThread);
		
		pthread_join(p[0], NULL);
		pthread_join(p[1], NULL);
		pthread_join(p[2], NULL);
	}
	else{
		//Make 1 consumer thread and 4 producer threads
		numproducers = 4;
		p = new pthread_t[numproducers];
		pthread_create(&p[0], NULL, producer, myThread);
		pthread_create(&p[1], NULL, producer, myThread);
		pthread_create(&p[2], NULL, producer, myThread);
		pthread_create(&p[3], NULL, producer, myThread);
		
		pthread_join(p[0], NULL);
		pthread_join(p[1], NULL);
		pthread_join(p[2], NULL);
		pthread_join(p[3], NULL);
	}
/*
	for (int i = 0; i < numproducers; i++) {
		pthread_join(p[i], NULL);
	}*/
	
	string current;
	
	while(true) {
		consumer();
		if (buffer.empty() && toShutdown == false) {
			cerr << "Exited Abnormally" << endl;
			exit(1);
		} else if (buffer.empty() && toShutdown == true) {
			shutdown();
		}
	}
	
	return 0;
}	

long int fileSize(string fileName){
	streampos begin,end;
  ifstream myfile (fileName.c_str(), ios::binary);
  begin = myfile.tellg();
  myfile.seekg (0, ios::end);
  end = myfile.tellg();
  myfile.close();
  long int size = end - begin;
  return size;
}


bool create(string filename){
	int i;
//	cout << "Creating " << filename << endl;
	vector<File> files = disk.getFiles();
	vector<bool> free_inodes = disk.getFreeInodes();
	for(i = 0; i < 256; i++){
		if(files[i].getFilename() == filename){
			cout << "This filename is already used. Please try again." << endl;
			return false;
		}
	}
	for(i = 0; i < 256;i++){
		if(free_inodes[i] == true){
			break;
		}
	}
	if(i == 256){
		cout << "there is already 256 files on this disk. Please delete some." << endl;
		return false;
	}
	
/**
	for(i = 0; i < 12; i++){
		int j = 0;
		while(disk.getFreeBlocks()[i] == false){
			j++;
		}
		disk.setFree(j, false);
	} **/

	int file_num;
	for(i = 0; i < 256; i++){
		if(free_inodes[i] == true){
			disk.setInode(i, File(filename, disk.getBlockSize(), i));
			file_num = i;
			break;
		}
	}
	
//	cout << filename << " creation done" << endl;
	
	return true;
	
/**	for(i = 0; i < 12; i++){
		int j = 0;
		while(disk.getFreeBlocks()[i] == false){
			j++;
		}
		disk.setDBP(file_num, i, j);
		disk.setFree(j, false);
	}**/
	
	
	
}

void list(){
	vector<File> files = disk.getFiles();
//	cout << files[0].filename << endl;
	vector<bool> free_inodes = disk.getFreeInodes();
	int numfiles = 0;
	bool foundone = false;
	for(int i = 0; i < 256; i++){
		if(free_inodes[i] == false){
			cout << files[i].getFilename() << " " << files[i].getSize() << endl;
			numfiles++;
			foundone = true;
		}
	}
	if(foundone == false){
		cout << "There are no files" << endl;
	}
	else{
		cout << "Number of files: " << numfiles << endl;
	}
	
//	cout << "List done" << endl;
}

void del(string filename){
	int i;
//	cout << "Beginning of delete" << endl;
	File deleteFile;
	vector<File> files = disk.getFiles();
	for (i = 0; i < 256; i++){
		if (files[i].getFilename() == filename){
			deleteFile = files[i];
			break;
		}
	}
	
	if (i == 256){
		cout << "File does not exist" << endl;
		return;
	}
	
	int fileNum = i;
	int inode_block_to_free = files[i].inode_block;
	
//	cout << fileNum << " " << inode_block_to_free << endl;
	
//	cout << "got here 1" << endl;
	
	//set the direct blocks as free
	for(i = 0; i < 12; i++){
		if(files[fileNum].dbps[i] != -1){
			disk.setFree(files[fileNum].dbps[i] , true);
		}
	}
	
	//free the inode number
	disk.setFreeInode(inode_block_to_free, true);
	
//	cout << "got here 2" << endl;
//	cout << files[fileNum].ibp_num->block_num << endl;
	//free indirect blocks
	if(files[fileNum].ibp_num->block_num != -1){
//		cout << "Got in here" << endl;
		disk.setFree(files[fileNum].ibp_num->block_num, true);
		for( int x = 0; x <  files[fileNum].ibp_num->dbps.size(); x++){
//			cout << "Got in here 2" << endl;
			if(files[fileNum].ibp_num->dbps[x] != -1){
				disk.setFree(x, true);
			}
		}
	}

	
//	cout << "got here 3" << endl;
	
	//free double indirect blocks
	if(files[fileNum].dibp_num->block_num != -1){
		disk.setFree(files[fileNum].dibp_num->block_num, true);
	}
	vector<int> dbps;
	for(int k = 0; k < files[fileNum].dibp_num->ibps.size();k++){
		dbps.insert(dbps.end(), files[fileNum].dibp_num->ibps[k]->dbps.begin(), files[fileNum].dibp_num->ibps[k]->dbps.end());
		for(int g = 0; g < dbps.size(); g++){
			if(dbps[g] != -1){
				disk.setFree(dbps[g], true);
			}
		}
		if(files[fileNum].dibp_num->ibps[k]->block_num != -1){
			disk.setFree(files[fileNum].dibp_num->ibps[k]->block_num, true);
		}
	}
	
//	cout << "got here 4" << endl;
	
	for(int x: dbps){
		if (x != -1) {
			disk.setFree(x, true);
		}
	}
	
	FILE *cont;
	cont = fopen(disk.diskname.c_str(), "r+");
	string replace = string(disk.block_size, ' ');
	
//	cout << "got here 4.5" << endl;
	
	//delete all dbp data
	for(int x = 0; x < 12; x++){
		if(deleteFile.dbps[x] == -1){ //if -1, that means its empty and thus no data left just break
			break;
		} else {
			fseek(cont, (deleteFile.dbps[x]*disk.block_size)+(256*disk.block_size) ,SEEK_SET);
			fputs(replace.c_str(), cont);
		}
	}
	
//	cout << "got here 5" << endl;
	
	//delete all ibp data
	for(int x= 0; x < deleteFile.ibp_num->dbps.size(); x++){
		//if -1, that means its empty and thus no data left just break
		if (deleteFile.ibp_num->block_num == -1 || deleteFile.ibp_num->dbps[x] == -1){ 
			break;
		} else {
				fseek(cont, (deleteFile.ibp_num->dbps[x]*disk.block_size)+(256*disk.block_size) ,SEEK_SET);
				fputs(replace.c_str(), cont);
		}
	}
	
//	cout << "got here 6" << endl;
	
	//delete all dibp
	for(int x = 0; x < deleteFile.dibp_num->ibps.size(); x++){
		//check if dibp initialized
		if(deleteFile.dibp_num->block_num == -1){
			break;
		} else {
			for( int k = 0; k < deleteFile.dibp_num->ibps[x]->dbps.size(); k++){
				//check if ibps is initialized
				if(deleteFile.dibp_num->ibps[x]->block_num == -1){
					break;
				} else {
					//check if dbps is initialized
					if (deleteFile.dibp_num->ibps[x]->dbps[k] == -1){
						break;
					} else {
						fseek(cont, (deleteFile.dibp_num->ibps[x]->dbps[k]*disk.block_size)+(256*disk.block_size) ,SEEK_SET);
						fputs(replace.c_str(), cont);
					}
				}
			}
		}
		
	}
	
//	cout << "got here 7" << endl;
	
	fclose(cont);

	//delete the file
	disk.deleteFile(fileNum, disk.block_size);
	disk.files[fileNum] = File(disk.block_size);
	disk.free_inodes[fileNum] = true;
//	cout << "End of delete file" << endl;
	
	
}



void cat(string filename){
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
						cout << readDataBuffer[0];
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
						cout << readDataBuffer[0];
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
								cout << readDataBuffer[0];
							} else {
								break;
							}
						}
					}
				}
			}
		}
	cout << endl;	
	}
	else //file could not be opened
	{
		cout << "File could not be opened." << endl;
	}
	
}



void disk_write(){
	int i,j,p;
	FILE *cont;
    cont = fopen(disk.diskname.c_str(), "r+");
	
//	cout << disk.num_blocks << endl;
	
	//Writing the disk info block
	fseek(cont, 0, SEEK_SET);
//	fputs((disk.diskname+" "+to_string(disk.block_size)+" "+to_string(disk.num_blocks)).c_str(), cont);
	fputs((to_string(disk.block_size)+" "+to_string(disk.num_blocks)).c_str(), cont);
	
	//Writing inode info
	for(i = 0; i < disk.files.size(); i++){
//		cout << disk.files[i].ibp_num->getBlockNum() << endl;
		string writer = to_string(disk.files[i].inode_block)+" "+disk.files[i].filename+" "+to_string(disk.files[i].filesize)+" ";
		for(j = 0; j < 12; j++){
			if (j == 11){
				writer = writer+to_string(disk.files[i].dbps[j])+" ";
			} else {
				writer = writer+to_string(disk.files[i].dbps[j])+",";
			}
		}
		writer = writer+to_string(disk.files[i].ibp_num->getBlockNum())+" "+to_string(disk.files[i].dibp_num->getBlockNum());
		for(j = writer.length(); j <disk.block_size; j++){
			writer = writer+" ";
		}
		fseek(cont, ((i+1)*disk.block_size), SEEK_SET);
		fputs(writer.c_str(), cont);
	}
	//Writing IBP info
	for(i = 0; i < disk.files.size(); i++){
		
		int IBPlocation = disk.files[i].ibp_num->getBlockNum();
//		cout << IBPlocation << endl;
		if(IBPlocation != -1){
			string writer = "";
			for(j = 0; j < disk.files[i].ibp_num->getDBPS().size();j++){
				writer = writer+to_string(disk.files[i].ibp_num->getDBPS()[j])+",";
			}
			for(j = writer.length(); j <disk.block_size; j++){
				writer = writer+" ";
			}
			fseek(cont, (IBPlocation*disk.block_size)+(disk.block_size*257), SEEK_SET);
			fputs(writer.c_str(), cont);
		}
	}
	//Write DIBP location
	for(i = 0; i < disk.files.size();i++){
		int DIBPlocation = disk.files[i].dibp_num->getBlockNum();
		if(DIBPlocation != -1){
			string writer = "";
			for(j = 0; j < disk.files[i].dibp_num->ibps.size(); j++){
				writer = writer+to_string(disk.files[i].dibp_num->ibps[j]->getBlockNum())+" ";
			}
			for(j = writer.length(); j <disk.block_size; j++){
				writer = writer+" ";
			}
			fseek(cont, (DIBPlocation*disk.block_size)+(disk.block_size*257), SEEK_SET);
			fputs(writer.c_str(), cont);
		}
	}
	//Write each IBP location in the DIBP
	for(i = 0; i < disk.files.size(); i++){
		for(j = 0; j < disk.files[i].dibp_num->ibps.size(); j++){
			int IBPlocation = disk.files[i].dibp_num->ibps[j]->getBlockNum();
			if(IBPlocation != -1){
				string writer = "";
				for(p = 0; p < disk.files[i].dibp_num->ibps[j]->dbps.size();p++){
					writer = writer+to_string(disk.files[i].dibp_num->ibps[j]->dbps[p])+",";
				}
				for(j = writer.length(); j <disk.block_size; j++){
					writer = writer+" ";
				}
				fseek(cont, (IBPlocation*disk.block_size)+(disk.block_size*257), SEEK_SET);
				fputs(writer.c_str(), cont);
			}
		}
	}
	
//	fseek(cont, (disk.files[fileNum].DIBP.ibps[i].dips[p]*disk.block_size)+(256*disk.block_size)+j, SEEK_SET);
//	fputs(bytes[index], cont);
	
//	cout << "Disk write complete" << endl;
	
	fclose(cont);
}

void file_write(string filename, char character, int byte, int num_bytes){
	int i,j,k,p;
	int fileNum;
	for (i = 0; i < 256; i++){
		if (disk.getFiles()[i].getFilename() == filename){
			fileNum = i;
			break;
		}
	}
	if(i == 256){
		cerr << "File does not exist" << endl;
	}
	
	
	//Adding more 
	while(disk.getFiles()[fileNum].getSize() < byte+num_bytes){
		bool dbp = false, ibp = false, dibp = false, breaktrue = false;
		for(i = 0; i < 12; i++){
			if(disk.getFiles()[fileNum].dbps[i] == -1){
				j = 0;
				while(j < disk.getFreeBlocks().size() && disk.getFreeBlocks()[j] == false){
					j++;
				}
				if(j == disk.getFreeBlocks().size()){
					cerr << "no available blocks" << endl;
					del(disk.getFiles()[fileNum].filename);
					return;
				}
				disk.setFree(j, false);
				disk.files[fileNum].dbps[i] = j;
				disk.files[fileNum].appendFilesize(disk.block_size);
				dbp = true; 
				ibp = true;
				dibp = true;
				break;
			}
		}
		if(dbp == false){
			if(disk.files[fileNum].ibp_num->getBlockNum() == -1){
				j = 0;
				while(j < disk.getFreeBlocks().size() && disk.getFreeBlocks()[j] == false){
					j++;
				}
				if(j == disk.getFreeBlocks().size()){
					cerr << "no available blocks" << endl;
					del(disk.getFiles()[fileNum].filename);
					return;
				}
				disk.setFree(j, false);
				disk.files[fileNum].ibp_num = new IBP(j, disk.block_size);
			//	disk.files[fileNum].appendFilesize(disk.block_size);
			}
			for(i = 0; i < disk.files[fileNum].ibp_num->dbps.size(); i++){
				if(disk.getFiles()[fileNum].ibp_num->dbps[i] == -1){
					j = 0;
					while(j < disk.getFreeBlocks().size() && disk.getFreeBlocks()[j] == false){
						j++;
					}
					if(j == disk.getFreeBlocks().size()){
						cerr << "no available blocks" << endl;
						del(disk.getFiles()[fileNum].filename);
						return;
					}
					disk.setFree(j, false);
					disk.files[fileNum].ibp_num->dbps[i] = j;
					disk.files[fileNum].appendFilesize(disk.block_size);
					ibp = true; 
					dibp = true;
					break;
				}
			}
		}
		if(ibp == false){
			if(disk.files[fileNum].dibp_num->getBlockNum() == -1){
				j = 0;
				while(j < disk.getFreeBlocks().size() && disk.getFreeBlocks()[j] == false){
					j++;
				}
				if(j == disk.getFreeBlocks().size()){
					cerr << "no available blocks" << endl;
					del(disk.getFiles()[fileNum].filename);
					return;
				}
				disk.setFree(j, false);
				disk.files[fileNum].dibp_num = new DIBP(j, disk.block_size);
			//	disk.files[fileNum].appendFilesize(disk.block_size);
			}
			for(k = 0; k < disk.files[fileNum].dibp_num->ibps.size(); k++){
				if(breaktrue == true){
					break;
				}
				if(disk.files[fileNum].dibp_num->ibps[k]->getBlockNum() == -1){
					j = 0;
					while(j < disk.getFreeBlocks().size() && disk.getFreeBlocks()[j] == false){
						j++;
					}
					if(j == disk.getFreeBlocks().size()){
						cerr << "no available blocks" << endl;
						del(disk.getFiles()[fileNum].filename);
						return;
					}
					disk.setFree(j, false);
					disk.files[fileNum].dibp_num->ibps[k] = new IBP(j, disk.block_size);
				//	disk.files[fileNum].appendFilesize(disk.block_size);
				}
				for(i = 0; i < disk.files[fileNum].dibp_num->ibps[k]->dbps.size(); i++){
					if(disk.files[fileNum].dibp_num->ibps[k]->dbps[i] == -1){
						j = 0;
						while(j < disk.getFreeBlocks().size() && disk.getFreeBlocks()[j] == false){
							j++;
						}
						if(j == disk.getFreeBlocks().size()){
							cerr << "no available blocks" << endl;
							del(disk.getFiles()[fileNum].filename);
							return;
						}
						disk.setFree(j, false);
						disk.files[fileNum].dibp_num->ibps[k]->dbps[i] = j;
						disk.files[fileNum].appendFilesize(disk.block_size);
						dibp = true; 
						breaktrue = true;
						break;
					}
				}
			}
		}
		if(dibp == false){
			cerr << "Nor enough space to allocate for the file." << endl;
			return;
		}
	}
	
	
	FILE *cont;
    cont = fopen(disk.diskname.c_str(), "r+");
	string newchar(1, character);
   
    int index = 0;
	for(i = 0; i < 12; i++){
		j = 0;
		while(j < disk.block_size){
			if(index >= byte){
				fseek(cont, (disk.files[fileNum].dbps[i]*disk.block_size)+(257*disk.block_size)+j, SEEK_SET);
				fputs(&newchar[0], cont);
			}
			index++;
			j++;
			if(index == byte+num_bytes){
				cout << "Write successful" << endl;
				fclose(cont);
				return;
			}
		}
	}
	for(i = 0; i < disk.files[fileNum].ibp_num->dbps.size(); i++){
		j = 0;
		while(j < disk.block_size){
			if(index >= byte){
				fseek(cont, (disk.files[fileNum].ibp_num->dbps[i]*disk.block_size)+(257*disk.block_size)+j, SEEK_SET);
				fputs(&newchar[0], cont);
			}
			index++;
			j++;
			if(index == byte+num_bytes){
				cout << "Write successful" << endl;
				fclose(cont);
				return;
			}
		}
	}
	for(i = 0; i < disk.files[fileNum].dibp_num->ibps.size(); i++){
		for(p = 0; p < disk.files[fileNum].dibp_num->ibps[i]->dbps.size(); p++){
			j = 0;
			while(j < disk.block_size){
				if(index >= byte){
					fseek(cont, (disk.files[fileNum].dibp_num->ibps[i]->dbps[p]*disk.block_size)+(257*disk.block_size)+j, SEEK_SET);
					fputs(&newchar[0], cont);
				}
				index++;
				j++;
				if(index == byte+num_bytes){
					cout << "Write successful" << endl;
					fclose(cont);
					return;
				}
			}
		}
	}
	
	fclose(cont);
}


void import(string filename, string unixname){
	int i,j,k,p;
	int fileNum;
	for (i = 0; i < 256; i++){
		if (disk.getFiles()[i].getFilename() == filename){
			del(filename);
			create(filename);
			for (j = 0; j < 256; j++){
				if (disk.getFiles()[j].getFilename() == filename){
					fileNum = j;
					break;
				}
			}
			break;
		}
	}
	if(i == 256){
		for(k = 0; k < 256; k++){
			if(disk.getFreeInodes()[k] == true){
				create(filename);
				for (p = 0; p < 256; p++){
					if (disk.getFiles()[p].getFilename() == filename){
						fileNum = p;
						break;
					}
				}
				break;
			}
		}
	}
	if(k == 256){
		cerr << "Cannot make the file." << endl;
		return;
	}


	ifstream infile;
	infile.open(unixname.c_str());
	char character;
	string bytes = "";
	while(!infile.eof()){
		infile.get(character);
//		cout << character << endl;
		bytes = bytes+character;
	}
	
//	cout << "got here" << endl;
	bytes.erase(bytes.length()-1, bytes.length());
//	cout << bytes.size() << endl;
//	cout << disk.getFiles()[fileNum].getSize() << endl;
//	cout << disk.block_size << endl;
	//Adding more 
	while(disk.getFiles()[fileNum].getSize() < bytes.length()){
//		cout << "loop" << endl;
		bool dbp = false, ibp = false, dibp = false, breaktrue = false;
		for(i = 0; i < 12; i++){
			if(disk.getFiles()[fileNum].dbps[i] == -1){
				j = 0;
				while(j < disk.getFreeBlocks().size() && disk.getFreeBlocks()[j] == false){
					j++;
				}
				if(j == disk.getFreeBlocks().size()){
					cerr << "no available blocks" << endl;
					del(disk.getFiles()[fileNum].filename);
					return;
				}
				disk.setFree(j, false);
				disk.files[fileNum].dbps[i] = j;
//				cout << j << endl;
				disk.files[fileNum].appendFilesize(disk.block_size);
//				cout << disk.getFiles()[fileNum].getSize() << endl;
				dbp = true; 
				ibp = true;
				dibp = true;
				break;
			}
		}
		if(dbp == false){
			if(disk.files[fileNum].ibp_num->getBlockNum() == -1){
				j = 0;
				while(j < disk.getFreeBlocks().size() && disk.getFreeBlocks()[j] == false){
					j++;
				}
				if(j == disk.getFreeBlocks().size()){
					cerr << "no available blocks" << endl;
					return;
				}
				disk.setFree(j, false);
				disk.files[fileNum].ibp_num = new IBP(j, disk.block_size);
			//	disk.files[fileNum].appendFilesize(disk.block_size);
			}
			for(i = 0; i < disk.files[fileNum].ibp_num->dbps.size(); i++){
				if(disk.getFiles()[fileNum].ibp_num->dbps[i] == -1){
					j = 0;
					while(j < disk.getFreeBlocks().size() && disk.getFreeBlocks()[j] == false){
						j++;
					}
					if(j == disk.getFreeBlocks().size()){
						cerr << "no available blocks" << endl;
						del(disk.getFiles()[fileNum].filename);
						return;
					}
					disk.setFree(j, false);
					disk.files[fileNum].ibp_num->dbps[i] = j;
					disk.files[fileNum].appendFilesize(disk.block_size);
					ibp = true; 
					dibp = true;
					break;
				}
			}
		}
		if(ibp == false){
			if(disk.files[fileNum].dibp_num->getBlockNum() == -1){
				j = 0;
				while(j < disk.getFreeBlocks().size() && disk.getFreeBlocks()[j] == false){
					j++;
				}
				if(j == disk.getFreeBlocks().size()){
					cerr << "no available blocks" << endl;
					del(disk.getFiles()[fileNum].filename);
					return;
				}
				disk.setFree(j, false);
				disk.files[fileNum].dibp_num = new DIBP(j, disk.block_size);
				//disk.files[fileNum].appendFilesize(disk.block_size);
			}
			for(k = 0; k < disk.files[fileNum].dibp_num->ibps.size(); k++){
				if(breaktrue == true){
					break;
				}
				if(disk.files[fileNum].dibp_num->ibps[k]->getBlockNum() == -1){
					j = 0;
					while(j < disk.getFreeBlocks().size() && disk.getFreeBlocks()[j] == false){
						j++;
					}
					if(j == disk.getFreeBlocks().size()){
						cerr << "no available blocks" << endl;
						del(disk.getFiles()[fileNum].filename);
						return;
					}
					disk.setFree(j, false);
					disk.files[fileNum].dibp_num->ibps[k] = new IBP(j, disk.block_size);
				//	disk.files[fileNum].appendFilesize(disk.block_size);
				}
				for(i = 0; i < disk.files[fileNum].dibp_num->ibps[k]->dbps.size(); i++){
					if(disk.files[fileNum].dibp_num->ibps[k]->dbps[i] == -1){
						j = 0;
						while(j < disk.getFreeBlocks().size() && disk.getFreeBlocks()[j] == false){
							j++;
						}
						if(j == disk.getFreeBlocks().size()){
							cerr << "no available blocks" << endl;
							del(disk.getFiles()[fileNum].filename);
							return;
						}
						disk.setFree(j, false);
						disk.files[fileNum].dibp_num->ibps[k]->dbps[i] = j;
						disk.files[fileNum].appendFilesize(disk.block_size);
						dibp = true; 
						breaktrue = true;
						break;
					}
				}
			}
		}
		if(dibp == false){
			cerr << "Not enough space to allocate for the file." << endl;
			return;
		}
	}
	
//	cout << "here" << endl;
//	cout << disk.getFiles()[fileNum].getSize() << endl;
	//writing the bytes to the file location
    
    
    FILE *cont;
    cont = fopen(disk.diskname.c_str(), "r+");
   
    int index = 0;
	for(i = 0; i < 12; i++){
		j = 0;
		while(j < disk.block_size){
			fseek(cont, (disk.files[fileNum].dbps[i]*disk.block_size)+(257*disk.block_size)+j, SEEK_SET);
			fputs(&bytes[index], cont);
			index++;
			j++;
			if(index == bytes.length()){
				cout << "Import successful" << endl;
				fclose(cont);
				return;
			}
		}
	}
//	cout << "Finished DBPs" << endl;
//	cout << index << endl;
	for(i = 0; i < disk.files[fileNum].ibp_num->dbps.size(); i++){
//		cout << index << endl;
		j = 0;
		while(j < disk.block_size){
			fseek(cont, (disk.files[fileNum].ibp_num->dbps[i]*disk.block_size)+(257*disk.block_size)+j, SEEK_SET);
			fputs(&bytes[index], cont);
			index++;
			j++;
			if(index == bytes.length()){
//				cout << index << endl;
				cout << "Import successful" << endl;
				fclose(cont);
				return;
			}
		}
	}
	for(i = 0; i < disk.files[fileNum].dibp_num->ibps.size(); i++){
		for(p = 0; p < disk.files[fileNum].dibp_num->ibps[i]->dbps.size(); p++){
			j = 0;
			while(j < disk.block_size){
				fseek(cont, (disk.files[fileNum].dibp_num->ibps[i]->dbps[p]*disk.block_size)+(257*disk.block_size)+j, SEEK_SET);
				fputs(&bytes[index], cont);
				index++;
				j++;
				if(index == bytes.length()){
					cout << "Import successful" << endl;
					fclose(cont);
					return;
				}
			}
		}
	}
	
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
		for(int i = start_byte; i < start_byte + num_bytes; i++){
	    cout << fileData[i];
	}
	cout << endl;	
	}
	else //file could not be opened
	{
		cout << "File could not be opened." << endl;
	}
}



void disk_init(string filename){
	FILE *cont;
    cont = fopen(filename.c_str(), "r+");
    string diskname, disk_blocks_num, disk_block_size;
    diskname = filename;
    
//    cout << "Beginning of disk init" << endl;
    
    //grabbing num_blocks and block_size
    ifstream infile(filename.c_str());
    string superblock;
    stringstream ss;
    
    if(infile.good()){
    	getline(infile, superblock); //grabs first line
    }
    ss << superblock;
    ss >> disk_block_size >> disk_blocks_num; //stringstream splits by space and stores into the variables
//    cout << "disk_blocks_num = " << disk_blocks_num << " and disk_block_size = " << disk_block_size << endl; 
    int num_blocks = atoi(disk_blocks_num.c_str());
    int block_size = atoi(disk_block_size.c_str());
   
   
//   cout << num_blocks << " " << block_size << endl;
//   cout << "Beginning of disk init 2" << endl;
   
   disk = Disk(diskname, num_blocks, block_size);
   
//    cout << "Beginning of disk init 3" << endl;
   
    //first block is dedicated to disk info?
    char inode[512];
    char ibpcontents[512];
    char dibpcontents[512];
    string temp, inode_name,dbps, newtemp;
    int pos, pos2;
    int block_num;
    int ibp_num;
    int dibp_num;
    int j;
 //   cout << "Beginning of disk init 4" << endl;
    for(int i = 1; i < 257;i++){
 //   	 cout << "loop: " << i << endl;
    	int seek_position = i*disk.block_size;
    	fseek(cont, seek_position, SEEK_SET);
    	fgets(inode, disk.block_size, cont);
    	
    	temp = string(inode);
//    	cout << temp << endl;
    	pos = temp.find(" ");
//    	cout << i << " " << temp.substr(0,pos) << endl;
//		cout << atoi(temp.substr(0,pos).c_str()) << endl;
    	if(atoi(temp.substr(0,pos).c_str()) != -1){
   // 		cout << "got here in init" << endl;
    		block_num = atoi(temp.substr(0,pos).c_str());
    		temp.erase(0, pos+1);
    		
    		pos = temp.find(" ");
    		
    		inode_name = temp.substr(0,pos);
//    		cout << "here " << endl;
    		disk.files[block_num] = File(inode_name, disk.block_size, block_num);
    		
    		disk.free_inodes[block_num] = false;
  //  		cout << disk.files[block_num].filename <<  endl;
    		temp.erase(0, pos+1);
    		
    		pos = temp.find(" ");
    		
    		int filesize = atoi(temp.substr(0,pos).c_str());
    		disk.files[block_num].filesize = filesize;
    		temp.erase(0, pos+1);
    		
   // 		cout << disk.files[block_num].filesize << endl;
    		
    		pos = temp.find(" ");
    		dbps = temp.substr(0,pos);
//    		cout << dbps << endl;
    		for(j=0;j< 12; j++){
    			pos2 = dbps.find(",");
    			disk.files[block_num].dbps[j] = atoi(dbps.substr(0,pos2).c_str());
    			if(atoi(dbps.substr(0,pos2).c_str()) != -1){
    				disk.setFree(atoi(dbps.substr(0,pos2).c_str()), false);
    			}
 //   			cout << disk.files[block_num].dbps[j] << endl;
    			dbps.erase(0,pos2+1);
    		}
    		temp.erase(0,pos+1);
//    		cout << temp << endl;
			pos = temp.find(" ");
    		ibp_num = atoi(temp.substr(0,pos).c_str());
//    		cout << temp.substr(0,pos) << endl;
 //   		cout << "IBP num: " << ibp_num << endl;
    		if(ibp_num > -1){
    			disk.setFree(ibp_num, false);
    			disk.files[block_num].ibp_num = new IBP(ibp_num, disk.block_size);
    			fseek(cont, (ibp_num*disk.block_size)+(257*disk.block_size), SEEK_SET);
    			fgets(ibpcontents, disk.block_size, cont);
    			string new1temp = string(ibpcontents);
 //   			cout << new1temp << endl;
    			for(j = 0; j < 	disk.files[block_num].ibp_num->dbps.size(); j++){
    				pos2 = new1temp.find(",");
	    			disk.files[block_num].ibp_num->dbps[j] = atoi(new1temp.substr(0,pos2).c_str());
//	    			cout << disk.files[block_num].ibp_num->dbps[j] << " " << atoi(new1temp.substr(0,pos2).c_str()) << endl;
	    			if(atoi(new1temp.substr(0,pos2).c_str()) != -1){
	    				disk.setFree(atoi(new1temp.substr(0,pos2).c_str()), false);
	    			}
	    			new1temp.erase(0,pos2+1);
    			}
    			
    			temp.erase(0,pos+1);
    			pos = temp.find(" ");
    			dibp_num = atoi(temp.substr(0,pos).c_str());
    			if(dibp_num > -1){
    				disk.setFree(dibp_num, false);
	    			disk.files[block_num].dibp_num = new DIBP(dibp_num, disk.block_size);
	    			fseek(cont, (dibp_num*disk.block_size)+(257*disk.block_size), SEEK_SET);
	    			fgets(dibpcontents, disk.block_size, cont);
	    			string new2temp = string(dibpcontents);
	//    			cout << new2temp << endl;
	    			for(j = 0; j <	disk.files[block_num].dibp_num->ibps.size(); j++){
	    				pos2 = new2temp.find(",");
		    			disk.files[block_num].dibp_num->ibps[j] = new IBP(atoi(new2temp.substr(0,pos2).c_str()));
		    			if(atoi(new2temp.substr(0,pos2).c_str()) != -1){
		    				disk.setFree(atoi(new2temp.substr(0,pos2).c_str()), false);
		    			}
		    			new2temp.erase(0,pos2+1);
	    			}
	    			//bool done = false;
	    			for(int j = 0; j < disk.files[block_num].dibp_num->getIBPS().size(); j++){
	    				ibp_num = disk.files[block_num].dibp_num->getIBPS()[j]->getBlockNum();
	    				if(ibp_num > -1 ){
	    					disk.setFree(ibp_num, false);
			    			disk.files[block_num].dibp_num->ibps[j] = new IBP(ibp_num, disk.block_size);
			    			fseek(cont, (ibp_num*disk.block_size)+(257*disk.block_size), SEEK_SET);
			    			fgets(ibpcontents, disk.block_size, cont);
			    			string new3temp = string(ibpcontents);
			    			for(int p = 0; p < 	disk.files[block_num].dibp_num->ibps.size(); p++){
			    				pos2 = new3temp.find(",");
				    			disk.files[block_num].dibp_num->ibps[j]->dbps[p] = atoi(new3temp.substr(0,pos2).c_str());
				    			if(atoi(new3temp.substr(0,pos2).c_str()) != -1){
				    				disk.setFree(atoi(new3temp.substr(0,pos2).c_str()), false);
				    			}
				    			new3temp.erase(0,pos2+1);
			    			}
	    				}
	    				else{
	    						disk.files[block_num].dibp_num->ibps[j] =  new IBP(block_size);
	    				}
	    			}
    			}
    			else{
    				disk.files[i-1].dibp_num = new DIBP(disk.block_size);
    			}
    		}
    		else{
	    		disk.files[i-1].ibp_num = new IBP(disk.block_size);
	    		disk.files[i-1].dibp_num = new DIBP(disk.block_size);
	    	}
    	}
    }
}
