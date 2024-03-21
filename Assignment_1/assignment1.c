#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* input_txt = fopen("input.txt", "r");
    FILE* output_txt = fopen("output_test.txt", "a");
    char *read_line, *tot_line, *result;

    if(input_txt == NULL)
        printf("input.txt does not opened normally.");
    else{
        size_t read_trials = 0;
        while( (result = fgets(*read_line, 64, input_txt)) != NULL){
            printf("Read line : %s", read_line);
            fputs(read_line, output_txt);
        }
    }
    return 0;
}