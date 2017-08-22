#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

void signal_handler(int sig){
   
      fprintf(stdout, "EXITING: Process with pid =%d, child of ppid=%d\n", getpid(), getppid());
    exit(0);
    
}


void printAllChildren(int *src) {
    int dest[32];
    memcpy(dest, src, 32*sizeof(int));
    
    fprintf(stdout, "\n");
    for (int i = 0; i < 32; i++){
        if (dest[i] == 0){
            fprintf(stdout, "\n");
            return;
        }
        fprintf(stdout,"%d\n", dest[i]);
    }
    fprintf(stdout, "\n");
    
}



void printAlive(){
    fprintf(stdout, "ALIVE: Process with pid =%d, child of ppid=%d\n",  getpid(), getppid());
}

//create child( num_procs, myfifo);
void createChild(int num_procs, char *myfifo, int current_pos, int *sptr, int *pids, int root_pid) {
    
    if (num_procs == 1){
        //do something with myfifo
        
        *sptr = getpid(); //get parent pid in the value of sptr
        memcpy(&pids[current_pos], sptr, sizeof(int) ); // sptr -> pids[current_pos]
        printAlive();
        /* write "Hi" to the FIFO */
        
        int fd;
       
        
        fd = open(myfifo, O_RDWR | O_NONBLOCK);
        
        write(fd, "Hi", sizeof("Hi"));
     
        close(fd);
       
        
        signal(SIGUSR1, signal_handler);
        pause();
        //exit(0);
      
    }
    
    
    
    
    int pid;
    int pfds[2];
    
    if (pipe(pfds) == -1) {
        perror("pipe");
        exit(1);
    }
    
    pid = fork();

    if (pid == 0) {
        // Child reads from the UNAMED pipe
        /* close the write end */
        close(pfds[1]);
        
        /* read message from child through the read end */
        if( read(pfds[0], &num_procs, sizeof(num_procs)) <= 0 ) {
            perror("Child reading from UNAMED pipe has failed.");
            exit(1);
        }
        
        //Find out if it is the LEAF child
        
        
        
        signal(SIGUSR1, signal_handler);
        createChild(num_procs, myfifo, current_pos+1, sptr, pids, root_pid);
        pause();
        //exit(0);
    } else if (pid < 0) {
        perror("fork failed");
    } else {
        //parent writes to the UNAMED pipe
        
        /* close the read end */
        close(pfds[0]);
        //decrement the num_procs
        num_procs = num_procs - 1;
        
        //send num)procs
        if(write(pfds[1], &num_procs, sizeof(num_procs)) <= 0) {
            perror("Parent Writing to UNAMED pipe has failed.");
            exit(1);
        }
        
        *sptr = getpid(); //get parent pid in the value of sptr
        memcpy(&pids[current_pos], sptr, sizeof(int) ); // sptr -> pids[current_pos]
        printAlive();
        
        if (getpid() == root_pid){
            return;
        } else {
            wait(NULL);
        
    }
}
}

int main(int argc, char**argv, char *envp[]){
    int *pids; //shared memory object ptr
    int num_procs = 0;
    int shm_fd; //shared memory file descriptor
    
    const char *name = "OS"; //name of shared memory object
    
    if (atoi(argv[1]) < 1 || atoi(argv[1]) > 32){
        fprintf(stderr, "ERROR: num_procs must be between 1 and 32 inclusively!\n");
        exit(1);
    } else {
        num_procs = atoi(argv[1]);
    }
    
    if (num_procs == 1){
        printAlive();
        fprintf(stdout, "\n%d\n", getpid());
        fprintf(stdout, "EXITING: Process with pid =%d, child of ppid=%d\n", getpid(), getppid());
        exit(0);
    }
    
    
    int c;
    int pid;
    int root_pid = getpid();
    
    shm_fd = shm_open(name, O_RDONLY | O_WRONLY, 0666);
    
    // Map space for shared array
    pids = mmap(0, 32*sizeof(int), PROT_READ|PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS, shm_fd, 0);
    if (!pids) {
        perror("mmap failed");
        exit(1);
    }
    memset((void *)pids, 0, 32*sizeof(int));
    
    
    
    //creating the NAMED pipe

    int fd;
    char * myfifo = "/tmp/myfifo";
    char buf[sizeof("Hi")];
    mkfifo(myfifo, 0666);
    fd = open(myfifo, O_RDWR | O_NONBLOCK);
    

   
   
    
  
 
    int *sptr = (int*) malloc(sizeof(int)); //create the shared pointer
    
    createChild(num_procs, myfifo, 0, sptr, pids, root_pid);
    sleep(5);
    
    
  
    read(fd, buf, sizeof("Hi") );
   
    close(fd);
    
   
   
    if ( strcmp (buf, "Hi") == 0){
        
        printAllChildren(pids);
        
    } else {
        printf("Something went wrong!\n");
    }
    
    int *status;
    for(int i = 1; i < 32; i++){
        if (pids[i] == 0){
            break;
        }
        kill(pids[i], SIGUSR1);
        waitpid(pids[i], status ,WNOHANG);
    }
    
    //free everything used
    free(sptr);
    unlink(myfifo);
    shm_unlink(name);
    
    exit(0);
}


