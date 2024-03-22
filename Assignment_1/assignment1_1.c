#include <stdio.h> // Use printf.
#include <stdlib.h> // Use for realloc.
#include <string.h> // Use for strlen.
#include <math.h> // Use for pow.
#include "assignment1_1.h"

void conv_bin_to_sign_char_type(char* bin_line, char* return_line, size_t target_size){
    printf("Conv function\n");
    size_t line_len = strlen(bin_line);
    size_t bin_size = 8 * target_size;
    size_t tot_qty = line_len / bin_size;
    printf("%ld %ld %ld\n", line_len, bin_size, tot_qty);
    char* return_mem_add = realloc(return_line, tot_qty + 1);
    if(return_mem_add == NULL)
        printf("Mem reallocation failed.\n");
    
    for(size_t trial = 1; trial <= tot_qty; trial++){
        printf("%d th position\n", trial);
        char tmp[bin_size];
        unsigned char result = 0;
        printf("Target pos : %d\n", line_len - (bin_size * trial) - 1);
        printf("Target partial string : %s\n", return_line + (line_len - (bin_size * trial) - 1));
        strncpy(tmp, return_line + (line_len - (bin_size * trial) - 2), bin_size);
        printf("Copied binary line : %s | strlen : %d\n", tmp, strlen(tmp));
        for(size_t digit = bin_size; digit >= 1; digit--){
            printf("%ld th value : %d * %d = %d\n", digit, (int)tmp[digit], (int)pow(2,digit), (int)tmp[digit] * (int)pow(2, digit));
            result += (unsigned char)(tmp[digit] * (int)pow(2, digit));
        }
        printf("%c", result);
        strcat(return_line, &result);
    }
}