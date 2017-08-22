#include "CacheSim.h"
#include <string>

using namespace std;

int main(int argc, char **argv){
    
    cout << "Please wait! Shouldn't take long than a minute or two" << endl;
    
    //check if right number of args
    if(argc != 3){
        cout << "ERROR! Wrong format of arguments!" << endl;
        exit(1);
    }
    
    // number of cache entries = cache size / cache line size
    // 1024/32 = 32, 4*1024/32 = 128, 16*1024/32 = 512, 32*1024/32 = 1024;
    int directMappedCacheSizes[] = {32, 128, 512, 1024};
    int associativities[] = {2, 4, 8, 16};
    
    //create all the cache simulators for each type of cache we are testing
    CacheSim dm(argv[1]);
    CacheSim sa(argv[1]);
    CacheSim fa(argv[1]);
    CacheSim sanoalloc(argv[1]);
    CacheSim saprefetch(argv[1]);
    CacheSim pom(argv[1]);
    
   
    //this is the results to be written to the output file
    string line[7];
    for (int i = 0; i < 7; i++){
        line[i] = "";
    }
    
    //proceed to call all methods in order
    
    for(int i = 0; i < 4; i++){
        line[0] += dm.directMappedCacheSim(directMappedCacheSizes[i], i);
    
    }
    
    
    for(int i = 0; i < 4; i++){
        line[1] += sa.setAssociativeCacheSim(associativities[i], i);
    }
    

    
    line[2] = fa.fullyAssociativeCacheSim("LRU");
    
   
    
    line[3] = fa.fullyAssociativeCacheSim("Hot-Cold");
    

    
    for(int i = 0; i < 4; i++ ){
        line[4] += sanoalloc.setAssociativeNoAllocationOnWriteMiss(associativities[i], i);
    }
    
    
    
    for(int i = 0; i < 4; i++ ){
        line[5] += saprefetch.setAssociativeNextlinePrefetching(associativities[i], i);
    }
    
 
    
    for(int i = 0; i < 4; i++ ){
        line [6] += pom.prefetchOnMiss(associativities[i], i);
    }
    
    //writing all results to the output file
    
    ofstream outFile(argv[2]);
    
    for(int i = 0; i < 7; i++){
        outFile << line[i] << endl;
    }
    
    outFile.close();
    
    
   
    
    return 0;
}
