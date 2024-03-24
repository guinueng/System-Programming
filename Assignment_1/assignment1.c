#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment1_1.h"

int main(){
    FILE* input_txt = fopen("input.txt", "r");
    FILE* output_txt = fopen("output_test.txt", "a");
    char *read_line, *tot_line, *result, *reloc_mem_add;
    char *s_char, *ascii, *u_char, *s_int, *u_int, *sign_float, *sign_double; // We have to save the converted result.
    char *s_char_rst, *ascii_rst, *u_char_rst, *s_int_rst, *u_int_rst; // We have to save final result.

    s_char = malloc(16);
    ascii = malloc(16);
    u_char = malloc(16);
    s_int = malloc(4);
    u_int = malloc(4);

    s_char_rst = malloc(14);
    ascii_rst = malloc(14);
    u_char_rst = malloc(16);
    s_int_rst = malloc(13);
    u_int_rst = malloc(15);
    memcpy(s_char_rst, "Signed Char: ", 13);
    memcpy(ascii_rst, "ASCII Codes: ", 13);
    memcpy(u_char_rst, "Unsigned Char: ", 15);
    memcpy(s_int_rst, "Signed Int: ", 12);
    memcpy(u_int_rst, "Unsigned Int: ", 14);

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
                read_trials++;
            }
            else{ // If the case that we picked on line is 'n', we can consider we approached in the final part of the line.
                // Then we have to consider data as little-endian.
                printf("%ld th Else\n", trial);
                printf("tot line : %s\n", tot_line);

                s_char = bin_to_s_char(tot_line, s_char, sizeof(signed char));
                ascii = bin_to_ascii(tot_line, ascii, sizeof(char));
                u_char = bin_to_u_char(tot_line, u_char, sizeof(unsigned char));
                s_int = bin_to_s_int(tot_line, s_int, sizeof(signed int));
                u_int = bin_to_s_int(tot_line, u_int, sizeof(unsigned int));

                printf("unsigned int result : %s\n\n", u_int);

                read_trials = 1;
            }
            trial++; // RM when finish.
        }

        const char null_ = '\0';
        s_char = bin_to_u_char(tot_line, s_char, sizeof(signed char));
        reloc_mem_add = realloc(s_char_rst, strlen(s_char_rst) + strlen(s_char) + 1);
        if(reloc_mem_add == NULL)
            printf("Mem reallocation failed.\n");
        s_char_rst = reloc_mem_add;
        strcat(s_char_rst, s_char);
        strcat(s_char_rst, "\n");
        memcpy(s_char_rst + strlen(s_char_rst), &null_, 1); // Add null in the last part of string.
        fputs(s_char_rst, output_txt);

        ascii = bin_to_ascii(tot_line, ascii, sizeof(char));
        reloc_mem_add = realloc(ascii_rst, strlen(ascii_rst) + strlen(ascii) + 1);
        if(reloc_mem_add == NULL)
            printf("Mem reallocation failed.\n");
        ascii_rst = reloc_mem_add;
        strcat(ascii_rst, ascii);
        strcat(ascii_rst, "\n");
        memcpy(ascii_rst + strlen(ascii_rst), &null_, 1); // Add null in the last part of string.
        fputs(ascii_rst, output_txt);

        u_char = bin_to_u_char(tot_line, u_char, sizeof(unsigned char)); // Putting Unsigned char into output file.
        reloc_mem_add = realloc(u_char_rst, strlen(u_char_rst) + strlen(u_char) + 1);
        if(reloc_mem_add == NULL)
            printf("Mem reallocation failed.\n");
        u_char_rst = reloc_mem_add;
        strcat(u_char_rst, s_char);
        strcat(u_char_rst, "\n");
        memcpy(u_char_rst + strlen(u_char_rst), &null_, 1); // Add null in the last part of string.
        fputs(u_char_rst, output_txt);
        printf("Finished uchar part.");

        s_int = bin_to_s_int(tot_line, s_int, sizeof(signed int));
        reloc_mem_add = realloc(s_int_rst, strlen(s_int_rst) + strlen(s_int) + 1);
        if(reloc_mem_add == NULL)
            printf("Mem reallocation failed.\n");
        s_int_rst = reloc_mem_add;
        strcat(s_int_rst, s_int);
        strcat(s_int_rst, "\n");
        memcpy(s_int_rst + strlen(s_int_rst), &null_, 1); // Add null in the last part of string.
        fputs(s_int_rst, output_txt);

        u_int = bin_to_u_int(tot_line, u_int, sizeof(unsigned int));
        reloc_mem_add = realloc(u_int_rst, strlen(u_int_rst) + strlen(u_int) + 1);
        if(reloc_mem_add == NULL)
            printf("Mem reallocation failed.\n");
        u_int_rst = reloc_mem_add;
        strcat(u_int_rst, u_int);
        strcat(u_int_rst, "\n");
        memcpy(u_int_rst + strlen(u_int_rst), &null_, 1); // Add null in the last part of string.
        fputs(u_int_rst, output_txt);
    }

    free(s_char); // Free mem space when we allocated above.
    free(s_char_rst);
    free(ascii);
    free(ascii_rst);
    free(u_char);
    free(u_char_rst);
    free(s_int);
    free(s_int_rst);
    free(u_int);
    free(u_int_rst);
    return 0;
}