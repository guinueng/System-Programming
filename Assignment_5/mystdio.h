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
    int wrbuffer_len;
} myFILE;


myFILE *myfopen(const char *pathname, const char *mode);
int myfclose(myFILE *stream);
int myfseek(myFILE *stream, int offset, int whence);
int myfread(void *ptr, int size, int nmemb, myFILE *stream);
int myfwrite(const void *ptr, int size, int nmemb, myFILE *stream);
int myfflush(myFILE *stream);
int myfputs(const char* str, myFILE* stream); // Modified due to modification based on assignment 5's new ppt.
char* myfgets(char* str, int num, myFILE* stream);


/* ************************
 *  Implement after here. *
 * ************************ */

/* fopen mode: "r", "r+", "w", "w+", "a", "a+" */
/* Read only = 0, Write only = 1, RW = 2 */
myFILE *myfopen(const char *pathname, const char *mode){
    myFILE* tmp = malloc(sizeof(myFILE));

    if(strlen(pathname) > 512 || strlen(pathname) < 0){ // pathname exceeds 512 bytes or lower than 0.
        write(1, "File Format Error\n", 18);
        free(tmp);
        return NULL;
    }

    // Need to implement file size check and dir check.
    struct stat buf;
    stat(pathname, &buf);
    if(S_ISDIR(buf.st_mode)){ // Check given filepath's file is folder or not.
        write(1, "File Format Error\n", 18);
        free(tmp);
        return NULL;
    }

    if(buf.st_size < 0 || buf.st_size > 2147483647){
        write(1, "File Format Error\n", 18);
        free(tmp);
        return NULL;
    }

    if(!strcmp(mode, "r")){
        if( access(pathname, F_OK) == -1 ){ // Check File Exist.
            free(tmp);
            return NULL;
        }
        if( access(pathname, R_OK) == -1 ){
            write(1, "File Format Error\n", 18);
            free(tmp);
            return NULL;
        }
        tmp -> fd = open(pathname, O_RDONLY);
        tmp -> mode_flag = 0;
        tmp -> offset = 0;
    }
    if(!strcmp(mode, "r+")){
        if( access(pathname, F_OK) == -1 ){
            free(tmp);
            return NULL;
        }
        if( access(pathname, R_OK) == -1  || access(pathname, W_OK) == -1){
            write(1, "File Format Error\n", 18);
            free(tmp);
            return NULL;
        }
        tmp -> fd = open(pathname, O_RDWR);
        tmp -> mode_flag = 2;
        tmp -> offset = 0;
        tmp -> wrbuffer[0] = '\0';
        tmp -> wrbuffer_len = 0;
    }
    if(!strcmp(mode, "w")){
        if( access(pathname, F_OK) != -1 && access(pathname, W_OK) == -1 ){
            write(1, "File Format Error\n", 18);
            free(tmp);
            return NULL;
        }
        tmp -> fd = open(pathname, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        tmp -> mode_flag = 1;
        tmp -> offset = 0;
        tmp -> wrbuffer[0] = '\0';
        tmp -> wrbuffer_len = 0;
    }
    if(!strcmp(mode, "w+")){
        if( access(pathname, F_OK) != -1 && (access(pathname, R_OK) == -1 || access(pathname, W_OK) == -1) ){
            write(1, "File Format Error\n", 18);
            free(tmp);
            return NULL;
        }
        tmp -> fd = open(pathname, O_RDWR | O_TRUNC | O_CREAT, 0644);
        tmp -> mode_flag = 2;
        tmp -> offset = 0;
        tmp -> wrbuffer[0] = '\0';
        tmp -> wrbuffer_len = 0;
    }
    if(!strcmp(mode, "a")){
        if( access(pathname, F_OK) != -1 && (access(pathname, W_OK) == -1) ){
            write(1, "File Format Error\n", 18);
            free(tmp);
            return NULL;
        }
        tmp -> fd = open(pathname, O_WRONLY | O_APPEND | O_CREAT, 0644);
        tmp -> mode_flag = 1;
        tmp -> offset = 0;
        tmp -> wrbuffer[0] = '\0';
        tmp -> wrbuffer_len = 0;
    }
    if(!strcmp(mode, "a+")){ // Can't understand exactly.
        if( access(pathname, F_OK) != -1 && access(pathname, R_OK) == -1 || access(pathname, W_OK) == -1 ){
            write(1, "File Format Error\n", 18);
            free(tmp);
            return NULL;
        }
        tmp -> fd = open(pathname, O_RDWR | O_TRUNC | O_CREAT, 0644);
        tmp -> mode_flag = 2;
        tmp -> offset = 0; // Need to fix value of end of file.
        tmp -> wrbuffer[0] = '\0';
        tmp -> wrbuffer_len = 0;
    }

    return tmp;
}

int myfclose(myFILE *stream){
    myfflush(stream);
    free(stream);
    return 0;
}

int myfseek(myFILE *stream, int offset, int whence){
    size_t result = lseek(stream -> fd, offset, whence); // If lseek success, returns positive values.
    if(result != -1) // When success.
        return 0;
    else // When fail.
        return -1;
}

int myfread(void *ptr, int size, int nmemb, myFILE *stream){
    if(stream -> mode_flag == 1){ // If does not have read permission.
        write(1, "Permission Denied\n", 19);
        return 0;
    }

    size_t result = read(stream -> fd, ptr, size * nmemb);

    if(result == size * nmemb){
        stream -> offset += result;
        return result;
    }
    else{
        stream -> offset += (result - 1); // read function returns value which contains '\0'. If nothing we get, it returns 1.
        return 0;
    }
}

int myfwrite(const void *ptr, int size, int nmemb, myFILE *stream){ // Need to add buffer.
    if(stream -> mode_flag == 0){ // If does not have write permission.
        write(1, "Permission Denied\n", 19);
        return 0;
    }

    const char* char_ptr = ptr;
    size_t tot_size = size * nmemb; // Tot qty of bytes to write.
    size_t buf_len = stream -> wrbuffer_len; // strlen of wrbuffer.
    size_t tot_trial = (tot_size + buf_len) / 1024; // How many trials need to store wrbuffer and flush to file.
    size_t left_len = (tot_size + buf_len) % 1024; // How many qty need to store on wrbuffer.
    size_t cur_loc = 0; // Given ptr's pos.
    size_t result = 0; // tot # of bytes transferred.
    
    if(tot_size >= 1024){ // First operation when str len >= 1024.
        for(size_t i = buf_len; i < 1024; i++)
            stream -> wrbuffer[i] = char_ptr[cur_loc++];
        result += write(stream -> fd, stream -> wrbuffer, 1024);
        stream -> wrbuffer_len = 0;
    }
    
    for(size_t i = 1; i < tot_trial; i++){ // Middle operation when strlen >= 2048.
        for(size_t j = 0; j < 1024; j++)
            stream -> wrbuffer[j] = char_ptr[cur_loc++];
        if(stream -> wrbuffer_len == 1024){
            result += write(stream -> fd, stream -> wrbuffer, 1024);
            stream -> wrbuffer_len = 0;    
        }
    }

    if(left_len != 0){ // Last operation when leftover strlen < 1024.
        for(size_t i = 0; i < left_len; i++)
            stream -> wrbuffer[stream -> wrbuffer_len++] = char_ptr[cur_loc++];
        stream -> wrbuffer_len = left_len;
    }

    if(result > 0 || stream -> wrbuffer_len > 0)
        return result;
    else
        return 0;
}

int myfflush(myFILE *stream){ // Let set file offset in the final part of file. Then write it. And return to original offset.
    if(stream -> mode_flag == 0){ // If it has read only permission.
        return 0; // Nothing to do. Read buffer is dismissed.(Based on piazza comments.)
    }
    if(stream -> wrbuffer_len == 0)
        return 0;
    else if( stream -> wrbuffer_len > 0 && write(stream -> fd, stream -> wrbuffer, stream -> wrbuffer_len) >= 0){
        stream -> wrbuffer_len = 0;
        return 0;
    }
    else
        return EOF;
}

int myfputs(const char* str, myFILE* stream){
    if(stream -> mode_flag == 0){ // If does not have write permission.
        write(1, "Permission Denied\n", 19);
        return 0;
    }
    
    size_t str_len = strlen(str);
    size_t wbuf_len = stream -> wrbuffer_len;
    size_t tot_trial = (str_len + wbuf_len) / 1024;
    size_t left_len = (str_len + wbuf_len) % 1024;
    size_t cur_loc = 0;
    size_t result = 0;

    if(tot_trial > 0){ // First operation when str len >= 1024.
        for(size_t i = wbuf_len; i < 1024; i++)
            stream -> wrbuffer[i] = str[cur_loc++];
        result += write(stream -> fd, stream -> wrbuffer, 1024);
        stream -> wrbuffer_len = 0;
    }
    
    for(size_t i = 1; i < tot_trial; i++){ // Middle operation when strlen >= 2048.
        for(size_t j = 0; j < 1024; j++)
            stream -> wrbuffer[j] = str[cur_loc++];
        if(stream -> wrbuffer_len == 1024){
            result += write(stream -> fd, stream -> wrbuffer, 1024);
            stream -> wrbuffer_len = 0;    
        }
    }

    if(left_len != 0){ // Last operation when leftover strlen < 1024.
        for(size_t i = 0; i < left_len; i++)
            stream -> wrbuffer[stream -> wrbuffer_len++] = str[cur_loc++];
    }

    if(result > 0)
        return 0;
    else
        return EOF;
}

char* myfgets(char *str, int num, myFILE* stream){
    if(stream -> mode_flag == 1){ // If does not have read permission.
        write(1, "Permission Denied\n", 19);
        return NULL;
    }
    char tmp;
    for(size_t i = 0; i < num - 1; i++){
        if(read(stream -> fd, &tmp, 1) != 0){
            *(str + i) = tmp;
            if(tmp == '\n'){
                *(str + i + 1) = '\0';
                return str;
            }
        }
        else{
            *(str + i) = '\0';
            return NULL;
        }
    }
}

#endif // mystdio.h included