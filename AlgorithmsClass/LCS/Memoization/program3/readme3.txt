To compile (I made a makefile):

make 

to run this command:

./program3 filex.txt filey.txt output3.txt

Then to see the contents of output2.txt, run this command:

open output3.txt

The program uses the top to bottom approach or memoization method. This idea is similar to the recursion function and also has the same exponential running time of O(2^n) worst case. The problem with the recursion function is that it calls the same subproblems too many times. Memoization avoids it by checking if the subproblem was already solved by saving the memoized solutions and then acts accordingly. 


I only have a main function, a max function and the LCSMemoization function.
main:
	Read filex.txt and file.txt and store the sequences in X and Y. Then I start the clock and call the LCSmemoization function. Then I write to the output file the length of the LCS and the runtime of the algorithm.

max:
	Given two integer a and b, if a >=b return a else return b.

LCSMemoization:
	Create sol1, sol2, sol3 to hold the solutions to subproblems. Fill up the LCS[0…m][0…n] table with negative 1’s. Check the base cases, if m or n is 0 and if there is already a memoized solution at LCS[m][n]. Convert the strings X and Y into character arrays. Then check, if the letters are equal store in solution 1 by recursively calling LCSMemoization with m-1 and n-1 and store it in LCS[m][n]. Otherwise store sol2 and stol2 with m-1 and n and m and n-1 respectively with a recursive call. Then compare the two and act accordingly.

	