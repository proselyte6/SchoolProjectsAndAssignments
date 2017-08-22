#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv, char *envp[]) {
    int num_integers = 100;
    int min_int = 1;
    int max_int = 255;
    bool seed = false;
    bool output_stdout = true;
    char* outputFileName;
    //srand(time(NULL));
    
   
    
    for(int i = 1; i < argc; i = i + 1){
     
        
        
        if ( strcmp(argv[i], "-u") == 0){
            fprintf(stderr, "This is my usage string\n");
            exit(1);
        } else if ( strcmp(argv[i], "-n") == 0){
            char *ptr;
            long ret = strtol(argv[i+1],&ptr,10);
            if (*ptr == '\0'){
                fprintf(stderr, "ERROR: wrong format of arguments!\n");
                exit(1);
            }
            
            
            if (atoi(argv[i+1]) < 0 || atoi(argv[i+1]) > 1000000){
                fprintf(stderr, "ERROR: num_integers is out of range\n");
                exit(1);
            } else {
                num_integers = atoi(argv[i+1]);
                continue;
            }
            
        } else if ( strcmp(argv[i], "-m") == 0){
            char *ptr;
            long ret = strtol(argv[i+1],&ptr,10);
            if (*ptr == '\0'){
                fprintf(stderr, "ERROR: wrong format of arguments!\n");
                exit(1);
            }
            
            if (atoi(argv[i+1]) < 1){
                fprintf(stderr, "ERROR: min_int is too small\n");
                exit(1);
            } else {
                min_int = atoi(argv[i+1]);
                continue;
            }
            
        } else if ( strcmp(argv[i], "-M") == 0){
            char *ptr;
            long ret = strtol(argv[i+1],&ptr,10);
            if (*ptr == '\0'){
                fprintf(stderr, "ERROR: wrong format of arguments!\n");
                exit(1);
            }
            
            if (atoi(argv[i+1]) > 1000000 || atoi(argv[i+1]) < min_int ){
                fprintf(stderr, "ERROR: max_int is out of range\n");
                exit(1);
            } else {
                max_int = atoi(argv[i+1]);
                continue;
            }
            
        } else if ( strcmp(argv[i], "-s") == 0){
            char *ptr;
            long ret = strtol(argv[i+1],&ptr,10);
            if (*ptr == '\0'){
                fprintf(stderr, "ERROR: wrong format of arguments!\n");
                exit(1);
            }
            
            seed = true;
            srand(strtoul(argv[i+1], NULL, 10));
            continue;
        } else if ( strcmp(argv[i], "-o") == 0){
            if ( strstr(argv[i+1], ".txt") == NULL){
                fprintf(stderr, "ERROR: wrong format of arguments!\n");
                exit(1);
            }
            
            output_stdout = false;
            outputFileName = argv[i+1];
            continue;
        } else if ( strncmp(argv[i], "-", 1) == 0){
            fprintf(stderr, "This is my usage string\n");
            exit(1);
        } else {
            continue;
        }
        
    }
    
    //if '-s' not specified in command line args
    if (seed == false){
        srand(time(NULL));
    }
    
    int *myints;
    myints = (int *) malloc (num_integers * sizeof(int));
    /* check the return value here! */
    if (myints == NULL){
        perror("Error with myints: ");
        exit(1);
    }
    
    for(int x=0; x < num_integers; x++){
        myints[x] = rand();
        while (myints[x] < min_int || myints[x] > max_int){
            myints[x] = rand();
        }
    }
    
    if (output_stdout == true){
        fprintf( stdout, "%d\n", num_integers);
        for(int y=0; y < num_integers; y++){
            fprintf( stdout, "%d\n", myints[y]);
        }
    } else {
        FILE *fp;
        fp = fopen(outputFileName, "w+");
        fprintf(fp, "%d\n", num_integers);
        for(int y=0; y < num_integers; y++){
            fprintf( fp, "%d\n", myints[y]);
        }
        fclose(fp);
    }
    free(myints);
    return 0;
}