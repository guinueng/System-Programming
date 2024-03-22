#include <stdio.h> // Use printf.
#include <stdlib.h> // Use for realloc.
#include <string.h> // Use for strlen.
#include <math.h> // Use for pow.
#include "assignment1_1.h"

void conv_bin_to_sign_char_type(char* bin_line, unsigned char* return_line, size_t target_size){
    printf("Conv function\n");
    printf("Given string : %s\n", bin_line);
    size_t line_len = strlen(bin_line);
    size_t bin_size = 8 * target_size;
    size_t tot_qty = line_len / bin_size;
    printf("%ld %ld %ld\n", line_len, bin_size, tot_qty);
    printf("strlen : %ld\n", strlen(return_line));
    char* return_mem_add = realloc(return_line, strlen(return_line) + tot_qty + 1);
    if(return_mem_add == NULL)
        printf("Mem reallocation failed.\n");
    
    for(size_t trial = 1; trial <= tot_qty; trial++){
        printf("%ld th position\n", trial);
        printf("bin size : %ld", bin_size);
        char tmp[bin_size + 1];
        unsigned char result = 0;
        printf("Result : %u\n", result);
        printf("Target pos : %ld\n", line_len - (bin_size * trial) - 1);

        // Copying partial part of given bin_line into tmp string.
        for(size_t pos = 0; pos < bin_size; pos++){
            size_t margin = (line_len - (bin_size * trial) + pos);
            printf("Margin : %ld | target num : %c\n", margin, *(bin_line + margin));
            tmp[pos] = *(bin_line + margin);
        }
        tmp[bin_size] = '\0';
        //strcpy(tmp, return_line + (line_len - (bin_size * trial) - 2));
    
        printf("Copied binary line : %s | strlen : %ld\n", tmp, strlen(tmp));
        for(int digit = bin_size - 1; digit >= 0; digit--){
            printf("%d th value : %d * %d = %d\n", digit, (tmp[digit] - 48), (int)pow(2,bin_size - digit), (int)(tmp[digit] - 48) * (int)pow(2,bin_size - digit - 1));
            result += (unsigned char)((tmp[digit] - 48) * (int)pow(2,bin_size - digit - 1));
        }
        printf("Calc result : %u | strlen : %ld\n", result, strlen(&result));
        
        strcat(return_line, &result);
            //memcpy(return_line + ((trial - 1) * bin_size), &result, bin_size);
        printf("Result line : %s| strlen : %ld\n", return_line, strlen(return_line));
    }   
}