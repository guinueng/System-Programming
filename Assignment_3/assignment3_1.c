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

    int c_n = 0, pos = 1;
    printf("p_n : %d\n", p_n);

    pid_t c_pid, pid;
    printf("original PID : %d\n", getpid());

    int pipe_init[2]; // Pipe connection for the first and last process.
    pipe(pipe_init);
    write(pipe_init[1], "1", sizeof("1"));

    int pipe_fd[2];

    for(size_t i = 0; i < p_n - 1; i++){
        pipe(pipe_fd);
        write(pipe_fd[1], &pos, sizeof(pos));
        pid = fork();

        if(pid == 0 && i == p_n - 2){
            // Case for the last one. Does not need to make other child process. Thus finish exec.
            //close(pipe_fd[1]);
            //close(pipe_init[0]);
            c_pid = getpid();
            c_n = i + 1;
            printf("%dth pid : %d\n", c_n, c_pid);
        }
        else if(pid != 0){
            // Parent case. Get pid number and current executed trial number and store it. Then wait until all child process is made.
            //close(pipe_init[1]);
            //if(i != 0)
                //close(pipe_init[0]);
            //close(pipe_fd[0]);
            c_pid = getpid();
            c_n = i;
            printf("%dth pid : %d\n", c_n, c_pid);
            int tmp = 0;
            write(pipe_fd[1], &tmp, sizeof(c_n));
            pid_t a = wait('\0');
            break;
        }
        else{
            //close(pipe_fd[1]);
            //close(pipe_init[0]);
            //close(pipe_init[1]);
        }
        // The other case is child case. So we do not need to consider cause it locates inside of for loop.
    }

    printf("\n");
    printf("%dth program has PID : %d\n", c_n, c_pid);

    while(1){
        int n;
        read(pipe_fd[0], &n, sizeof(n));
        printf("pipe pos : %d\n", pos);
        if( n % p_n == c_n ){
            printf("%d program printed %dth line.\n", c_n, pos);
            char read_line[65];
            char* result = fgets(read_line, 65, file);
            if( result != NULL ){
                printf("%d %d %s | %dth line\n", c_pid, c_n, read_line, n);
                n++;
                write(pipe_fd[0], &n, sizeof(n));
                printf("Read one line.\n");
            }
            else{
                printf("%d %d Read all data\n", c_pid, c_n);
            }
        }
        else{
            printf("Wait\n");
            sleep(1);
        }
        printf("I don't know.\n");
    }


    return 0;
}