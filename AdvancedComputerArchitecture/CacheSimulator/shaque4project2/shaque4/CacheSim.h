#ifndef CACHESIM_H
#define CACHESIM_H

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
#include <sstream>
#include <chrono>

using namespace std;

//this just used to track instructions for set associative and fully associative since we use LRU and need multiple lines per set
struct info{
    double last_used_time;
    vector<long long> cache_line;
};

class CacheSim{
public:
    CacheSim(string inputFileN);
    string directMappedCacheSim(int tableSize, int resultIndex);
    string setAssociativeCacheSim(int associativity, int resultIndex);
    string fullyAssociativeCacheSim(string replacementPolicy);
    string setAssociativeNoAllocationOnWriteMiss( int associativity, int resultIndex);
    string setAssociativeNextlinePrefetching (int associativity, int resultIndex);
    string prefetchOnMiss (int associativity, int resultIndex);
private:
    long long total_references; //keep track of the total number of instructions
    string inputFile; //the input file name
    chrono::high_resolution_clock::time_point start_time; //starting time used to keep track of what is least recently used (LRU)
};
#endif