#include <stdio.h> // Use printf.
#include <stdlib.h> // Use for realloc.
#include <string.h> // Use for strlen.
#include <math.h> // Use for pow.
#include "assignment1_1.h"

char* conv_bin_to_ascii_type(char* bin_line, char* return_line, size_t target_size){
    size_t line_len = strlen(bin_line);
    size_t bin_size = 8 * target_size;
    size_t tot_qty = line_len / bin_size;
    size_t start_pos = strlen(return_line);
    char* return_mem_add = realloc(return_line, (start_pos + (tot_qty * 2) + 1) ); // During realloc, mem add can change due to limited size of original mem location.
    if(return_mem_add == NULL)
        printf("Mem reallocation failed.\n");
    return_line = return_mem_add; // Change mem add into new location.
    
    char tmp[bin_size + 1];
    for(size_t trial = 1; trial <= tot_qty; trial++){
        start_pos = strlen(return_line);
        char result = 0;

        // Copying partial part of given bin_line into tmp string.
        for(size_t pos = 0; pos < bin_size; pos++){
            size_t margin = (line_len - (bin_size * trial) + pos);
            tmp[pos] = *(bin_line + margin);
        }
        tmp[bin_size] = '\0';

        for(int digit = bin_size - 1; digit >= 0; digit--)
            result += ((tmp[digit] - 48) * (int)pow(2,bin_size - digit - 1));

        memcpy(return_line + start_pos, &result, sizeof result);
        char blank = ' ';
        memcpy(return_line + strlen(return_line), &blank, 1);
    }
    char null_ = '\0';
    memcpy(return_line + strlen(return_line), &null_, 1); // Add null in the last part of string.

    return return_line; // Returns mem loc. Because when using realloc, mem add may change.
}

char* conv_bin_to_sign_char_type(char* bin_line, char* return_line, size_t target_size){
    printf("\nConv function\n");
    printf("Given string : %s\n", bin_line);
    size_t line_len = strlen(bin_line);
    size_t bin_size = 8 * target_size;
    size_t tot_qty = line_len / bin_size;
    size_t start_pos = strlen(return_line);
    printf("%ld %ld %ld\n", line_len, bin_size, tot_qty);
    printf("return line strlen : %ld\n\n", start_pos);
    unsigned char* return_mem_add = realloc(return_line, (start_pos + (tot_qty * 4) + 1) );
    printf("Realloc size : %ld\n", (start_pos + (tot_qty * 4) + 1) );
    if(return_mem_add == NULL)
        printf("Mem reallocation failed.\n");
    return_line = return_mem_add;
    
    unsigned char tmp[bin_size + 1];
    for(size_t trial = 1; trial <= tot_qty; trial++){
        start_pos = strlen(return_line);
        printf("Start pos : %ld\n", start_pos);
        printf("\n\n%ld th position\n", trial);
        //printf("bin size : %ld", bin_size);
        unsigned char result = 0;
        //printf("Result : %u\n", result);
        printf("Target pos : %ld\n", line_len - (bin_size * trial));

        // Copying partial part of given bin_line into tmp string.
        //printf("Copied binary : ");
        for(size_t pos = 0; pos < bin_size; pos++){
            size_t margin = (line_len - (bin_size * trial) + pos);
            //printf("Margin : %ld | target num : %c\n", margin, *(bin_line + margin));
            tmp[pos] = *(bin_line + margin);
            //printf("%d ", tmp[pos]);
        }
        //printf("\n");
        tmp[bin_size] = '\0';
        //strcpy(tmp, return_line + (line_len - (bin_size * trial) - 2));
    
        //printf("Copied binary line : %s | strlen : %ld\n", tmp, strlen(tmp));
        for(int digit = bin_size - 1; digit >= 0; digit--){
            //printf("%d th value : %d * %d = %d\n", digit, (tmp[digit] - 48), (int)pow(2,bin_size - digit), (int)(tmp[digit] - 48) * (int)pow(2,bin_size - digit - 1));
            result += ((tmp[digit] - 48) * (int)pow(2,bin_size - digit - 1));
        }
        char *conv_uchar_to_string;
        conv_uchar_to_string = malloc(4); // Must change value later.
        sprintf(conv_uchar_to_string, "%u", result);
        printf("Calc result : %u | sizeof : %ld\n", result, sizeof result);
        printf("Conv to string result : %s\n", conv_uchar_to_string);
        //printf("Before memcpy strlen : %ld\n", strlen(return_line));
        //memcpy(return_line + strlen(return_line), &result, sizeof result);
        /*
        if(trial == 1)
            strcpy(return_line, conv_uchar_to_string);
        else
            strcat(return_line, conv_uchar_to_string);*/
        memcpy(return_line + start_pos, conv_uchar_to_string, sizeof(conv_uchar_to_string));
        printf("Result line Before adding blank : %s| strlen : %ld\n", return_line, strlen(return_line));
        char blank[2] = {' ', '\0'};
        printf("blank : |%s|, sizeof blank : %ld\n", blank, strlen(blank));
        printf("strlen : %ld\n", strlen(return_line));
        //strcat(return_line, &blank);
        memcpy(return_line + strlen(return_line), &blank, 2);
        //strcat(return_line, &blank);
        printf("Result line : %s| strlen : %ld\n", return_line, strlen(return_line));
    }
    char null_ = '\0';
    memcpy(return_line + strlen(return_line), &null_, 1); // Add null in the last part of string.

    return return_line; // Returns mem loc. Because when using realloc, mem add may change.
}