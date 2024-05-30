#include "mystdio.h"
int main() {
    myFILE *file = myfopen("test_flush.txt", "w");
    myfputs("This is a test.", 15, file);
    myfflush(file);
    myfclose(file);
    return 0;
}