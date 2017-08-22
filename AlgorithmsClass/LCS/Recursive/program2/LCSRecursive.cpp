//
//  LCSRecursive.cpp
//  program1
//
//  Created by Shafkat Haque on 3/10/16.
//  Copyright © 2016 Shafkat Haque. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;


int max(int a, int b){
    if (a >= b){
        return a;
    } else {
        return b;
    }
}

int LCSRecursive(char *x, char *y, int m, int n){
    if (m == 0 || n == 0){
        return 0;
    }
    if (x[m-1] == y[n-1]){
        return 1+LCSRecursive(x,y,m-1,n-1);
    } else {
        return max(LCSRecursive(x,y,m,n-1),LCSRecursive(x,y,m-1,n));
    }
}


int main(int argc, const char * argv[]) {
    if (argc != 4){
        cout << "Please enter such as ./program2 <filex.txt> <filey.txt> <output1.txt>" << endl;
        return -1;
    }
    
    string xstring;
    string ystring;
    
    //stores x from filex.txt
    ifstream filex(argv[1]);
    if (filex.is_open()){
        string line;
        while (getline (filex, line)){
            xstring = line;
        }
        filex.close();
    }
    
    //stores y from file.txt
    ifstream filey(argv[2]);
    if (filey.is_open()){
        string line;
        while (getline (filey, line)){
            ystring = line;
        }
        filey.close();
    }

    char x[xstring.length()];
    char y[ystring.length()];
    
    strcpy(x , xstring.c_str());
    strcpy(y , ystring.c_str());
    
    
    clock_t t1, t2;
    t1 = clock();
    int LCSlength = LCSRecursive(x,y,xstring.length(),ystring.length());
    t2 = clock();
    float diff((float)t2 - (float)t1);
    
    ofstream output(argv[3]);
    if (output.is_open()){
        output << "The Length of the LCS is " << LCSlength << endl;
        output << "The runtime of the algorithm is " << diff << endl;
        output.close();
    }


    
    
    return 0;
}
