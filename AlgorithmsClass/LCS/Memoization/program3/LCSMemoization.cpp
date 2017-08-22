//
//  LCSMemoization.cpp
//  program3
//
//  Created by Shafkat Haque on 3/10/16.
//  Copyright © 2016 Shafkat Haque. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int LCSmemoization(int m, int n, string xstring, string ystring){\
    int sol1, sol2, sol3;
    int LCS[m+1][n+1];
    
    for (int i = 0; i <= m; i++){
        for (int j=0; j <= n; j++){
            LCS[i][j] = -1;
        }
    }
    
    if (m == 0 || n == 0){
        return 0;
    }
    
    if (LCS[m][n] >= 0){
        return LCS[m][n];
    }
    
    char x[m];
    char y[n];
    
    strcpy(x, xstring.c_str());
    strcpy(y, ystring.c_str());
    
    if (x[m-1] == y[n-1]){
        sol1 = LCSmemoization(m-1,n-1,xstring,ystring);
        LCS[m][n] = sol1+1;
        return sol1+1;
    } else {
        sol2 = LCSmemoization(m-1,n,xstring,ystring);
        sol3 = LCSmemoization(m,n-1,xstring,ystring);
        
        if (sol2 >= sol3){
            LCS[m][n] = sol2;
            return sol2;
        } else {
            LCS[m][n] = sol3;
            return sol3;
        }
    }
}

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
    
    
    clock_t t1, t2;
    t1 = clock();
    int LCSlength = LCSmemoization(x.length(),y.length(),x,y);
    t2 = clock();
    float diff((float)t2 - (float)t1);
    
    ofstream output(argv[3]);
    if (output.is_open()){
        output << "Then Length of the LCS is " << LCSlength << endl;
        output << "The runtime of the algorithm is " << diff << endl;
        output.close();
    }
    

    return 0;
}
