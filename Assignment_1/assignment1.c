#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment1_1.h"

int main(){
    FILE* input_txt = fopen("input.txt", "r");
    FILE* output_txt = fopen("output_test.txt", "a");
    char *read_line, *tot_line, *result, *reloc_mem_add;
    char *sign_char, *ascii, *un_char, *sign_int, *un_int, *sign_float, *sign_double; // We have to save the result.
    char *ascii_rst;
    ascii_rst = malloc(14);
    memcpy(ascii_rst, &"ASCII Codes: ", 13);
    //sign_char = malloc(sizeof(char) * 14);
    //strcpy(sign_char, "Signed Char: ");
    //unsigned char *sign_char;
    ascii = malloc(16);
    if(input_txt == NULL)
        printf("input.txt does not opened normally.");
    else{
        fputs("ASCII Codes: ", output_txt);
        size_t read_trials = 1;
        size_t line = 1; // We have to consider which line we get the binaries and how many binaries in that line.
        read_line = malloc(65);
        tot_line = malloc(65);
        // Then locate memory to get read 64 binary value in files at target line,
        // and locate memory which have to store whole line's input.
        while( (result = fgets(read_line, 65, input_txt)) != NULL){
            // Repeat when we approach end of file.
            if(*read_line != '\n'){ // If the case that we picked on line is not 'n'
                if(read_trials != 1){
                    printf("Read_trials : %ld\n", read_trials);
                    reloc_mem_add = realloc(tot_line, (read_trials * 65));
                    if(reloc_mem_add == NULL)
                        printf("Mem reallocation failed.\n");
                    else{
                        tot_line = reloc_mem_add;
                        tot_line = strcat(tot_line, read_line); // Adding two string into tot_line string.
                    }
                }
                else{
                    tot_line = strcpy(tot_line, read_line); // Copying read_line string into tot_line.
                }
                printf("After strcpy : \nRead line : %s \n Tot line : %s\n", read_line, tot_line);
                read_trials++;
            }
            else{ // If the case that we picked on line is 'n', we can consider we approached in the final part of the line.
                // Then we have to consider data as little-endian.
                printf("Else\n");
                //size_t line_len = strlen(tot_line);
                // char *sign_char, *ascii, *un_char, *sign_int, *un_int, *sign_float, *sign_double;
                //reloc_mem_add = realloc(sign_char, (line_len / 4 / sizeof(signed char)));
                //printf("%ld", sizeof(sign_char));
                printf("Before ascii Char : %s|strlen : %ld|size : %ld\n", ascii, strlen(ascii), sizeof(ascii));
                conv_bin_to_sign_ascii_type(tot_line, ascii, sizeof(char));
                fputs(ascii, output_txt);
                /*printf("Tot line which appended : %s\n", tot_line);
                fputs(tot_line, output_txt);
                free(read_line);
                free(tot_line);
                read_line = malloc(65);
                tot_line = malloc(65);
                read_trials = 1;
                printf("Reset\n\n");*/
                read_trials = 1;
            }
        }
        /*printf("Else case\n");
        printf("Tot line which appended : %s\n", tot_line);
        fputs(tot_line, output_txt);
        free(read_line);
        free(tot_line);
        read_line = malloc(65);
        tot_line = malloc(65);
        read_trials = 1;
        printf("Reset\n\n");*/
    }

    free(ascii);
    return 0;
}