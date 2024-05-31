#include "mystdio.h"
int main() {
    myFILE *file = myfopen("test_read_write.txt", "w+");
    const char *text = "Sample text to write to file.";
    myfwrite(text, sizeof(char), strlen(text), file);
    myfseek(file, 0, SEEK_SET); // Go back to the start of the filechar buffer[BUFSIZE];
    char buffer[BUFSIZE];
    myfread(buffer, sizeof(char), strlen(text), file);
    //printf("Read from file: %s\n", buffer);
    write(1, "Read from file: ", 16);
    write(1, buffer, 1024);
    write(1, "\n", 1);
    myfclose(file);
    return 0;
}