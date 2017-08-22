//
//  LCSBottomUp.cpp
//  program1
//
//  Created by Shafkat Haque on 3/10/16.
//  Copyright © 2016 Shafkat Haque. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>

using namespace std;

int max(int a, int b){
    if (a >= b){
        return a;
    } else {
        return b;
    }
}

void LCSBottomUP(string filex, string filey, string outputFile){
    int m = filex.length();
    int n = filey.length();
    int LCS[m+1][n+1];
    
    char x[m];
    char y[n];
    
    strcpy(x, filex.c_str());
    strcpy(y, filey.c_str());
    
    clock_t t1, t2;
    t1= clock();
    
    for (int i=0; i <= m; i++){
        for (int j=0; j<= n; j++){
            //fill up rows of 0 and 0 with 0
            if (i == 0 || j == 0){
                LCS[i][j] = 0;
            } else if (x[i-1] == y[j-1]){
                LCS[i][j] = LCS[i-1][j-1]+1;
            } else {
                LCS[i][j] = max(LCS[i-1][j],LCS[i][j-1]);
            }
        }
    }
    
    t2 = clock();
    float diff((float)t2-(float)t1);
    
    int LCSindex = LCS[m][n];
    char lcs[LCSindex+1];
    lcs[LCSindex] = '\0';
    
    
    int i = m;
    int j = n;
    while (i > 0 && j > 0){
        if (x[i-1] == y[j-1]){
            lcs[LCSindex-1] = x[i-1];
            i--; j--; LCSindex--;
        } else if (LCS[i-1][j] > LCS[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    
    if ( m > 10 || n > 10){
        ofstream output(outputFile);
        if (output.is_open()){
            output << "The Length of the LCS is " << LCS[m][n] << endl;
            output << "The running time of the algorithm is " << diff << endl;
            output.close();
        }
    } else {
        ofstream output(outputFile);
        if (output.is_open()){
            for (int a = 0; a <=m; a++){
                for (int b = 0; b <= n; b++){
                    output << LCS[a][b] << " ";
                }
                output << endl;
            }
            output << "A longest common subsequence is " << lcs << endl;
            output << "The running time of the algorithm " << diff << endl;
            output.close();
        }
    }
}l
int main(int argc, const char * argv[]) {
    if (argc != 4){
        cout << "Please enter such as ./program1 <filex.txt> <filey.txt> <output1.txt>" << endl;
        return -1;
    }
    
    string x;
    string y;
    
    //stores x from filex.txt
    ifstream filex(argv[1]);
    if (filex.is_open()){
            string line;
        while (getline (filex, line)){
            x = line;
        }
        filex.close();
    }
    
    //stores y from file.txt
    ifstream filey(argv[2]);
    if (filey.is_open()){
        string line;
        while (getline (filey, line)){
            y = line;
        }
        filey.close();
    }
    
    LCSBottomUP(x,y,argv[3]);
    
    return 0;
}
