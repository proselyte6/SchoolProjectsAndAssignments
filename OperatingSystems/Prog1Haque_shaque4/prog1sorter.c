#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include "timer.h"




int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}


int main(int argc, char **argv, char *envp[]) {
   
    int num_integers = 100;
    int min_int = 1;
    int max_int = 255;
    bool seed = false;
    bool output_stdout = true;
    bool input_stdin = true;
    bool count_stdout = true;
    bool num_integers_specified = false;
    char* inputFileName;
    char* outputFileName;
    char* countFileName;
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
                num_integers_specified = true;
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
        } else if ( strcmp(argv[i], "-i") == 0){
            if ( strstr(argv[i+1], ".txt") == NULL){
                fprintf(stderr, "ERROR: wrong format of arguments!\n");
                exit(1);
            }
            
            input_stdin = false;
            inputFileName = argv[i+1];
            continue;
        } else if ( strcmp(argv[i], "-o") == 0){
            if ( strstr(argv[i+1], ".txt") == NULL){
                fprintf(stderr, "ERROR: wrong format of arguments!\n");
                exit(1);
            }
            
            output_stdout = false;
            outputFileName = argv[i+1];
            continue;
        } else if (strcmp(argv[i], "-c") == 0) {
            if ( strstr(argv[i+1], ".txt") == NULL){
                fprintf(stderr, "ERROR: wrong format of arguments!\n");
                exit(1);
            }
            
            count_stdout = false;
            countFileName = argv[i+1];
            continue;
            
            
        } else if ( strncmp(argv[i], "-", 1) == 0){
            fprintf(stderr, "This is my usage string\n");
            exit(1);
        } else {
            continue;
        }
        
    }
    
    //start timer
    startTimer();
    
    char buff[255];
    int *myints;
    myints = (int *) malloc (num_integers * sizeof(int));
    if (myints == NULL) {
        perror("Error with myints: ");
        exit(1);
    }
    int index = 0;
    char num_integers_generator[9];
    
    
    if (input_stdin == false){
        FILE *inputFile;
        inputFile = fopen(inputFileName, "r");
        
        
       fgets(num_integers_generator, sizeof(num_integers_generator) , inputFile);
        num_integers_generator[strcspn(num_integers_generator, "\n")] = '\0';
        
        
        if (num_integers_specified == true){
            if (num_integers == atoi(num_integers_generator)){
                //now add to some array all the ints
                //add all the ints NEEDED to the buff
                while (fgets(buff, sizeof(buff), inputFile)){
                    buff[strcspn(buff, "\n")] = '\0';
                    myints[index] = atoi(buff);
                    index = index + 1;
                }
                
            } else {
                fprintf(stderr, "ERROR: num_integers are not equal in generator and sorter program\n");
                exit(1);
            }
        } else {
            if (num_integers < atoi(num_integers_generator)){
                //only read up to num_integers
                while (fgets(buff, sizeof(buff), inputFile)){
                    buff[strcspn(buff, "\n")] = '\0';
                    
                    if (index >= num_integers){
                        break;
                    } else {
                        myints[index] = atoi(buff);
                        index = index + 1;
                    }
                }
            } else {
                //read the whole file
                while (fgets(buff, sizeof(buff), inputFile)){
                    buff[strcspn(buff, "\n")] = '\0';
                    myints[index] = atoi(buff);
                    index= index + 1;
                }
            }
            
        }
        fclose(inputFile);
        

    } else {
        //read from stdin
        fgets(num_integers_generator, sizeof(num_integers_generator), stdin);
         num_integers_generator[strcspn(num_integers_generator, "\n")] = '\0';
        
        if (num_integers_specified == true){
            if (num_integers == atoi(num_integers_generator)){
                //now add to some  array all the ints
                //add all the ints NEEDED to the buff
                while (fgets(buff, sizeof(buff), stdin)){
                    buff[strcspn(buff, "\n")] = '\0';
                    myints[index] = atoi(buff);
                    index = index + 1;
                }
                
            } else {
                fprintf(stderr, "ERROR: num_integers are not equal in generator and sorter program\n");
                exit(1);
            }
        } else {
            if (num_integers < atoi(num_integers_generator)){
                //only read up to num_integers
                while (fgets(buff, sizeof(buff), stdin)){
                    buff[strcspn(buff, "\n")] = '\0';
                    
                    if (index >= num_integers){
                        break;
                    } else {
                        myints[index] = atoi(buff);
                        index = index + 1;
                    }
                }
            } else {
                //read the whole file
                while (fgets(buff, sizeof(buff), stdin)){
                    buff[strcspn(buff, "\n")] = '\0';
                    myints[index] = atoi(buff);
                    index = index + 1;
                }
            }
        }

        
    }
    
    qsort(myints, num_integers, sizeof(int), compare);

    if (output_stdout == true){
        //write sorted array to screen
        for( int i = 0; i < num_integers; i++){
             fprintf( stdout, "%d\n", myints[i]);
        }
    } else {
        //write sorted array to outputFileName
        FILE *fp;
        fp = fopen(outputFileName, "w+");
        for(int y=0; y < num_integers; y++){
            fprintf( fp, "%d\n", myints[y]);
        }
        fclose(fp);
    }
    
    char* userid = getenv("USER");
    
    if (count_stdout == true){
        //write username id info  to screen
        int count = 0;
        for(int i=0; i < strlen(userid); i++){
                count = 0;
                for(int x = 0; x < num_integers; x++){
                    if ( myints[x] == (int) userid[i]){
                        count = count + 1;
                    }
                }
            fprintf( stdout, "%c\t%d\t%d\n", userid[i], userid[i], count);
        }
        
    } else {
        //write username id info to countFileName
        FILE *f;
        f = fopen(countFileName, "w+");
        int count = 0;
        for(int i=0; i < strlen(userid); i++){
            count = 0;
            for(int x = 0; x < num_integers; x++){
                if ( myints[x] == (int) userid[i]){
                    count = count + 1;
                }
            }
            fprintf( f, "%c\t%d\t%d\n", userid[i], userid[i], count);
        }
        fclose(f);
    }
    
    //end timer
    endTimer();
    calculateTimeDifference();

    free(myints);
    return 0;
}