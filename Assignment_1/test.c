#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    unsigned char tmp[10];
    unsigned char *tmp_str;
    printf("%ld\n", sizeof(tmp));
    tmp_str = malloc(1);
    for(size_t i = 0; i < sizeof(tmp) / sizeof(unsigned char); i++){
        char *buf, *reloc_mem_add;
        unsigned char tmp_char = 212 + i;
        buf = malloc(100);
        sprintf(buf, "%u", tmp_char);
        printf("conv : %s\n", buf);
        reloc_mem_add = realloc(tmp_str, strlen(tmp_str) + strlen(buf) + 1);
        tmp_str = reloc_mem_add;
        if(i == 0)
            strcpy(tmp_str, buf);
        else
            strcat(tmp_str, buf);
        //*(tmp_str + i) = (unsigned char)(210+i);
        free(buf);
    }
    char null_ = '\0';
    memcpy(tmp_str + strlen(tmp_str), &null_, 1); // Add null in the last part of string.
    printf("%s\n", tmp_str);
    //printf("%hhn\n",tmp_str);

    int num = 0;
    FILE *save = fopen("test.txt", "w");
    //printf(save, "%d", tmp_str);
    
    fputs(tmp_str, save);
    //printf("%d\n", num);

    return 0;
}