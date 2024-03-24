#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment1_1.h"

int main(){
    FILE* input_txt = fopen("input.txt", "r");
    FILE* output_txt = fopen("output_test.txt", "a");
    char *read_line, *tot_line, *result, *reloc_mem_add;
    char *sign_char, *ascii, *un_char, *sign_int, *un_int, *sign_float, *sign_double; // We have to save the converted result.
    char *ascii_rst, *sign_char_rst; // We have to save final result.
    //unsigned char *sign_char;
    ascii_rst = malloc(14);
    memcpy(ascii_rst, "ASCII Codes: ", 13);
    sign_char_rst = malloc(14);
    memcpy(sign_char_rst, "Signed Char: ", 13);
    ascii = malloc(16);
    sign_char = malloc(16);
    
    //ascii = malloc(17);
    //fputs("ASCII Codes: ", output_txt);

    if(input_txt == NULL)
        printf("input.txt does not opened normally.");
    else{
        size_t trial = 1; // Should remove. Just for testing purpose.
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
                    //printf("Read_trials : %ld\n", read_trials);
                    reloc_mem_add = realloc(tot_line, (read_trials * 64) + 1);
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
                //printf("After strcpy : \nRead line : %s \n Tot line : %s\n", read_line, tot_line);
                read_trials++;
            }
            else{ // If the case that we picked on line is 'n', we can consider we approached in the final part of the line.
                // Then we have to consider data as little-endian.
                printf("%ld th Else\n", trial);
                printf("tot line : %s\n", tot_line);
                //size_t line_len = strlen(tot_line);
                // char *sign_char, *ascii, *un_char, *sign_int, *un_int, *sign_float, *sign_double;
                //reloc_mem_add = realloc(sign_char, (line_len / 4 / sizeof(signed char)));
                //printf("%ld", sizeof(sign_char));

                ascii = conv_bin_to_ascii_type(tot_line, ascii, sizeof(char));
                
                printf("Before signed Char : %s|strlen : %ld|size : %ld\n", sign_char, strlen(sign_char), sizeof(sign_char));
                sign_char = conv_bin_to_sign_char_type(tot_line, sign_char, sizeof(signed char));
                printf("After signed Char : %s\n", sign_char);

                /*
                int num;
                if( (num = fputs(ascii, output_txt)) != EOF){
                    printf("# of written char : %i\n", num);
                }
                else{
                    printf("Written Failed");
                }*/

                printf("sign char result : %s\n\n", sign_char);

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
            trial++; // RM when finish.
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

        ascii = conv_bin_to_ascii_type(tot_line, ascii, sizeof(char));
        reloc_mem_add = realloc(ascii_rst, strlen(ascii_rst) + strlen(ascii) + 1);
        if(reloc_mem_add == NULL)
            printf("Mem reallocation failed.\n");
        ascii_rst = reloc_mem_add;
        strcat(ascii_rst, ascii);
        strcat(ascii_rst, "\n");
        const char null_ = '\0';
        memcpy(ascii_rst + strlen(ascii_rst), &null_, 1); // Add null in the last part of string.
        fputs(ascii_rst, output_txt);
        printf("Finished ASCII part.");

        sign_char = conv_bin_to_sign_char_type(tot_line, sign_char, sizeof(signed char));
        reloc_mem_add = realloc(sign_char_rst, strlen(sign_char_rst) + strlen(sign_char) + 1);
        if(reloc_mem_add == NULL)
            printf("Mem reallocation failed.\n");
        sign_char_rst = reloc_mem_add;
        strcat(sign_char_rst, sign_char);
        strcat(sign_char_rst, "\n");
        memcpy(sign_char_rst + strlen(sign_char_rst), &null_, 1); // Add null in the last part of string.
        fputs(sign_char_rst, output_txt);
    }

    free(ascii); // Free mem space when we allocated above.
    free(ascii_rst);
    free(sign_char);
    free(sign_char_rst);
    return 0;
}