// CS 375: Design & Analysis of Algorithms 
// Final Project / Presentation

// Matrix Representation Implementation of Dijkstra's Algorithm
// Shafkat Haque & Rachael Wang

#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

// Change V value for number of nodes you want in the graph
#define V 5

// Finds the min distance from all vertices not in shortest path tree ----
int minimumDistance(int distance[], bool finalize[]) {
	int min = INT_MAX, minInd;
	for(int i=0; i<V; i++) {
		if(distance[i] <= min && finalize[i] == false) {
			min = distance[i];
			minInd = i;
		}
	}
	return minInd; 			// Min Index
}

// Prints shortest path from source to i ---------------------------------
void outputPath(int shortPathTree[], int i) {
	// If int i is the sourceNode
	if(shortPathTree[i] == -1) {
		return;
	}
	outputPath(shortPathTree, shortPathTree[i]);
	printf("%d ", i);
}

// Prints solution to Dijkstra's in organized format ---------------------
int printDijkstra(int distance[], int shortPathTree[]) {
	int source = 0;
	printf("----------------------------------\n");
	printf("Vertex\t |Dist \t |Path \n");
	printf("----------------------------------");

	for(int i=1; i<V; i++) {
		printf("\n%d -> %d \t | %d\t | %d ", source, i, distance[i], source);
		outputPath(shortPathTree, i);
	}
	printf("\n----------------------------------\n");
}

// Function for Dijkstra's Shortest Path Algorithm -----------------------
// (Uses adjacency matrix representation for graphs) ---------------------
void shortestPath(int graph[V][V], int sourceNode) {
	// Stores shortest path tree
	int shortPathTree[V];
	// Holds the shortest distance from sourceNode to V
	int distance[V];	
	// Set to true if vertex is in the shortest path tree
	// (Or if the distance from sourceNode to V is confirmed)		
	bool finalize[V];	

	// Set all distances to infinity
	// Set all elements in finalize[V] to false --------------------------
	for(int i=0; i<V; i++) {
		finalize[i] = false;
		shortPathTree[0] = -1;
		distance[i] = INT_MAX;	// INT_MAX: max number an int can have
	}
	// -------------------------------------------------------------------

	distance[sourceNode] = 0;	// Initialize distance for sourceNode

	for(int j=0; j<V-1; j++) {
		// Set minimum distance to variable 'min' from unprocessed vertices 
		int min = minimumDistance(distance, finalize);
		finalize[min] = true;

		// Update distances of adjacent vertices 
		for(int k=0; k<V; k++) {
			if(graph[min][k] && !finalize[k] && distance[min] + graph[min][k] < distance[k]) {
				shortPathTree[k] = min;
				distance[k] = distance[min] + graph[min][k];
			}
		}
	}
    
	printDijkstra(distance, shortPathTree);
}

// Main function to test the algorithm -----------------------------------
int main() {
	// TEST CASE 1 : 9 Vertices and 23 edges
//	int graph[V][V] = {{0, 4, 3, 0, 8, 0, 0, 0, 0},
//                       {4, 0, 0, 0, 0, 2, 9, 0, 0},
//                       {3, 0, 0, 0, 0, 0, 7, 0, 0},
//                       {0, 0, 0, 0, 0, 0, 2, 0, 0},
//                       {0, 0, 0, 2, 0, 3, 0, 0, 0},
//                       {0, 4, 0, 0, 5, 0, 4, 0, 0},
//                       {0, 0, 0, 9, 0, 1, 0, 6, 0},
//                     {3, 0, 0, 0, 0, 0, 2, 0, 9},
//                       {0, 0, 5, 0, 0, 3, 0, 6, 0}
//                      };
//    clock_t t1, t2;
//    t1 = clock();
//    shortestPath(graph, 0);
//    t2 = clock();
//    float diff((float)t2-(float)t1);
//    printf("Time it took to run: %f\n" , diff);
    //TEST CASE 2 : Sparse graph 5 vertices and 5 edges
    int graph2[V][V] = {{0, 2, 0, 3, 0},
                       {0, 0, 0, 0, 5},
                       {0, 0, 0, 0, 0},
                      {0, 2, 5, 0, 0},
                       {0, 0, 0, 0, 0}};
   
    
        clock_t t1, t2;
        t1 = clock();
        shortestPath(graph2, 0);
        t2 = clock();
        float diff((float)t2-(float)t1);
        printf("Time it took to run: %f\n" , diff);
    
    //TEST CASE 3 : dense graph 5 vertices and 25 edges
    int graph3[V][V] = {{17, 3, 23, 11, 24},
                        {2, 8, 3, 7, 5},
                        {6, 1, 4, 8, 1},
                        {5, 2, 5, 1, 4},
                        {1, 3, 3, 2, 9}};
    
//    clock_t t1, t2;
//    t1 = clock();
//    shortestPath(graph3, 0);
//    t2 = clock();
//    float diff((float)t2-(float)t1);
//    printf("Time it took to run: %f\n" , diff);

    
    
    return 0;
}