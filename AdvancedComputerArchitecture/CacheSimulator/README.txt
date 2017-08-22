The goal of this project is to measure the effectiveness of cache subsystem organizations using traces of memory instructions obtained realistic programs. Each trace contains about 1 million memory instructions with two values provided for each instruction: a flag indicating whether this is a load or a store (L stands for a load, S stands for a store), and the byte memory address targeted by this instruction. Three traces are provided.


Your goal is to write a program in C or C++ that measures the cache hit rate of various data cache organizations and prefetching techniques (note: we are not estimating the instruction cache performance in this project, only the data cache). Specifically, the following cache designs have to be implemented.

1)	[10%] Direct-Mapped Cache. Assume that each cache line has a size of 32 bytes and model the caches sized at 1KB, 4KB, 16KB and 32KB

2)	[20%] Set-Associative Cache. Again, assume that the cache line size is 32 bytes and model a 16KB cache with associativity of 2, 4, 8 and 16. Assume that the least recently used (LRU) replacement policy is implemented.

3)	[20%] Fully-Associative cache. Assume that each cache line is 32 bytes and the total cache size is 16KB. Implement Least Recently Used (LRU) and hot-cold LRU approximation policies.

4)	[10%] Set-Associative Cache with no Allocation on a Write Miss. In this design, if a store instruction misses into the cache, then the missing line is not written into the cache, but instead is written directly to memory. Evaluate this design for the same configurations as in question (2) above.

5)	[20%] Set-Associative Cache with Next-line Prefetching. In this design, the next cache line will be brought into the cache with every cache access. For example, if current access is to line X, then line (x+1) is also brought into the cache, replacing the cache’s previous content. (Do the accesses one at a time; first a regular access and then check for prefetch. However, do not count hits for prefetch because these are not actual program accesses). Evaluate this design for the same configurations as in question (2) above.


6)	[20%] Prefetch-on-a-Miss. This is similar to part (5) above, but prefetching is only triggered on a cache miss.

The code that you submit should compile into a single executable called cache-sim with a simple `make` command. This executable should run all of the caches on the given trace, which will be specified via command line options as follows:
 
./cache-sim input_trace.txt output.txt

Where:

-input_trace.txt – file name of file containing branch trace

-output.txt – file name of file to write output statistics



The output file should have the following format: (an example text file is on Blackboard too with comments, which should not be output by your program)

x,y; x,y; x,y; x,y; x,y;

x,y; x,y; x,y; x,y;

x,y;

x,y;

x,y; x,y; x,y; x,y;

x,y; x,y; x,y; x,y;

x,y; x,y; x,y; x,y;

Where each x,y; pair corresponds to the number of cache hits (x) and the total number of accesses (y) of one of the cache configurations. The first line provides the results for the direct mapped caches, second line for set associative, the third line for the fully associative cache with LRU replacement, the fourth line for the fully associative cache with hot-cold replacement, the fifth for the associative caches without store allocation, the sixth line for associative caches with next line prefetching and the seventh line for associative caches with next line prefetching only for cache misses. The numbers within each line should be separated by a single space.
