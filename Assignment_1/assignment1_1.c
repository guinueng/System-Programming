#include <stdio.h> // Use printf.
#include <stdlib.h> // Use for realloc.
#include <string.h> // Use for strlen.
#include <math.h> // Use for pow.
#include "assignment1_1.h"

void conv_bin_to_sign_char_type(char* bin_line, char* return_line, size_t target_size){
    size_t line_len = strlen(bin_line);
    size_t bin_size = 8 * target_size;
    size_t tot_qty = line_len / bin_size;
    char* return_mem_add = realloc(return_line, tot_qty);
    if(return_mem_add == NULL)
        printf("Mem reallocation failed.\n");
    
    for(size_t trial = 1; trial <= tot_qty; trial--){
        char tmp[bin_size];
        int result = 0;
        strncpy(tmp, &return_line[line_len - (bin_size * trial)], bin_size);
        for(size_t digit = bin_size; digit >= 0; digit--){
            result += (tmp[digit] * pow(2, digit));
        }
        
        strcat(return_line, (char)result);
    }
}