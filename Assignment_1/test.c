#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    unsigned char tmp = (unsigned char)48;
    unsigned char *tmp_str;
    printf("%d\n", sizeof tmp);
    tmp_str = malloc(sizeof tmp + 1);
    memcpy(tmp_str, &tmp, sizeof tmp);
    tmp_str[sizeof tmp + 1] = '\0';
    printf("%u\n", tmp);
    printf("%s\n",tmp_str);

    FILE *save = fopen("test.txt", "w");
    fputs(tmp_str, save);

    return 0;
}