#include <stdio.h> // To use printf and other function.
#include <assert.h> // To use assert function.
#include <unistd.h> // To use pid.
#include <stdlib.h> // To use atoi function to change char* to int.
#include <sys/wait.h> // To use wait function.

int main(int argc, char* argv[]){
    assert( argc == 3 ); // Exec only input val on cmd is 3.

    FILE* file = fopen(argv[1], "r");

    size_t p_n = atoi(argv[2]);

    assert( p_n < 17 || p_n > 3 );

    int pipe_fd[2], c_n = 0;
    pipe(pipe_fd);

    printf("p_n : %d\n", p_n);

    pid_t c_pid, pid;

    printf("original PID : %d\n", getpid());

    for(size_t i = 1; i < p_n; i++){
        pid = fork();

        if(pid == 0){
            //printf("I'm child!\n");
        }
        else if(pid != 0){
            //printf("I'm parent.\n");
            c_pid = getpid();
            c_n = i;
            printf("%dth pid : %d\n", c_n, c_pid);
            pid_t a = wait('\0');
            break;
        }
        else{
            //printf("I'm last.\n");
            c_pid = getpid();
            c_n = i;
            printf("%dth pid : %d\n", c_n, c_pid);
            pid_t a = wait('\0');
            break;
        }
    }


    printf("%dth program has PID : %d\n", c_n, c_pid);

}