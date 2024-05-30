#ifndef MYSTDIO_H
#define MYSTDIO_H	1

#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE     1024    /* Default buffer size: 1024 bytes  */
#define EOF         -1      /* to indicate the end of the file. */

#define SEEK_SET    0       /* Seek from beginning of file.     */
#define SEEK_CUR    1       /* Seek from current position.      */
#define SEEK_END    2       /* Seek from end of file.           */

#define STDIN_FD    0
#define STDOUT_FD   1
#define STDERR_FD   2

typedef struct _myFILE{
	int fd;                 /* file descriptor of this file     */
    char rdbuffer[BUFSIZE]; /* read buffer of this file         */
    char wrbuffer[BUFSIZE]; /* write buffer of this file        */
    int mode_flag;          /* flag to describe opened mode     */
    int offset;             /* current position of a file (file position indicator) */
    int last_operation;     /* last operation for this file (read or write) */
} myFILE;


myFILE *myfopen(const char *pathname, const char *mode);
int myfclose(myFILE *stream);
int myfseek(myFILE *stream, int offset, int whence);
int myfread(void *ptr, int size, int nmemb, myFILE *stream);
int myfwrite(const void *ptr, int size, int nmemb, myFILE *stream);
int myfflush(myFILE *stream);
int myfputs(const char* str, int num, myFILE* stream);
char* myfgets(char* str, int num, myFILE* stream);


/* ************************
 *  Implement after here. *
 * ************************ */

/* fopen mode: "r", "r+", "w", "w+", "a", "a+" */
myFILE *myfopen(const char *pathname, const char *mode){
    myFILE* tmp = malloc(sizeof(myFILE));
    if( access(pathname, F_OK) == -1 ){
            write(1, "File does not exist.\n", 22);
            free(tmp);
            return NULL;
        }
    if(mode == "r"){
        if( access(pathname, R_OK) == -1 ){
            write(1, "Permission Denied.\n", 20);
            free(tmp);
            return NULL;
        }
        tmp->fd = open(pathname, O_RDONLY);
        tmp->mode_flag = 0;
        tmp->offset = 0;
    }
    return tmp;
}

int myfclose(myFILE *stream){
    if( write(stream -> fd, stream -> wrbuffer, 1024) == -1 ){ // make unwritten buffer to be written.
        write(1, "Write failed.\n", 15);
        return EOF;
    }
    free(stream);
    return 0;
}

int myfseek(myFILE *stream, int offset, int whence){
    // Implement write buffer flush here.
    size_t result = lseek(stream -> fd, offset, whence);
    if(result != -1)
        return 0;
    else
        return -1;

    /*size_t length;
    while(1){
        size_t result = read(stream -> fd, NULL, 1000);
        if(result != 0)
            length += result;
        else if(result == 0)
            break;
    }
    if(whence == SEEK_SET){
        stream -> offset = 0;
        if(0 + offset <= length){
            stream -> offset = offset;
            return 0;
        }
        else
            return -1;
    }
    else if(whence == SEEK_CUR){
        if(stream -> offset + offset <= length){
            stream -> offset = offset;
            return 0;
        }
        else
            return -1;
    }
    else if(whence == SEEK_END){
        if(length + offset <= length){
            stream -> offset = length + offset;
            return 0;
        }
        else
            return -1;
    }
    else
        return -1;*/
}

int myfread(void *ptr, int size, int nmemb, myFILE *stream){
    size_t result = read(stream -> fd, ptr, size * nmemb);
    if(result > 0){
        stream -> offset += result;
        return result;
    }
    else
        return 0;
    
    /*
    int r_qty = 0;
    if((stream -> offset % 1024) == 0)
        read(stream -> fd, stream -> rdbuffer, 1024);
    if( (stream -> offset % 1024) + size * nmemb < 1024 ){
        for(size_t i = 0; i < size * nmemb; i++)
            *(ptr + i) = stream -> rdbuffer[(stream -> offset % 1024) + i];
    }
    else{
        size_t readable_len = 1024 - (stream -> offset % 1024);
        for(size_t i = 0; i < readable_len; i++)
            ptr + i = stream -> rdbuffer[(stream -> offset % 1024) + size * i];
        stream -> offset += readable_len;
        size_t read_len = read(stream -> fd, stream -> rdbuffer, 1024);
        size_t must_read_len = size * nmemb - readable_len;
        if(must_read_len < read_len)
            for(size_t i = 0; i < must_read_len; i++)
                ptr + readable_len + i = stream -> rdbuffer[i];
        else
            for(size_t i = 0; i < read_len; i++)
                ptr + readable_len + i = stream -> rdbuffer[i];
    }*/
}

int myfwrite(const void *ptr, int size, int nmemb, myFILE *stream){
    size_t result = write(stream -> fd, ptr, size * nmemb);
    if(result > 0)
        return result;
    else
        return 0;
}

int myfflush(myFILE *stream){
    if(write(stream -> fd, stream -> wrbuffer, 1024) >= 0)
        return 0;
    else
        return EOF;
}

int myfputs(const char* str, int num, myFILE* stream){

}

char* myfgets(char *str, int num, myFILE* stream){

}

#endif // mystdio.h included