#include <stdio.h> // To use printf and other function.
#include <assert.h> // To use assert function.
#include <unistd.h> // To use pid.
#include <stdlib.h> // To use malloc, atoi function to change char* to int.
#include <sys/wait.h> // To use wait function.
#include <string.h>
#include <fcntl.h> // To use open func.

int main(int argc, char* argv[]){
    assert( argc == 3 ); // Exec only input val on cmd is 3.
    FILE* file = fopen(argv[1], "r");
    int fd = open(argv[1], O_RDONLY|O_SYNC);
    size_t p_n = atoi(argv[2]);

    assert( p_n < 17 || p_n > 3 );
    int c_n = 0, pos = 1;
    printf("p_n : %d\n", p_n);

    pid_t c_pid, pid;
    printf("original PID : %d\n", getpid());

    int pipe_init[2]; // Pipe connection for the first and last process.
    pipe(pipe_init);

    int pipe_fd_even[2];
    int pipe_fd_odd[2];

    for(size_t i = 0; i < p_n - 1; i++){
        int tmp = 0;
        if(i % 2 == 0)
            pipe(pipe_fd_even);
        else
            pipe(pipe_fd_odd);
        pid = fork();

        if(pid == 0 && i == p_n - 2){
            // Case for the last one. Does not need to make other child process. Thus finish exec.
            if(i % 2 == 0){
                close(pipe_fd_even[1]);
            }
            else{
                close(pipe_fd_odd[1]);
            }
            close(pipe_init[0]);
            c_pid = getpid();
            c_n = i + 1;
            printf("%dth pid : %d\n", c_n, c_pid);
            tmp = 1;
            write(pipe_init[1], &tmp, sizeof(tmp));
        }
        else if(pid != 0){
            // Parent case. Get pid number and current executed trial number and store it. Then wait until all child process is made.
            if(i % 2 == 0){
                close(pipe_fd_even[0]);
                write(pipe_fd_even[1], &tmp, sizeof(tmp));
            }
            else{
                close(pipe_fd_odd[0]);
                write(pipe_fd_odd[1], &tmp, sizeof(tmp));
            }
            c_pid = getpid();
            c_n = i;
            printf("%dth pid : %d\n", c_n, c_pid);
            break;
        }
        else{ // Child case;
            if(i % 2 == 0){
                close(pipe_fd_odd[1]);
                //write(pipe_fd_even[1], &tmp, sizeof(tmp));
            }
            else{
                close(pipe_fd_even[1]);
                //write(pipe_fd_odd[1], &tmp, sizeof(tmp));
            }
        }
        // The other case is child case. So we do not need to consider cause it locates inside of for loop.
    }

    printf("\n");

    if(c_n != 0 && c_n + 1 != p_n){
        close(pipe_init[0]);
        close(pipe_init[1]);
    }
    else if(c_n == 0)
        close(pipe_init[1]);


    int tmp = 0, cnt = 0;
    int n_t;
    if(c_n != p_n - 1)
        n_t = c_n + 1;
    else
        n_t = 0;

    printf("Next # : %d\n", n_t);

    while(1){
        if(c_n != 0){
            if(c_n % 2 == 0) // Process order is even.
                read(pipe_fd_odd[0], &tmp, sizeof(tmp));
            else // Process order is odd.
                read(pipe_fd_even[0], &tmp, sizeof(tmp));
        }
        else
            read(pipe_init[0], &tmp, sizeof(tmp));

        printf("C_n : %d\tRead val : %d\n", c_n, tmp);

        if(tmp == 1){
            printf("%dth program has PID : %d\n", c_n, c_pid);
            char* result;
            char* read_line;
            read_line = malloc(65);
            size_t indicator = 0;
            //result = fgets(read_line, 65, file); // how to approach open and read?
            for(size_t i = 0; i < 65; i++){
                indicator = read(fd, &read_line[i], 1);
                if(indicator == -1)
                    break;
                if(read_line[i] == '\n'){
                    indicator = 1;
                    break;
                }
            }
            printf("strlen : %d, sizeof : %d\n",strlen(read_line), sizeof(read_line) / sizeof(char));
            printf("%d %d |%s|\n", c_pid, c_n, read_line);
            //if( result != NULL ){
            if( indicator == 1 ){
                printf("%d %d %s\n", c_pid, c_n, read_line);
                if(c_n == p_n - 1)
                    write(pipe_init[1], &tmp, sizeof(tmp));
                else if(c_n % 2 == 0) // Process order is even.
                    write(pipe_fd_even[1], &tmp, sizeof(tmp));
                else // Process order is odd.
                    write(pipe_fd_odd[1], &tmp, sizeof(tmp));
            }
            else{
                printf("%dth process Read all data\n", c_pid);
                int sig = -1;
                if(c_n == p_n - 1)
                    write(pipe_init[1], &sig, sizeof(sig));
                else if(c_n % 2 == 0) // Process order is even.
                    write(pipe_fd_even[1], &sig, sizeof(sig));
                else // Process order is odd.
                    write(pipe_fd_odd[1], &sig, sizeof(sig));
            }
            
            free(read_line);
            printf("exec\n");
        }
        else if(tmp == -1){ // Finishing job.
            if(c_n == p_n - 1)
                break;
            else{
                int sig = -1;
                if(c_n == p_n - 1)
                    write(pipe_init[1], &sig, sizeof(sig));
                else if(c_n % 2 == 0) // Process order is even.
                    write(pipe_fd_even[1], &sig, sizeof(sig));
                else // Process order is odd.
                    write(pipe_fd_odd[1], &sig, sizeof(sig));
                wait(NULL);
                break;
            }
        }
        else if (tmp == -2){ // Terminating.
            break;
        }
        else{
            // Waiting.
            
        }
    }

    return 0;
}