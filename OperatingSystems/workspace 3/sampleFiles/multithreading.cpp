//Make test files,
//Write to buffer
//See if written to buffer correctly;
#include <pthread.h> 

#include <sys/types.h>

#include <stdio.h>
#include <assert.h> 
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>

void shutdown() {
	//Check to see if this is last command in buffer.
	//Otherwise, ignore (because producer thread closes once it writes it's entire contents to buffer)
	//If it is last command in buffer write to disk
	if (buffer.empty()) {
		cout << "Now exiting..." << endl;
		exit(0);
	}
}

using namespace std;

queue<string> buffer;

pthread_cond_t full;
pthread_mutex_t mutex, create;
int numproducers = -1;

vector<string> threadFiles;

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
	//const char* const nameFile = static_cast<const char* const>(fileName);
	pthread_mutex_lock(&create);
	fp.open(threadFiles.back());
	if (fp.is_open() == true) {
		threadFiles.pop_back();
		pthread_mutex_unlock(&create);
		while (!fp.eof()) {
			pthread_mutex_lock(&mutex);
			getline(fp, process);
			put(process);
			pthread_cond_signal(&full);
			pthread_mutex_unlock(&mutex);
		}
	} else {
		cerr << "file did not open" << endl;
		pthread_mutex_unlock(&create);
	}
	fp.close();
}

//Disk Controller
string consumer() {
	string process;
	string current;
	pthread_mutex_lock(&mutex);
	while (buffer.empty()) {
		pthread_cond_wait(&full, &mutex);
	}
	//gets command from front of queue
	current = get();
	//SENDS VALUE OF CURRENT TO DISK AND PROCESS IT. Parse current
	pthread_mutex_unlock(&mutex);
	return current;
}

int main(int argc, char *argv[]){
	
	//vector<DiskOpThread> dots;

	string disk_file_name;
	//If this works, try to dynamically allocate

	if(argc <= 2 || argc > 6){
		cerr << "Wrong Number of arguments!" << endl;
		return 1;
	}

	disk_file_name = argv[1];
	//DiskController dct = new DiskController(/**PARAMETER**/);
	for(int i = 2; i < argc; i++){
		//create vector of threads
		threadFiles.push_back(argv[i]);
	}
	
	//dct.processRequests(dots);
	
	//Only make producer thread once.
	//Make producer thread one per function
	string *myThread;
	pthread_t *p;
	if(argc == 3){
		//Make 1 consumer thread and 1 producer thread
		numproducers = 1;
		p= new pthread_t[numproducers];
		pthread_create(&p[0], NULL, producer, myThread);
	}
	else if(argc == 4){
		//Make 1 consumer thread and 2 producer threads
		numproducers = 2;
		p = new pthread_t[numproducers];
		pthread_create(&p[0], NULL, producer, myThread);
		pthread_create(&p[1], NULL, producer, myThread);
	}
	else if(argc == 5){
		//Make 1 consumer thread and 3 producer threads
		numproducers = 3;
		p = new pthread_t[numproducers];
		pthread_create(&p[0], NULL, producer, myThread);
		pthread_create(&p[1], NULL, producer, myThread);
		pthread_create(&p[2], NULL, producer, myThread);
	}
	else{
		//Make 1 consumer thread and 4 producer threads
		numproducers = 4;
		p = new pthread_t[numproducers];
		pthread_create(&p[0], NULL, producer, myThread);
		pthread_create(&p[1], NULL, producer, myThread);
		pthread_create(&p[2], NULL, producer, myThread);
		pthread_create(&p[3], NULL, producer, myThread);
	}
	for (int i = 0; i < numproducers; i++) {
		pthread_join(p[0], NULL);
	}
	FILE *test;
	string printMe;
	while(!buffer.empty()) {
		printMe = consumer();
		cout << printMe << endl;

	}
	return 0;
}
//void shutdown() {
	//Check to see if this is last command in buffer.
	//Otherwise, ignore (because producer thread closes once it writes it's entire contents to buffer)
	//If it is last command in buffer write to disk
	//disk_write();
//}