//
//  BestFirstSearch.cpp
//  haque_shafkat
//
//  Created by Shafkat Haque on 4/10/16.
//  Copyright © 2016 Shafkat Haque. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <cstdlib>


using namespace std;

int capacity; //capacity of the knapsack
int n; //size of the napsack

//items of the napsack
struct item{
    int profit;
    int weight;
    float profit_per_weight;
    //an overloaded operator to be able to create a priority queue and vector of the type 'item'
    bool operator<(const item &a) const{
        return profit_per_weight < a.profit_per_weight;
    }
};

//node for the state space tree
struct Node{
    int level; //pertains to the number of the item in the array (sorted in decreasing order)
    int total_profit; //current profit of the node
    int total_weight; //current weight of the node
    float bound; //highest possible profit of the node
    //an overloaded operator to be able to create a priority queue and vector of the type 'node'
    bool operator<(const Node &a) const{
        return bound < a.bound;
    }
};


//This function computes the bound of the current node being discovered in the state space tree. The array passed in is just the array of items.
//Looking at the level of the node, add on the weights of each item until the t_weight is <= the capacity.
//Once this is done, use k to check which item couldnt be fully added and then add a fraction of that item by subtracting the total weight from the capacity and multiplying it by the profit/weight
float compute_bound(Node x, item arr[]){
    int j, k; //j is used to check the level of the tree and increment through each item grabbing as many as possible. k will be used to grab a fraction of the kth item
    int t_weight; //total weight
    float bound; //the bound to return
    
    if (x.total_weight >= capacity){ //return 0 is the weight is >= the capacity
        return 0;
    } else {
        bound = (float)x.total_profit;
        j = x.level+1;
        t_weight = x.total_weight;
        while (j <= n && t_weight + arr[j].weight <= capacity){
            t_weight = t_weight + arr[j].weight;
            bound = bound + arr[j].profit;
            j++;
        }
        k = j;
        if (k <= n){
            bound = bound + (capacity-t_weight)*(arr[k].profit_per_weight);
        }
        return bound;
    }
}


//This function takes the nodes that were visited and promising and then out of those nodes, selected the ones that were chose for the optimal solution. The array is jsut the array of items. The idea is to backtrack and if the weight is the same as a level before it, then it means that item is not chosen for the optimal solution.
vector<item> optimalSet(vector<Node> nodes, item arr[]){
    vector<item> optSet; //optimal subset chosen for the solution that will be returned
    
    for (vector<Node>::iterator i = nodes.end(); (i-1) !=nodes.begin();i--){
        if(i -> total_weight == (i-1) -> total_weight && i -> level == ((i-1) -> level)-1){
            optSet.push_back(arr[(i-1) -> level]);
        } else if (i -> total_weight != (i-1) -> total_weight){
            optSet.push_back(arr[i -> level]);
        }
    }
    
    return optSet;
}

//This is the best first search branch and bound function. It takes the array of items and the file to write to.
//First, it creates the root. Then it visits the "yes" child and check if the current weight is <= capcity and if the profit is > maxProfit, and so that maxProfiti is changed. It then checks the bound and is put on the queue if the bound is greater than the maxprofit. It then creates the "no" child and visits it. It also checks if the bound is > than the maxProfit and updates accordingly. The line "if(v.bound > maxProfit)" expands v and checks it if promising. If this does not pass through, then a non promising node was hit, or a leaf node and so we increment to keep the number of leaf nodes visited in the queue. After, the optimal set is found and the data is written to the output file.
void best_first_search_branch_and_bound(item arr[],string outputFile){
    vector<Node> optimalSolution; //keeps track of the items that changed the maxProfit.
    
    int num_nodes_visited = 0; //number of nodes visited
    int num_leaf_nodes=-1; //number of leaf nodes set to -1 because it will count the root as one too
    priority_queue<Node> PQ; //priority queue for the nodes
    Node u, v; //nodes to keep track of, where u will be the child of v and v is whats being popped out of the queue
    
    v.level = 0;
    v.total_weight=0;
    v.total_profit=0;
    v.bound = compute_bound(v,arr);
    int maxProfit = 0; //highest max profit or the optimal solution
    PQ.push(v);
    num_nodes_visited++;
    
    while(!PQ.empty()){
        v = PQ.top();
        PQ.pop();
        
        if(v.bound > maxProfit){ //expand v and checks is v is promising
            u.level = v.level+1; //u child of v
            num_nodes_visited++; //"yes" child visited
            u.total_weight = v.total_weight+arr[u.level].weight;
            u.total_profit = v.total_profit+arr[u.level].profit;
           
            
            if (u.total_weight <= capacity && u.total_profit > maxProfit){
                optimalSolution.push_back(u);
                maxProfit = u.total_profit;
            }
            u.bound = compute_bound(u,arr);
            if (u.bound > maxProfit){
                PQ.push(u);
            }
            
            u.total_weight = v.total_weight;
            num_nodes_visited++; //"no" child visited
            u.total_profit = v.total_profit;
            u.bound = compute_bound(u, arr);
            
            if (u.bound > maxProfit){
                PQ.push(u);
            }
        }
        num_leaf_nodes++;
    }
    
    vector<item> optSet = optimalSet(optimalSolution, arr);
    ofstream output(outputFile);
    if (output.is_open()){
        output << n << "," << maxProfit << "," << optSet.size() << endl;
        output << num_nodes_visited << "," << num_leaf_nodes << endl;
        for (vector<item>::iterator i=optSet.begin(); i != optSet.end(); i++){
            output << i -> weight << "," << i -> profit << endl;
        }
        
        output.close();
    }
}

//This just created an item with its weight, profit and profit per weight
item initialize_item(int weight, int profit){
    item x;
    x.profit = profit;
    x.weight = weight;
    x.profit_per_weight = (float)profit/(float)weight;
    return x;
}

//simple swap method
void swap(item *n1, item *n2){
    item tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}

//Bubblesort to sort the array of items in decreasing order and n is the number of items.
void bubblesort(item arr[], int n){
    int i, j;
    for (i = 1; i < n; i++){
        for ( j = 1; j < n-i; j++){
            if (arr[j].profit_per_weight < arr[j+1].profit_per_weight){
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}


//check for the right number of arguments. Parse the input accordingly to create the array of items and gather info on the number of items and the capacity.
//Sort the array using bubble sort and then call the best first search branch and bound function.
int main(int argc, const char * argv[]) {
    if (argc != 3){
        cout << "Please enter valid input in this format: ./BestFirstSearch <input.txt> <output.txt>" << endl;
        return -1;
    }
    
    int w, p; //temp holder of weight, profit
    item* A; //the array of items
    
   
    int i =0;
    int commaPos;
    
    ifstream inputFile(argv[1]);
    if (inputFile.is_open()){
        string line;
        while (getline(inputFile, line)){
            if (i == 0){
                commaPos = line.find(',');
                n = stoi(line.substr(0,commaPos));
                capacity = stoi(line.substr(commaPos+1));
                A = new item[n+1];
                i++;
            } else {
                commaPos = line.find(',');
                w = stoi(line.substr(0,commaPos));
                p = stoi(line.substr(commaPos+1));
                A[i] = initialize_item(w,p);
                i++;
            }
        }
    }
    
    bubblesort(A,n+1);
    best_first_search_branch_and_bound(A, argv[2]);
    
    
    return 0;
}
