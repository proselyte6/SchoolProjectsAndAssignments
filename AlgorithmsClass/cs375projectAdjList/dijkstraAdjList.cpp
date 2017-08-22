// CS 375: Design & Analysis of Algorithms
// Final Project / Presentation

// Adjacency List Implementation of Dijkstra's Algorithm
// Shafkat Haque & Rachael Wang

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

using namespace std;

// A node in an adjacency list
struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
};

// An adjacency list that just contains a pointer to the first element in the list
struct AdjList
{
    struct AdjListNode *head;
};

// The graph is an array of adjacency lists and the size will be the number of vertices (V)
struct Graph
{
    int V;
    struct AdjList* array;
};

//Function for creating a new node
struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode =
    (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

//Function for creating a graph (array of adj lists) of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
    
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    
    return graph;
}

//adds an edge to graph
void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

//node for the min heap
struct MinHeapNode
{
    int  v;
    int distance;
};

//min heap struct
struct MinHeap
{
    int size;      // current number of nodes in the heap
    int capacity;  // heap's capacity
    int *pos;     //needed for decreaseKey()
    struct MinHeapNode **array;
};

//function to create a min heap node
struct MinHeapNode* newMinHeapNode(int v, int distance)
{
    struct MinHeapNode* minHeapNode =
    (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->distance = distance;
    return minHeapNode;
}

//function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
    (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
    (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

//function for swapping two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// function for min heapify at an index
void minHeapify(struct MinHeap* minHeap, int index)
{
    int smallest, left, right;
    smallest = index;
    left = 2 * index + 1;
    right = 2 * index + 2;
    
    if (left < minHeap->size &&
        minHeap->array[left]->distance < minHeap->array[smallest]->distance )
        smallest = left;
    
    if (right < minHeap->size &&
        minHeap->array[right]->distance < minHeap->array[smallest]->distance )
        smallest = right;
    
    if (smallest != index)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *indexNode = minHeap->array[index];
        
        // Swap positions
        minHeap->pos[smallestNode->v] = index;
        minHeap->pos[indexNode->v] = smallest;
        
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[index]);
        
        minHeapify(minHeap, smallest);
    }
}

//function to check if a min heap is empty
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}

//function to extract minimum (first/top) node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
    
    //copy the first/top node since it's the minimum value
    struct MinHeapNode* top = minHeap->array[0];
    
    //replace the first node with the last one
    struct MinHeapNode* last = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = last;
    
    // update position of last node
    minHeap->pos[top->v] = minHeap->size-1;
    minHeap->pos[last->v] = 0;
    
    // reduce heap size and heapify
    --minHeap->size;
    minHeapify(minHeap, 0);
    
    return top;
}

//function to decreasy distance value of a given vertex v.
void decreaseKey(struct MinHeap* minHeap, int v, int distance)
{
    //get the index of v from heap array
    int i = minHeap->pos[v];
    
    //update the node's distance
    minHeap->array[i]->distance = distance;
    
    // traverse up while the complete binary tree is not heapified
    // O(Logn) - since it goes through the binary tree
    while (i && minHeap->array[i]->distance < minHeap->array[(i - 1) / 2]->distance)
    {
        // swap node with its predecessor
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
        
        // move to predecessor index
        i = (i - 1) / 2;
    }
}

//function to check if a vertex is in the min heap
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
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
int printDijkstraAdjList(int distance[], int shortPathTree[], int V) {
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

//function to implement adjacency list representation for dijkstra's algorithm that calulates distances of shortest paths from a source vertex to all vertices.
void dijkstraAdjList(struct Graph* graph, int source)
{
    int V = graph->V;//number of vertices in graph
    int distance[V]; //distance from the source vertex
    int shortPathTree[V];
    
   
    struct MinHeap* minHeap = createMinHeap(V);
    
    // initialize min heap with all vertices with distance value of all vertices
    for (int v = 0; v < V; ++v)
    {
        shortPathTree[0] = -1;
        distance[v] = INT_MAX; //set distance value to infinity
        minHeap->array[v] = newMinHeapNode(v, distance[v]);
        minHeap->pos[v] = v;
    }
    
    //src vertex distance is 0 since it has to be extracted first
    minHeap->array[source] = newMinHeapNode(source, distance[source]);
    minHeap->pos[source]   = source;
    distance[source] = 0;
    decreaseKey(minHeap, source, distance[source]);
    
    minHeap->size = V;
    
    
    int x = 0;
   //min heap contains all nodes whose shortest distance is not yet finalized, but will be once empty
    while (!isEmpty(minHeap))
    {
        // extract the vertex with minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        
        //visit all adjacent vertices of the extracted vertex and update their distance values
        
        struct AdjListNode* visit = graph->array[u].head;
        
        while (visit != NULL)
        {
            int v = visit->dest;
            
            //if shortest distance to v is not finalized yet update the distance and the heap
            if (isInMinHeap(minHeap, v) && distance[u] != INT_MAX && visit->weight + distance[u] < distance[v]){
                shortPathTree[v] = u;
                distance[v] = distance[u] + visit->weight;
                decreaseKey(minHeap, v, distance[v]);
            }
            visit = visit->next;
        }
    }
    
    
    printDijkstraAdjList(distance, shortPathTree, V);
}



int main()
{
    //TEST CASE 1 : 9 VERTICES
    int V = 9;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 3);
    addEdge(graph, 0, 4, 8);
    addEdge(graph, 1, 0, 4);
    addEdge(graph, 1, 5, 2);
    addEdge(graph, 1, 6, 9);
    addEdge(graph, 2, 0, 3);
    addEdge(graph, 2, 6, 7);
    addEdge(graph, 3, 6, 2);
    addEdge(graph, 4, 3, 2);
    addEdge(graph, 4, 5, 3);
    addEdge(graph, 5, 1, 4);
    addEdge(graph, 5, 4, 5);
    addEdge(graph, 5, 6, 4);
    addEdge(graph, 6, 3, 9);
    addEdge(graph, 6, 5, 1);
    addEdge(graph, 6, 7, 6);
    addEdge(graph, 7, 0, 3);
    addEdge(graph, 7, 6, 2);
    addEdge(graph, 7, 8, 9);
    addEdge(graph, 8, 2, 5);
    addEdge(graph, 8, 5, 3);
    addEdge(graph, 8, 7, 6);
    
    //clock_t t1, t2;
    //t1 = clock();
    //dijkstraAdjList(graph, 0);
    //t2 = clock();
    //float diff((float)t2-(float)t1);
    //printf("Time it took to run: %f\n" , diff);
    
    //TEST CASE 2 : Sparse graph 5 vertices and 5 edges
    V = 5;
    struct Graph* graph2 = createGraph(V);

    addEdge(graph2, 0, 1, 2);
 
    addEdge(graph2, 0, 3, 3);


    addEdge(graph2, 1, 4, 5);
    addEdge(graph2, 3, 1, 2);
    addEdge(graph2, 3, 2, 5);
    
    clock_t t1, t2;
    t1 = clock();
    dijkstraAdjList(graph2, 0);
    t2 = clock();
    float diff((float)t2-(float)t1);
    printf("Time it took to run: %f\n" , diff);
    
    //Test case 3
    struct Graph* graph3 = createGraph(V);
    addEdge(graph3, 0 ,0, 17);
    addEdge(graph3, 0, 1, 3);
    addEdge(graph3, 0, 2, 23);
    addEdge(graph3, 0, 3, 24);
    addEdge(graph3, 0, 4, 9);
    addEdge(graph3, 1, 0, 2);
    addEdge(graph3, 1, 1, 8);
    addEdge(graph3, 1, 2, 11);
    addEdge(graph3, 1, 3, 7);
    addEdge(graph3, 1, 4, 5);
    addEdge(graph3, 2, 0, 6);
    addEdge(graph3, 2, 1, 1);
    addEdge(graph3, 2, 2, 4);
    addEdge(graph3, 2, 3, 8);
    addEdge(graph3, 2, 4, 1);
    addEdge(graph3, 3, 0, 5);
    addEdge(graph3, 3, 1, 2);
    addEdge(graph3, 3, 2, 5);
    addEdge(graph3, 3, 3, 1);
    addEdge(graph3, 3, 4, 4);
    addEdge(graph3, 4, 0, 1);
    addEdge(graph3, 4, 1, 3);
    addEdge(graph3, 4, 2, 3);
    addEdge(graph3, 4, 3, 2);
    addEdge(graph3, 4, 4, 23);
    
//    clock_t t1, t2;
//    t1 = clock();
//    dijkstraAdjList(graph3, 0);
//    t2 = clock();
//    float diff((float)t2-(float)t1);
//    printf("Time it took to run: %f\n" , diff);
    
    
    
    
    return 0;
}