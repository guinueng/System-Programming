#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* input_txt = fopen("input.txt", "r");
    FILE* output_txt = fopen("output_test.txt", "a");
    char *read_line, *tot_line, *result;

    if(input_txt == NULL)
        printf("input.txt does not opened normally.");
    else{
        size_t read_trials = 1;
        read_line = malloc(65);
        tot_line = malloc(65);
        while( (result = fgets(read_line, 65, input_txt)) != NULL){
            if(*read_line != '\n'){
                if(read_trials != 1){
                    realloc(tot_line, 65 * read_trials);
                }
                else{
                    tot_line = read_line;
                }
                printf("Read line : %s\nTot line : %s", read_line, tot_line);
            }
            else{
                fputs(tot_line, output_txt);
            }
        }
    }
    return 0;
}