#include "mystdio.h"
int main() {
    myFILE *file = myfopen("test", "w");
    myfputs("This is a test.", file);
    myfflush(file);
    myfclose(file);
    return 0;
}