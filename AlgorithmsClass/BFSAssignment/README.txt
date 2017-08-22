To compile the program:

make

To run the program:

./BestFirstSearch input.txt output.txt

This program implements the best-first-search branch and bound algorithm. It uses a state space tree and prunes out. It visits the promising nodes with the highest upper bounds first until the best optimal solution is found. It also uses a priority queue to keep the nodes in order since the the levels of the tree directly responds to the number of the item (sorted in decreasing order).The worst case time complexity would be theta(2^n). However, it will still arrive at an optimal solution faster than BFS and DFS since the nodes are put in a pre-determined order and are visited in a certain way. I didn’t use classes and included everything in one .cpp file. I did create structs though. One struct is for the actual items which contained values for weight, profit and profit per pound. The other struct was the nodes for the space state tree which contained values of the level, total profit, total weight and the bound.
