To compile (I made a makefile):

make

To run this command:

./program2 filex.txt filey.txt output2.txt

Then to see the contents of output2.txt, run this command:

open output2.txt

The program uses the recursive solution to find out the length of the LCS. By seeing the overlapping subproblems property, a recursive solutions creates a recurrence for a value for the optimal solution. The worst case time complexity of this is O(2^n) and happens when the length of the LCS is 0 or when none of the letters match.

I only have a main function, a max function and the LCSRecursive function.
main:
	Read filex.txt and file.txt and store the sequences in X and Y. I then cover the strings into character arrays and time the the recursive function LCSRecursive. After the function is done, I write to the output file, the length of the LCS and the runtime of the algorithm.

max:
	Given two integer a and b, if a >=b return a else return b.

LCSRecursive:

	Start with checking the base case and return 0. Then if if the letters are equal starting from m-1 and n-1 return the function with m-1 and n-1 and add one to it. Otherwise return the max of the function with m and n-1 and the function with m-1 and n. This returns the length of the LCS.