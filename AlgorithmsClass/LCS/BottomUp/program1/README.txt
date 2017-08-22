To compile (I made a makefile): 

make

to run this command:

./program1 filex.txt filey.txt output1.txt

Then to see the contents of output1.txt, run this command:

open output1.txt

The program uses dynamic programming and the bottom up approach to solve the longest common subsequence problem. The idea is to solve the subproblems first. The solutions are stored in a table LCS[0…m][0…n]. It fills up the table a row at the time from left to right and once the algorithm is finished, the length of the LCS is in LCS[m][n]. To get a LCS, you keep track of the optimal subproblems to choose the right letters. The time complexity is O(mn) where m is the length of sequence X and n is the length of sequence Y because there are only that many table entries. 

I only have a main function, a max function and the LCSBottomUp function.
main:
	Read filex.txt and file.txt and store the sequences in X and Y. Pass those strings and the output file name to be written in into the LCSBottomUp function.

max:
	Given two integer a and b, if a >=b return a else return b.
LCSBottomUp:
	Convert the strings into char arrays to access each letter. Then keeping the timer using clock(), fill up the rows of the table LCS[0…m][0…n]. First fill all the LCS[0][0…n] and LCS[0…m][0] with zeroes. Then check if two letters are equal, if they are, take the value diagonally in the table (a row to the left and a column up) and add 1. if not take the max of the value above it and the value to the right of it, if equal take the value above it. Then starting from LCS[m][n] store in the letters that lead to the LCS. Decrement each value accordingly. Then if any of the strings are longer than 10 just write the length and the running time in the output file, else, display the table and then display the LCS and the running time.
