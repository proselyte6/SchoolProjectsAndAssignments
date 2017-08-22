#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


//prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time
//Leaf nodes have no kids
//N (2-4) level process tree, each node has M (1-3) children other than leaf nodes
//if -p leaf processes are to be paused
//if -s leaf processes are to sleep for sleep_time
//if -s, non-leaf processes call wait() for children to finish


//CALL THIS BEFORE CREATING ANY CHILDREN, SLEEPING OR PAUSING
void printAlive(int tree_level, int pid, int ppid){
    fprintf(stdout, "ALIVE: Level %d process with pid =%d, child of ppid=%d\n", tree_level, pid, ppid);
}

//CALL THIS BEFORE EXITING FOR EACH PROCESS
void printExiting(int tree_level, int pid, int ppid){
    fprintf(stdout, "EXITING: Level %d process with pid =%d, child of ppid=%d\n", tree_level, pid, ppid);
}

int main(int argc, char **argv, char *envp[]){
    int num_levels = 0;
    int num_children = 1;
    int sleep_time = 1;
    bool pauseProcess = false;
    
    
    for (int i = 1; i < argc; i = i + 1){
        
        if (strcmp(argv[i], "-u") == 0){
            fprintf(stderr, "This is my usage string\n");
            exit(1);
        } else if (strcmp(argv[i], "-N") == 0){
            
            char *ptr;
            long ret = strtol(argv[i+1],&ptr,10);
            if (*ptr != '\0'){
                fprintf(stderr, "ERROR: wrong format of arguments!\n");
                exit(1);
            }
            
            //0 or 1 no child processes
            if (atoi(argv[i+1]) > 4){
                fprintf(stderr, "ERROR: num_levels cannot be larger than 4\n");
                exit(1);
            } else {
                num_levels = atoi(argv[i+1]);
                continue;
            }
            
        } else if (strcmp(argv[i], "-M") == 0){
            
            
            char *ptr;
            long ret = strtol(argv[i+1],&ptr,10);
            if (ret == 0){
                fprintf(stderr, "ERROR: wrong format of arguments!\n");
                exit(1);
            }
            
            if (atoi(argv[i+1]) > 3){
                fprintf(stderr, "ERROR: num_children cannot be larger than 3\n");
                exit(1);
            } else {
                num_children = atoi(argv[i+1]);
                continue;
            }
            
        } else if (strcmp(argv[i], "-p") == 0){
            pauseProcess = true;
            
            if (argv[i+1] == NULL){
                
            } else if (strcmp(argv[i+1], "-s") == 0){
                fprintf(stderr, "This is my usage string\n");
                exit(1);
            }
            
            
            
        } else if (strcmp(argv[i], "-s") == 0){
            
            char *ptr;
            long ret = strtol(argv[i+1],&ptr,10);
            if (ret == 0){
                fprintf(stderr, "ERROR: wrong format of arguments!\n");
                exit(1);
            }
            
            
            
            sleep_time = atoi(argv[i+1]);
            
        } else if ( strncmp(argv[i], "-", 1) == 0){
            fprintf(stderr, "This is my usage string\n");
            exit(1);
        } else {
            continue;
        } //if ending
        
    }//for loop ending
    
    char* passargs[argc+1];
    passargs[0] = strdup("./prog2tree");
    
    for(int i = 1; i < argc; i++){
        passargs[i] = strdup(argv[i]);
    }
    passargs[argc] = NULL;
    
    int current_level = num_levels - 1;
    
    if (num_levels == 0 || current_level == 0){
        printAlive(0, (int) getpid(), (int) getppid());
        
        if (pauseProcess == true){ //-p specified
            pause();
        } else { //-s specified or none specified
            sleep(sleep_time);
        }
        
        printExiting(0, (int) getpid(), (int) getppid());
        
        exit(0);
    }
    
    printAlive(current_level, (int) getpid(), (int) getppid() );
    pid_t pids[num_children];
    int x = num_children;
    
    for (int y=0; y<num_children; y++){
        pids[y] = fork();
        
        if(pids[y] < 0) { //something went wrong
            fprintf(stderr, "ERROR: somethign went wrong while forking\n");
            exit(1);
        } else if (pids[y] == 0) { //childre
            for(int i=1; i < argc; i++){
                
                if (strcmp(passargs[i],"-N") == 0){
                    sprintf(passargs[i+1], "%d", current_level);
                    
                }
            }
            execvp(passargs[0], passargs);
        }
    }
    
    
    
    int status;
    pid_t pid;
    while (x > 0){
        pid = wait(&status);
        
        --x;
    }
    
    printExiting(current_level, (int) getpid(), (int) getppid());
    
    
    
    
    
    
    
    
    
    
    
    
    
}//main ending