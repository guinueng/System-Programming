#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    unsigned char tmp[10];
    unsigned char *tmp_str;
    printf("%ld\n", sizeof(tmp));
    tmp_str = malloc(sizeof(tmp) + 1);
    for(size_t i = 0; i < sizeof(tmp) / sizeof(unsigned char); i++){
        *(tmp_str + i) = (unsigned char)(210+i);
    }
    char null_ = '\0';
    memcpy(tmp_str + strlen(tmp_str), &null_, 1); // Add null in the last part of string.
    printf("%u\n", tmp_str[2]);
    printf("%hhn\n",tmp_str);

    int num = 0;
    FILE *save = fopen("test.txt", "w");
    fwrite(tmp_str, 1, num, save);
    printf("%d\n", num);

    return 0;
}