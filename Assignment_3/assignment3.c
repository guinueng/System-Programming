#include <stdio.h> // To use printf and other function.
#include <assert.h> // To use assert function.
#include <unistd.h> // To use pid.
#include <stdlib.h> // To use malloc, atoi function to change char* to int.
#include <sys/wait.h> // To use wait function.
#include <string.h>
#include <fcntl.h> // To use open func.

int main(int argc, char* argv[]){
    assert( argc == 3 ); // Exec only input val on cmd is 3.
    int fd = open(argv[1], O_RDONLY|O_SYNC);
    size_t p_n = atoi(argv[2]);

    assert( p_n < 17 || p_n > 3 );
    int c_n = 0, pos = 1;

    pid_t c_pid, pid;

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
                //close(pipe_fd_even[1]);
            }
            else{
                //close(pipe_fd_odd[1]);
            }
            //close(pipe_init[0]);
            c_pid = getpid();
            c_n = i + 1;
            tmp = 1;
            write(pipe_init[1], &tmp, sizeof(tmp)); // Write signal.
            write(pipe_init[1], &tmp, sizeof(tmp)); // Write line.
        }
        else if(pid != 0){
            // Parent case. Get pid number and current executed trial number and store it. Then wait until all child process is made.
            if(i % 2 == 0){
                //close(pipe_fd_even[0]);
                write(pipe_fd_even[1], &tmp, sizeof(tmp));
            }
            else{
                //close(pipe_fd_odd[0]);
                write(pipe_fd_odd[1], &tmp, sizeof(tmp));
            }
            c_pid = getpid();
            c_n = i;
            break;
        }
        else{ // Child case;
            if(i % 2 == 0){
                //close(pipe_fd_odd[1]);
                //write(pipe_fd_even[1], &tmp, sizeof(tmp));
            }
            else{
                //close(pipe_fd_even[1]);
                //write(pipe_fd_odd[1], &tmp, sizeof(tmp));
            }
        }
        // The other case is child case. So we do not need to consider cause it locates inside of for loop.
    }

    int tmp = 0, cnt = 0, detect = 0;
    int n_t;
    if(c_n != p_n - 1)
        n_t = c_n + 1;
    else
        n_t = 0;

    while(1){
        int last = 0;
        if(c_n != 0){
            if(c_n % 2 == 0) // Process order is even.
                read(pipe_fd_odd[0], &tmp, sizeof(tmp));
            else // Process order is odd.
                read(pipe_fd_even[0], &tmp, sizeof(tmp));
        }
        else
            read(pipe_init[0], &tmp, sizeof(tmp));

        if(tmp == 1){
            char* result;
            char* read_line;
            read_line = malloc(65);
            size_t indicator = 0;
            for(size_t i = 0; i < 65; i++){
                indicator = read(fd, &read_line[i], 1);
                if(indicator == -1)
                    break;
                if(read_line[i] == '\n'){
                    indicator = 1;
                    break;
                }
            }

            if( indicator == 1 ){
                int line = 0;
                if(c_n != 0){
                    if(c_n % 2 == 0) // Process order is even.
                        read(pipe_fd_odd[0], &line, sizeof(line));
                    else // Process order is odd.
                        read(pipe_fd_even[0], &line, sizeof(line));
                }
                else
                    read(pipe_init[0], &line, sizeof(line));

                printf("%d %d %s", c_pid, line, read_line);
                line++;
                if(c_n == p_n - 1){
                    write(pipe_init[1], &tmp, sizeof(tmp));
                    write(pipe_init[1], &line, sizeof(line));
                }
                else if(c_n % 2 == 0){ // Process order is even.
                    write(pipe_fd_even[1], &tmp, sizeof(tmp));
                    write(pipe_fd_even[1], &line, sizeof(line));
                }
                else{ // Process order is odd.
                    write(pipe_fd_odd[1], &tmp, sizeof(tmp));
                    write(pipe_fd_odd[1], &line, sizeof(line));
                }
            }
            else{
                printf("%d Read all data\n", c_pid);
                int sig = -1;
                if(c_n == p_n - 1)
                    write(pipe_init[1], &sig, sizeof(sig));
                else if(c_n % 2 == 0) // Process order is even.
                    write(pipe_fd_even[1], &sig, sizeof(sig));
                else // Process order is odd.
                    write(pipe_fd_odd[1], &sig, sizeof(sig));
            }

            free(read_line);
        }
        else if(tmp == -1){ // Finishing job.
            int sig = -1;
            if(c_n == p_n - 1)
                write(pipe_init[1], &sig, sizeof(sig));
            else if(c_n % 2 == 0) // Process order is even.
                write(pipe_fd_even[1], &sig, sizeof(sig));
            else // Process order is odd.
                write(pipe_fd_odd[1], &sig, sizeof(sig));
            if(detect != 0){
                wait(NULL);
                break;
            }
            detect++;
        }
        else{
            // Waiting.
        }
    }

    /*while(1){
        // Looping to terminate from last process.
        int sig = 1;
        if(c_n == p_n - 1){
            if(c_n % 2 == 0)
                write(pipe_fd_odd[1], &sig, sizeof(sig));
            else
                write(pipe_fd_even[1], &sig, sizeof(sig));
            break;
        }
        else{
            int rx = 0;
            if(c_n % 2 == 0)
                read(pipe_fd_even[0], &rx, sizeof(rx));
            else
                read(pipe_fd_odd[0], &rx, sizeof(rx));
            if(rx == 1){
                int sig = 1;
                if(c_n % 2 == 0)
                    write(pipe_fd_odd[1], &sig, sizeof(sig));
                else
                    write(pipe_fd_even[1], &sig, sizeof(sig));
                break;
            }
        }
    }*/

    printf("%d I'm exiting\n", c_pid);
    return 0;
}