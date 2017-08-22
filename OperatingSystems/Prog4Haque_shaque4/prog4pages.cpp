#include <iostream>
#include <ostream>
#include <string>
#include <istream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;

//These global variables are for for pure randomness. each page has equal chance of being chosen. rand() has bias when modding with small numbers cause it uses lower order bits
int seed = time(0);
default_random_engine engine(seed);

//Function definitions below:

int findPosition(vector<int> v, int value, int startingIndex){
    
    for (int i = startingIndex; i < v.size(); i++){
        
        if (value == v[i]){
            return i;
        }
    }
    return -1;
    
}


long double clock(int cacheSize, vector<int> pageAccesses){
   // cout << "Entering clock function!" << endl;
    vector<int> cache;
    vector<int> clock; //contains clock hand/use bits. if 0 == not used recently, 1 == recently used
    int i = 0;
    int num_hits = 0;
    int num_refs = 0;
    for (vector<int>::iterator it = pageAccesses.begin(); it != pageAccesses.end(); it++) {
        vector<int>::iterator itCache = find(cache.begin(), cache.end(), *it);
        //page not in cache + cold starts
        if (itCache == cache.end()) {
            //continue filling frames
            if (cache.size() < cacheSize) {
                cache.push_back(*it);
                clock.push_back(1); //set clock hand/use bitto 1 initially
            }
            //page fault, replace
            else {
                num_refs++;
                while (true) {
                    //found a page to replace
                    if (clock[i] == 0) {
                        cache[i] = *it;
                        clock[i] = 1;
                        i = (i + 1) % cacheSize;
                        break;
                    }
                    else {
                        clock[i] = 0;
                    }
                    //makes sure i is never longer than frameNum
                    i = (i + 1) % cacheSize;
                }
            }
        }
        //if clock frames contains the page
        else {
            int indexInCache;
            for (indexInCache = 0; cache[indexInCache] != *itCache; indexInCache++);
            clock[indexInCache] = 1;
            if (cache.size() >= cacheSize) {
                 num_hits++;
                num_refs++;
            }
        }
    }
    long double hit_rate = (num_hits/ (long double) num_refs)  * 100;
    //cout << "Leaving Clock function!" << endl;
    return hit_rate;
}

long double random(int cacheSize, vector<int> pageAccesses){
    //cout << "Entering Random function!" << endl;
    int num_hits = 0;
    int num_refs = 0;
    vector<int> cache;
    int randomPageIndex;
    
    for (vector<int>::iterator it = pageAccesses.begin(); it != pageAccesses.end(); ++it){
        //page not in cache + cold starts
        if (findPosition(cache, *it, 0) == -1)
        {
            //page fault
            if (cache.size() >= cacheSize)
            {
                //replaces a random page
                randomPageIndex = rand() % cache.size();
                cache[randomPageIndex] = *it;
                num_refs++;
            }
            else
            {
                //continue filling frames
                cache.push_back(*it);
            }
        }
        //page in cache
        else {
            if (cache.size() >= cacheSize) {
                num_hits++;
                num_refs++;
            }
        }
    }
    
    long double hit_rate = (num_hits/ (long double) num_refs)  * 100;
    //cout << "Leaving Random function!" << endl;
    return hit_rate;
    
}


long double fifo(int cacheSize, vector<int> pageAccesses){
    //cout << "Entering FIFO function!" << endl;
    int num_hits = 0;
    int num_refs = 0;
    vector<int> cache;
    int nextOut = 0; //index to keep track of next page to get rid of in FIFO order
    
    for (vector<int>::iterator it = pageAccesses.begin(); it != pageAccesses.end(); ++it){
        //page not in cache + cold starts
        if (findPosition(cache, *it, 0) == -1)
        {
            //page fault
            if (cache.size() >= cacheSize)
            {
                //replaces first page in
                cache[nextOut] = *it;
                if (nextOut + 1 < cacheSize){ //move to next page within cache as that is the next one out
                    nextOut++;
                } else { //rest to 0 since we hit the last page in cache
                    nextOut = 0;
                }
                num_refs++;
            }
            else
            {
                //continue filling frames
                cache.push_back(*it);
            }
        }
        //page hit
        else {
            if (cache.size() >= cacheSize) {
                num_hits++;
                num_refs++;
            }
        }
    }
    long double hit_rate = (num_hits/ (long double) num_refs)  * 100;
    //cout << "Leaving FIFO function!" << endl;
    return hit_rate;
    
}

long double lru(int cacheSize, vector<int> pageAccesses){
   // cout << "Entering LRU function!" << endl;
    
    int num_hits = 0;
    int num_refs = 0;
    vector<int> lru_stack;
    vector<int> cache;
    
    for (int i : pageAccesses){
        //cold starts and misses in cache
        int pos = findPosition(cache, i, 0);
        if (pos == -1){
            //page fault, needs replacement
            if (cache.size() >= cacheSize){
                //finds the least recently used page to replace (top of stack)
                int page_to_replace = lru_stack[0];
                pos = findPosition(cache, page_to_replace, 0);
                cache[pos] = i;
                //remove replaced in stack and put in new page
                lru_stack.erase(lru_stack.begin());
                lru_stack.push_back(i);
                num_refs++;
            }
            else{
                cache.push_back(i);
                lru_stack.push_back(i);
            }
        }
        //if cache has a hit
        else{
            pos = findPosition(lru_stack, i, 0);
            lru_stack.erase(lru_stack.begin() + pos);
            lru_stack.push_back(i);
            if (cache.size() >= cacheSize) {
                num_hits++;
               num_refs++;
            }
        }
       
    }
    long double hit_rate = (num_hits/ (long double) num_refs)  * 100;
    //cout << "Leaving LRU function!" << endl;
    return hit_rate;
}



long double opt(int cacheSize, vector<int> pageAccesses){
    //cout << "Entering OPT function!" << endl;
    int num_hits = 0;
    int num_refs = 0;
    vector<int> cache;
    
    for(int i = 0; i < pageAccesses.size(); i++){
        int access = pageAccesses.at(i);
        int pos = findPosition(cache, access, 0);
        
        //handles cold starts and misses
        if (pos == -1){
            //page fault
            if (cache.size() >= cacheSize){
                vector<int> pg_index; //to check if pages are never used again thus all values initialized to  -1
                for(int j = 0; j < cacheSize; j++){
                    pg_index.push_back(-1);
                }
                //finds position of page closest in future to be accessed
                for(int j = 0; j < cache.size(); j++){
                   
                    if ((pos = findPosition(pageAccesses, cache.at(j), i)) != -1){
                        pg_index[j] = pageAccesses.size() - 1 - pos;
                    }
                }
                int replace_this_page;
                int reI = -2;
                for (int x = 0; x < pg_index.size(); x++){
                    
                    if (reI == -2){
                        replace_this_page = cache[x];
                        reI = pg_index[x];
                    }
                    else if (pg_index[x] < reI){
                        replace_this_page = cache[x];
                        reI = pg_index[x];
                    }
                }
                
                pos = findPosition(cache, replace_this_page, 0);
                cache[pos] = access;
                num_refs++;
            } else { //fill frames
                cache.push_back(access);
            }
        //if page is in the cache
        } else {
            pos = findPosition(cache, access, 0);
            if (cache.size() >= cacheSize) {
                num_hits++;
                num_refs++;
            }
        }
        
       
}
    long double hit_rate = (num_hits/ (long double) num_refs)  * 100;
    //cout << "Leaving OPT function!" << endl;
    return hit_rate;
    
}

//assume numPages is 100
vector<int> create80_20locality(int numPages, int numPageAccesses){
    vector<int>  pages20, pages80, locality80_20;
    int twentyPercentPages = (int)(numPages * .2); //20
    int eightyPercentPages = numPages - twentyPercentPages; //80
    uniform_int_distribution<int> distribution(0, numPages-1); //uniform dist -> [0,99]
    
    
    
    //create a subset of a random 20% of pages of the unique number of pages
    //looping through 20
    for(int i = 0; i < twentyPercentPages; i++){
        int page = distribution(engine); //chooses random page
        
        //make sure each page is unique! only adds to pages20 if page is not contained in pages20.
        //if it is, keep doing rand() mod numPages to get a new page until its not in pages20
        while ( find (pages20.begin(), pages20.end(), page) != pages20.end()){
            page = distribution(engine);
        }
        
        pages20.push_back(page);
    }

    //use pages20 to add the pages not in it. to do so I used the find (within <algorithm> to make sure it grabs pages not in pages20
    //
    for(int i = 0; i < numPages; i++){
        if ( find (pages20.begin(), pages20.end(), i) != pages20.end()){
            //pages 20 already has this page so do nothing
        } else {
            pages80.push_back(i); //*** NOTE *** : this is adding pages in increasing order
        }
    }
    //randum shuffle (within <algorithm>) the pages80 vector
    random_shuffle(pages80.begin(), pages80.end());
    
    uniform_int_distribution<int> d80(0, pages80.size()-1); //uniform dist -> [0, 80) or [0, 79]
    uniform_int_distribution<int> d20(0, pages20.size()-1); //uniform dist -> [0, 20) or [0,19]
    
    
    int r20p80_size = .2 * numPageAccesses; //size where 20% references is 80% pages. so 20% of 10,000 is 2,000
    int r80p20_size = numPageAccesses - r20p80_size; //size where 80% references is 20% pages. so 80% of 10,000 is 8,000
    
    
    for(int i = 0; i < r20p80_size; i++){
        int r = d80(engine);
        locality80_20.push_back(pages80[r]); //make 20% of references to 80% of pages
    }
    
    for(int i = 0; i < r80p20_size; i++){
        int r = d20(engine);
        locality80_20.push_back(pages20[r]); //make 80% of references to 20% of pages
    }
    
    random_shuffle(locality80_20.begin(), locality80_20.end()); //shuffle the whole page accesses for 80-20 locality
    
    return locality80_20;
}

void writeNoLocalityCSV(int cacheSizes[], vector<int> noLocality){
    long double optResults[20];
    long double lruResults[20];
    long double fifoResults[20];
    long double randomResults[20];
    long double clockResults[20];
    
    for(int i=0; i < 20; i++){
        optResults[i] = opt(cacheSizes[i], noLocality);
        lruResults[i] = lru(cacheSizes[i], noLocality);
        fifoResults[i] = fifo(cacheSizes[i], noLocality);
        randomResults[i] = random(cacheSizes[i], noLocality);
        clockResults[i] = clock(cacheSizes[i], noLocality);
    }
    
    ofstream outputFile;
    outputFile.open("no-locality.csv");
    
    //create the column headers
    outputFile << "#cache" << "," << "OPT" << "," << "LRU" << "," << "FIFO" << "," << "RAND" << "," << "CLOCK" << endl;
    
    outputFile << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << endl;
    
    for(int i=0; i<20; i++){
    outputFile << cacheSizes[i] << "," << optResults[i] << "," << lruResults[i] << "," << fifoResults[i] << "," << randomResults[i] << "," << clockResults[i] << endl;
    }
    outputFile.close();
}

void write80_20LocalityCSV(int cacheSizes[],vector<int> locality80_20){
    long double optResults[20];
    long double lruResults[20];
    long double fifoResults[20];
    long double randomResults[20];
    long double clockResults[20];
    
    for(int i=0; i < 20; i++){
        optResults[i] = opt(cacheSizes[i], locality80_20);
        lruResults[i] = lru(cacheSizes[i], locality80_20);
        fifoResults[i] = fifo(cacheSizes[i], locality80_20);
        randomResults[i] = random(cacheSizes[i], locality80_20);
        clockResults[i] = clock(cacheSizes[i], locality80_20);
    }
    
    ofstream outputFile;
    outputFile.open("80-20.csv");
    
    //create the column headers
    outputFile << "#cache" << "," << "OPT" << "," << "LRU" << "," << "FIFO" << "," << "RAND" << "," << "CLOCK" << endl;
    
    outputFile << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << endl;
    
    for(int i=0; i<20; i++){
        outputFile << cacheSizes[i] << "," << optResults[i] << "," << lruResults[i] << "," << fifoResults[i] << "," << randomResults[i] << "," << clockResults[i] << endl;
    }
    outputFile.close();
}

void writeLoopingSequential(int cacheSizes[],vector<int> loopingSequential){
    long double optResults[20];
    long double lruResults[20];
    long double fifoResults[20];
    long double randomResults[20];
    long double clockResults[20];
    
    for(int i=0; i < 20; i++){
        optResults[i] = opt(cacheSizes[i], loopingSequential);
        lruResults[i] = lru(cacheSizes[i], loopingSequential);
        fifoResults[i] = fifo(cacheSizes[i], loopingSequential);
        randomResults[i] = random(cacheSizes[i], loopingSequential);
        clockResults[i] = clock(cacheSizes[i], loopingSequential);
    }
    
    ofstream outputFile;
    outputFile.open("looping.csv");
    
    //create the column headers
    outputFile << "#cache" << "," << "OPT" << "," << "LRU" << "," << "FIFO" << "," << "RAND" << "," << "CLOCK" << endl;
    
    outputFile << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << endl;
    
    for(int i=0; i<20; i++){
        outputFile << cacheSizes[i] << "," << optResults[i] << "," << lruResults[i] << "," << fifoResults[i] << "," << randomResults[i] << "," << clockResults[i] << endl;
    }
    outputFile.close();
}


int main(int argc, char* argv[]){
    cout << "NOTE: This program will take a while to run especially with an input of page accesses of 10,000. It can range from 6-7 minutes!!!" << endl;
    int numPages = 0;
    int numPageAccesses = 0;
    int cacheSizes[] = {5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
    vector<int> noLocality, loopingSequential, locality80_20;
    
    
    if (argc != 3) {
        cout << "Error! Wrong number of arguments" << endl;
        return 1;
    }
    else {
    
        try {
            numPages = stoi(argv[1]);
            numPageAccesses = stoi(argv[2]);
        }
        catch (...){
            cout << "ERROR! Wrong format of arguments" << endl;
            return 1;
        }
    }
    
    uniform_int_distribution<int> distribution(0, numPages-1);
    //creates pages accesses that follow the 80:20 locality
    locality80_20 = create80_20locality(numPages, numPageAccesses);
    
    for(int i = 0; i < numPageAccesses; i++){
        int r = distribution(engine);
        noLocality.push_back(r); //no locality is random order of page accesses
        loopingSequential.push_back(i % numPages); //creates sequential looping by going through 0 to maxpage by modding with total number of pages
    }
    
    writeNoLocalityCSV(cacheSizes, noLocality);
    write80_20LocalityCSV(cacheSizes, locality80_20);
    writeLoopingSequential(cacheSizes, loopingSequential); 
    return 0;
}


