#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE* input_txt = fopen("input.txt", "r");
    FILE* output_txt = fopen("output_test.txt", "a");
    char *read_line, *tot_line, *result, *reloc_mem_add;

    if(input_txt == NULL)
        printf("input.txt does not opened normally.");
    else{
        size_t read_trials = 1;
        read_line = malloc(65);
        tot_line = malloc(65);
        while( (result = fgets(read_line, 65, input_txt)) != NULL){
            if(*read_line != '\n'){
                if(read_trials != 1){
                    printf("Read_trials : %ld\n", read_trials);
                    reloc_mem_add = realloc(tot_line, (read_trials * 65));
                    printf("%ld reallocated\n", (read_trials * 65));
                    if(reloc_mem_add == NULL)
                        printf("Mem reallocation failed.\n");
                    else{
                        tot_line = reloc_mem_add;
                        tot_line = strcat(tot_line, read_line);
                    }
                }
                else{
                    tot_line = strcpy(tot_line, read_line);
                }
                printf("After strcpy : \nRead line : %s \n Tot line : %s\n", read_line, tot_line);
                read_trials++;
            }
            else{
                printf("Else case \\n Appeared!%s",read_line);
                printf("Tot line which appended : %s\n", tot_line);
                fputs(tot_line, output_txt);
                fputs("|",output_txt);
                free(read_line);
                free(tot_line);
                read_line = malloc(65);
                tot_line = malloc(65);
                read_trials = 1;
                printf("Reset\n\n");
            }
        }
        printf("Else case \\n Appeared!%s",read_line);
        printf("Tot line which appended : %s\n", tot_line);
        fputs(tot_line, output_txt);
        fputs("|",output_txt);
        free(read_line);
        free(tot_line);
        read_line = malloc(65);
        tot_line = malloc(65);
        read_trials = 1;
        printf("Reset\n\n");
    }
    return 0;
}