#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <sstream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include "CacheSim.h"

using namespace std;



//constructor
CacheSim::CacheSim(string inputFileN) {
    inputFile = inputFileN;
    start_time = std::chrono::high_resolution_clock::now();
    total_references = 0;
}

string CacheSim::directMappedCacheSim(int tableSize, int resultsIndex){

    vector<vector<long long> > cache (tableSize, vector<long long> (32, -1)); //the cache
    
    //everything needed to keep track of hits/misses
    ifstream infile(inputFile);
    string line;
    char instruction_type;
    long long address, cache_line_index, base, cache_index;
    long long cache_hits = 0;
    total_references = 0;
    
    //process input file
    while(getline(infile, line)){
        total_references++; //updates how many total references we have
        
        //parse the input file line by line
        stringstream ss;
        ss << line;
        ss >> instruction_type >> hex >> address;
        
        //calculating the base = address / cache line size
        //then use that to calculate the cache index
        //the cache line index is just address mod cache line size
        base = address / 32;
        cache_index = base % tableSize;
        cache_line_index = address % 32;
        
        //handle cache miss
        if(cache[cache_index][cache_line_index] != address){
            for(int i = 0; i < 32; i++){
                cache[cache_index][i] = base*32+i; //fill in the cache line
            }
            
        } else {
            cache_hits++; //cache hit
        }
    }
    
    infile.close();
    
    //this is just for parsing a string of output and returns the total cache hits and total referenced
    stringstream r;
    if (resultsIndex == 3){
        r << cache_hits << "," << total_references << ";";
    } else {
        r << cache_hits << "," << total_references << "; ";
    }
    string results = r.str();
    return results;
}

string CacheSim::setAssociativeCacheSim(int associativity, int resultsIndex){
    // 16kb * 1024b / 32b = 512
    //since its set associative divide 512 by associativity to get the cache entries/sets
    long long cache_entries = 512/associativity;
    struct info tmp;
    tmp.last_used_time = -1;
    tmp.cache_line.resize(32, -1);
    
    //n way cache, with the number of entries we need per line
    vector< vector< struct info > > cache (associativity, vector < struct info> (cache_entries,  tmp));
    
    //everything needed to keep track of hits/misses
    ifstream infile (inputFile);
    string line;
    char instruction_type;
    long long address, cache_line_index, base, cache_index;
    long long cache_hits = 0;
    total_references = 0;
    
    //process input file
    while (getline(infile, line)){
        bool hit = false; //keeps track if we have a hit in the set
        total_references++; //update total references
        
        //parse the input file line by line
        stringstream ss;
        ss << line;
        ss >> instruction_type >> hex >> address;
        
        //calculating the base = address / cache line size
        //then use that to calculate the cache index
        //the cache line index is just address mod cache line size
        base = address / 32;
        cache_index = base % cache_entries;
        cache_line_index = address % 32;
        
        for (unsigned int i = 0; i <cache.size(); i++){
            //cache hit and update last used time
            if (cache[i][cache_index].cache_line[cache_line_index] == address){
                cache_hits++;
                cache[i][cache_index].last_used_time = chrono::duration<double, milli> (chrono::high_resolution_clock::now() - start_time).count();
                hit = true;
                break;
            }
        }
        
        //miss
        if(!hit){
            double min = 99999999999999; //keeps track of the least recently used entry
            int victim_index = -1;
            
            //look for right slot to replace
            for(unsigned int i = 0; i < cache.size(); i++){
                if(cache[i][cache_index].last_used_time < min){
                    min = cache[i][cache_index].last_used_time;
                    victim_index = i;
                }
            }
            
            //replace the victim
            cache[victim_index][cache_index].last_used_time = chrono::duration<double, milli> (chrono::high_resolution_clock::now() - start_time).count();
            for(unsigned int i = 0; i < cache[victim_index][cache_index].cache_line.size(); i++){
                cache[victim_index][cache_index].cache_line[i] = base * 32 + i;
            }

        }
    }
    
    //this is just for parsing a string of output and returns the total cache hits and total referenced
    infile.close();
    stringstream r;
    if (resultsIndex == 3){
        r << cache_hits << "," << total_references << ";";
    } else {
        r << cache_hits << "," << total_references << "; ";
    }
    string results = r.str();
    return results;

    
}

string CacheSim::fullyAssociativeCacheSim(string replacementPolicy){
    long long retVal = -1; //return value
    string results;
    
    if (replacementPolicy.compare("LRU") == 0){
         results = setAssociativeCacheSim(512,3); //if LRU, just use set associative cach sim but use 3 so its one set
    } else if (replacementPolicy.compare("Hot-Cold") == 0){
        int cache_entries = 512; //16kb * 1024b / 32b = 512
        vector<int> hot_cold(cache_entries-1,0); //array implementation of hot-cold binary tree but using vector cause I like vectors
        
        //everything needed to keep track of hits/misses
        struct info tmp;
        tmp.last_used_time = -1;
        tmp.cache_line.resize(32, -1);
        vector<struct info> cache (cache_entries, tmp);
        ifstream infile (inputFile);
        string line;
        char instruction_type;
        long long address, base;
        long long cache_hits = 0;
        total_references = 0;
        
        //process input file
        while(getline(infile, line)){
            total_references++; //update total references
            
            //parse the input file line by line
            stringstream ss;
            ss << line;
            ss >> instruction_type >> hex >> address;
            
            //the base is jsut the address but i calculate it as such to make sure its int he right format
            //the cache line index is just address mod cache line size
            base = (address/32)*32;
            bool hit = false;
            int hit_index = -1;
            int cache_line_index = address % 32;
            for(unsigned int i=0; i < cache.size(); i++){
                //hit update, the hit index
                if(cache[i].cache_line[cache_line_index] == address){
                    hit = true;
                    hit_index = i;
                    break;
                }
            }
            int hot_cold_index = -1;
            //cache hit and update hot cold bits
            if(hit){
                cache_hits++;
                //location in hot cold tree to update
                hot_cold_index = hit_index + cache_entries -1;
                //backtrace through the tree to updat the bit
                while(hot_cold_index != 0){
                    //right child
                    if(hot_cold_index % 2 == 0){
                        hot_cold_index = (hot_cold_index-2)/2;
                        hot_cold[hot_cold_index] = 0;
                    //left child
                    } else {
                        hot_cold_index = (hot_cold_index - 1)/2;
                        hot_cold[hot_cold_index] = 1;
                    }
                }
            //cache miss
            } else {
                int victim_index = -1;
                hot_cold_index = 0; //hold the index of the cache line going to be replaced but represented as  tree
                for(int i = 0; i < log2(cache_entries); i++){
                    //update the bit
                    if(hot_cold[hot_cold_index] == 0){
                        hot_cold[hot_cold_index] = 1;
                        hot_cold_index = hot_cold_index * 2 + 1;
                    } else {
                        hot_cold[hot_cold_index] = 0;
                        hot_cold_index = hot_cold_index * 2 + 2;
                    }
                }
                //convert hot cold index to the victime index in the actual cache
                victim_index = hot_cold_index - (cache_entries-1);
                //update the cache line
                for(unsigned int i = 0; i < cache[victim_index].cache_line.size(); i++){
                    cache[victim_index].cache_line[i] = base + i;
                }
            }
        }
        
        //creating  the result string
        retVal = cache_hits;
        infile.close();
        stringstream r;
        r << cache_hits << "," << total_references << ";";
        results = r.str();
        
    }
    return results;
    
}

string CacheSim::setAssociativeNoAllocationOnWriteMiss( int associativity, int resultsIndex){
    // 16kb * 1024b / 32b = 512
    //since its set associative divide 512 by associativity to get the cache entries/sets
    long long cache_entries = 512/associativity;
    struct info tmp;
    tmp.last_used_time = -1;
    tmp.cache_line.resize(32, -1);
    
    //n way cache, with the number of entries we need per line
    vector< vector< struct info > > cache (associativity, vector < struct info> (cache_entries,  tmp));
    
    //everything needed to keep track of hits/misses
    ifstream infile (inputFile);
    string line;
    char instruction_type;
    long long address, cache_line_index, base, cache_index;
    long long cache_hits = 0;
    total_references = 0;
    
    //process input file
    while (getline(infile, line)){
        bool hit = false; //keep track if we have a hit in the set
        total_references++; //update total referenced
        
        //parse the input file line by line
        stringstream ss;
        ss << line;
        ss >> instruction_type >> hex >> address;
        
        //calculating the base = address / cache line size
        //then use that to calculate the cache index
        //the cache line index is just address mod cache line size
        base = address/32;
        cache_index = base % cache_entries;
        cache_line_index = address % 32;
        
        for (unsigned int i = 0; i < cache.size(); i++){
            //cache hit and update last time used
            if (cache[i][cache_index].cache_line[cache_line_index] == address){
                cache_hits++;
                cache[i][cache_index].last_used_time = chrono::duration<double, milli> (chrono::high_resolution_clock::now() - start_time).count();
                hit = true;
                break;
            }
            
        }
        
        //cache hit and its a load, so write it into the cache
        //if it was a store we dont write it to the cache
        if(!hit && (instruction_type == 'L')){
            
            double min = 99999999999999;//keeps track of the least recently used entry
            int victim_index = -1;
            
            //look for right slot to replace
            for(unsigned int i = 0; i < cache.size(); i++){
                if (cache[i][cache_index].last_used_time < min){
                    min = cache[i][cache_index].last_used_time;
                    victim_index = i;
                }
            }
            
            //replace the victim
            cache[victim_index][cache_index].last_used_time = chrono::duration<double, milli> (chrono::high_resolution_clock::now() - start_time).count();
            for(unsigned int i = 0; i < cache[victim_index][cache_index].cache_line.size(); i++){
                cache[victim_index][cache_index].cache_line[i] = base * 32 + i;
            }
        }
        
    }
    //creating the result string to return
    infile.close();
    stringstream r;
    if (resultsIndex == 3){
        r << cache_hits << "," << total_references << ";";
    } else {
        r << cache_hits << "," << total_references << "; ";
    }
    string results = r.str();
    return results;

    
}

string CacheSim::setAssociativeNextlinePrefetching( int associativity, int resultsIndex){
    // 16kb * 1024b / 32b = 512
    //since its set associative divide 512 by associativity to get the cache entries/sets
    long long cache_entries = 512/associativity;
    struct info tmp;
    tmp.last_used_time = -1;
    tmp.cache_line.resize(32, -1);
    
    //n way cache, with the number of entries we need per line
    vector< vector< struct info > > cache (associativity, vector < struct info> (cache_entries,  tmp));
    
    //everything needed to keep track of hits/misses
    ifstream infile (inputFile);
    string line;
    char instruction_type;
    long long address, cache_line_index, base, cache_index;
    long long cache_hits = 0;
    total_references = 0;
    
    //process input file
    while (getline(infile, line)){
        bool hit = false; //keeps track if we have a hit in the set
        total_references++; //update total references
        
        //parse the input file line by line
        stringstream ss;
        ss << line;
        ss >> instruction_type >> hex >> address;
        
        //calculating the base = address / cache line size
        //then use that to calculate the cache index
        //the cache line index is just address mod cache line size
        base = address / 32;
        cache_index = base % cache_entries;
        cache_line_index = address % 32;
        
        for (unsigned int i = 0; i < cache.size(); i++){
            //cache hit and update last time used
            if (cache[i][cache_index].cache_line[cache_line_index] == address){
                cache_hits++;
                cache[i][cache_index].last_used_time = chrono::duration<double, milli> (chrono::high_resolution_clock::now() - start_time).count();
                hit = true;
                break;
            }
            
        }
        //miss
        if(!hit){
            double min = 99999999999999; //keeps track of the least recently used entry
            int victim_index = -1;
            
            //look for right slot to replace
            for(unsigned int i = 0; i < cache.size(); i++){
                if (cache[i][cache_index].last_used_time < min){
                    min = cache[i][cache_index].last_used_time;
                    victim_index = i;
                }
            }
            
            //replace the victim
            cache[victim_index][cache_index].last_used_time = chrono::duration<double, milli> (chrono::high_resolution_clock::now() - start_time).count();
            for(unsigned int i = 0; i < cache[victim_index][cache_index].cache_line.size(); i++){
                cache[victim_index][cache_index].cache_line[i] = base * 32 + i;
            }
        }
        
        //perform nextline prefetching
        cache_index = (cache_index+1)%cache_entries;
        base++;
        bool nextline_hit = false;
        
        //check if the next line is a hit in place and update its last time used
        for(unsigned int i = 0; i < cache.size(); i++){
            if(cache[i][cache_index].cache_line[0] == (base*32)){
                cache[i][cache_index].last_used_time = chrono::duration<double, milli> (chrono::high_resolution_clock::now() - start_time).count();
                nextline_hit = true;
                break;
            }
        }
        //miss
        if(!nextline_hit){
            int victim_index = -1;
            double min = 9999999999999999;
            
            //find the right victim
            for(unsigned int i = 0; i < cache.size(); i++){
                if(cache[i][cache_index].last_used_time < min){
                    min = cache[i][cache_index].last_used_time;
                    victim_index = i;
                }
            }
            //replacing element at victim index
            cache[victim_index][cache_index].last_used_time = chrono::duration<double, milli> (chrono::high_resolution_clock::now() - start_time).count();
            for(unsigned int i = 0; i < cache[victim_index][cache_index].cache_line.size(); i++){
                cache[victim_index][cache_index].cache_line[i] = base * 32 + i;
            }
            
        }
        
        
    }
    
    //process result string
    infile.close();
    stringstream r;
    if (resultsIndex == 3){
        r << cache_hits << "," << total_references << ";";
    } else {
        r << cache_hits << "," << total_references << "; ";
    }
    string results = r.str();
    return results;


}

string CacheSim::prefetchOnMiss(int associativity, int resultsIndex){
    // 16kb * 1024b / 32b = 512
    //since its set associative divide 512 by associativity to get the cache entries/sets
    long long cache_entries = 512/associativity;
    struct info tmp;
    tmp.last_used_time = -1;
    tmp.cache_line.resize(32, -1);
    
    //n way cache, with number of entries we need per line
    vector< vector< struct info > > cache (associativity, vector < struct info> (cache_entries,  tmp));
    
    //everything need to keep track of hits/misses
    ifstream infile (inputFile);
    string line;
    char instruction_type;
    long long address, cache_line_index, base, cache_index;
    long long cache_hits = 0;
    total_references = 0;
    
    //process input file
    while (getline(infile, line)){
        bool hit = false; //keeps track if we have a hit in the set
        total_references++; //update total references
        
        //parse the input file line by line
        stringstream ss;
        ss << line;
        ss >> instruction_type >> hex >> address;
        
        //calculating the base = address / cache line size
        //then use that to calculate the cache index
        //the cache line index is just address mod cache line size
        base = address/32;
        cache_index = base % cache_entries;
        cache_line_index = address % 32;
        
        for (unsigned int i = 0; i < cache.size(); i++){
            //cache hit and update last time used
            if (cache[i][cache_index].cache_line[cache_line_index] == address){
                cache_hits++;
                cache[i][cache_index].last_used_time = chrono::duration<double, milli> (chrono::high_resolution_clock::now() - start_time).count();
                hit = true;
                break;
            }
            
        }
        
        //miss
        if(!hit){
            
            double min = 99999999999999; //keep track of least recently used entry
            int victim_index = -1;
            
            //looking for the right slot to replace
            for(unsigned int i = 0; i < cache.size(); i++){
                if (cache[i][cache_index].last_used_time < min){
                    min = cache[i][cache_index].last_used_time;
                    victim_index = i;
                }
            }
            
            //replace victim
            cache[victim_index][cache_index].last_used_time = chrono::duration<double, milli> (chrono::high_resolution_clock::now() - start_time).count();
            for(unsigned int i = 0; i < cache[victim_index][cache_index].cache_line.size(); i++){
                cache[victim_index][cache_index].cache_line[i] = base * 32 + i;
            }
        }
        
        //nextline prefetching only on miss
        if (!hit){
        
            cache_index = (cache_index+1)%cache_entries;
            base++;
            bool nextline_hit = false;
        
            //check if the next line is a hit in place and update its last time used
            for(unsigned int i = 0; i < cache.size(); i++){
                if(cache[i][cache_index].cache_line[0] == (base*32)){
                    cache[i][cache_index].last_used_time = chrono::duration<double, milli> (chrono::high_resolution_clock::now() - start_time).count();
                    nextline_hit = true;
                    break;
                }
            }
            
            
            if(!nextline_hit){
                int victim_index = -1;
                double min = 9999999999999999;
                
                //find the victim
                for(unsigned int i = 0; i < cache.size(); i++){
                    if(cache[i][cache_index].last_used_time < min){
                        min = cache[i][cache_index].last_used_time;
                        victim_index = i;
                    }
                }
                //replacing element at victim index
                cache[victim_index][cache_index].last_used_time = chrono::duration<double, milli> (chrono::high_resolution_clock::now() - start_time).count();
                for(unsigned int i = 0; i < cache[victim_index][cache_index].cache_line.size(); i++){
                    cache[victim_index][cache_index].cache_line[i] = base * 32 + i;
                }
            
            }
        
        }
    }
    
    //process input string
    infile.close();
    stringstream r;
    if (resultsIndex == 3){
        r << cache_hits << "," << total_references << ";";
    } else {
        r << cache_hits << "," << total_references << "; ";
    }
    string results = r.str();
    return results;


}