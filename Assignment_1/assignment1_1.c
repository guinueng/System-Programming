#include <stdio.h> // Use sprintf function for type converting.
#include <stdlib.h> // Use for malloc / calloc / realloc function.
#include <string.h> // Use for strlen function.
#include <math.h> // Use for pow function.
#include "assignment1_1.h"

char* bin_to_s_char(char* bin_line, char* return_line, size_t target_size){ // Need to mod s_char and u_char.
    size_t line_len = strlen(bin_line);
    size_t bin_size = 8 * target_size;
    size_t tot_qty = line_len / bin_size;
    size_t start_pos = strlen(return_line);

    char* return_mem_add = realloc(return_line, (start_pos + (tot_qty * 5) + 1) ); // During realloc, mem add can change due to limited size of original mem location.
    if(return_mem_add == NULL)
        printf("Mem reallocation failed.\n");
    return_line = return_mem_add; // Updating mem add because it can vary during realloc.
    
    char tmp[bin_size + 1]; // Make temporary binary store array.
    for(size_t trial = 1; trial <= tot_qty; trial++){
        char result = 0; // Make this to store calculated value.

        for(size_t pos = 0; pos < bin_size; pos++){ // Putting partial part of binary array into temporary which we want to calculate.
            size_t margin = (line_len - (bin_size * trial) + pos);
            tmp[pos] = *(bin_line + margin);
        }
        tmp[bin_size] = '\0'; // The last part of array should be NULL.

        printf("read line : %s\n", tmp);
        for(int digit = bin_size - 1; digit >= 0; digit--){ // Converting binary into decimal #. Need to fix it to apply negative value calculation.
            printf("calculating result : %d += ", result);
            if(digit != 0)
                result += ((tmp[digit] - 48) * (int)pow(2,bin_size - digit - 1));
            else
                result -= ((tmp[digit] - 48) * (int)pow(2,bin_size - digit - 1));
            printf("%d * %d = %d\n", (tmp[digit] - 48), (int)pow(2,bin_size - digit - 1), result);
        }
        printf("\n");
        char *s_char_to_str;
        s_char_to_str = malloc(5); // Char range : -128 ~ 127. Thus, maximum 5 location is needed.
        sprintf(s_char_to_str, "%d", result); // Converting char's integer value into string.

        memcpy(return_line + strlen(return_line), s_char_to_str, sizeof(s_char_to_str)); // Copying converted string into return_line string.
        char blank[2] = {' ', '\0'}; // Making array of blank space and null to input on last part of string.
        memcpy(return_line + strlen(return_line), &blank, 2); // Copying blank and null into last part of string.
        free(s_char_to_str);
    }
    char null_ = '\0';
    memcpy(return_line + strlen(return_line), &null_, 1); // Add null in the last part of string.

    return return_line; // Returns mem loc. Because when using realloc, mem add may change.
}

char* bin_to_ascii(char* bin_line, char* return_line, size_t target_size){
    size_t line_len = strlen(bin_line);
    size_t bin_size = 8 * target_size;
    size_t tot_qty = line_len / bin_size;
    size_t start_pos = strlen(return_line);
    char* return_mem_add = realloc(return_line, (start_pos + (tot_qty * 2) + 1) ); // During realloc, mem add can change due to limited size of original mem location.
    if(return_mem_add == NULL)
        printf("Mem reallocation failed.\n");
    return_line = return_mem_add; // Updating mem add because it can vary during realloc.
    
    char tmp[bin_size + 1];
    for(size_t trial = 1; trial <= tot_qty; trial++){
        start_pos = strlen(return_line);
        char result = 0;

        // Copying partial part of given bin_line into tmp string.
        for(size_t pos = 0; pos < bin_size; pos++){ // Putting partial part of binary array into temporary which we want to calculate.
            size_t margin = (line_len - (bin_size * trial) + pos);
            tmp[pos] = *(bin_line + margin);
        }
        tmp[bin_size] = '\0'; // The last part of array should be NULL.

        for(int digit = bin_size - 1; digit >= 0; digit--) // Converting binary into decimal #.
            result += ((tmp[digit] - 48) * (int)pow(2,bin_size - digit - 1));

        memcpy(return_line + start_pos, &result, sizeof result); // Copying converted string into return_line string.
        char blank[2] = {' ', '\0'}; // Making array of blank space and null to input on last part of string.
        memcpy(return_line + strlen(return_line), &blank, 2); // Copying blank and null into last part of string.
    }
    char null_ = '\0';
    memcpy(return_line + strlen(return_line), &null_, 1); // Add null in the last part of string.

    return return_line; // Returns mem loc. Because when using realloc, mem add may change.
}

char* bin_to_u_char(char* bin_line, char* return_line, size_t target_size){
    size_t line_len = strlen(bin_line);
    size_t bin_size = 8 * target_size;
    size_t tot_qty = line_len / bin_size;
    size_t start_pos = strlen(return_line);

    char* return_mem_add = realloc(return_line, (start_pos + (tot_qty * 4) + 1) ); // During realloc, mem add can change due to limited size of original mem location.
    if(return_mem_add == NULL)
        printf("Mem reallocation failed.\n");
    return_line = return_mem_add; // Updating mem add because it can vary during realloc.
    
    unsigned char tmp[bin_size + 1]; // Make temporary binary store array.
    for(size_t trial = 1; trial <= tot_qty; trial++){
        unsigned char result = 0; // Make this to store calculated value.

        for(size_t pos = 0; pos < bin_size; pos++){ // Putting partial part of binary array into temporary which we want to calculate.
            size_t margin = (line_len - (bin_size * trial) + pos);
            tmp[pos] = *(bin_line + margin);
        }
        tmp[bin_size] = '\0'; // The last part of array should be NULL.

        for(int digit = bin_size - 1; digit >= 0; digit--) // Converting binary into decimal #.
            result += ((tmp[digit] - 48) * (int)pow(2,bin_size - digit - 1));

        char *u_char_to_str;
        u_char_to_str = malloc(4); // Unsigned char's max value = 255. Thus, maximum 4 location is needed.
        sprintf(u_char_to_str, "%u", result); // Converting unsigned char's integer value into string.

        memcpy(return_line + strlen(return_line), u_char_to_str, sizeof(u_char_to_str)); // Copying converted string into return_line string.
        char blank[2] = {' ', '\0'}; // Making array of blank space and null to input on last part of string.
        memcpy(return_line + strlen(return_line), &blank, 2); // Copying blank and null into last part of string.
        free(u_char_to_str);
    }

    return return_line; // Returns mem loc. Because when using realloc, mem add may change.
}

char* bin_to_s_int(char* bin_line, char* return_line, size_t target_size){
    size_t line_len = strlen(bin_line);
    size_t bin_size = 8 * target_size;
    size_t tot_qty = line_len / bin_size;
    size_t start_pos = strlen(return_line);
    
    int tmp[bin_size + 1]; // Make temporary binary store array.
    for(size_t trial = 1; trial <= tot_qty; trial++){
        int result = 0; // Make this to store calculated value.

        for(size_t pos = 0; pos < bin_size; pos++){ // Putting partial part of binary array into temporary which we want to calculate.
            size_t margin = (line_len - (bin_size * trial) + pos);
            tmp[pos] = *(bin_line + margin) - 48;
        }
        tmp[bin_size] = '\0'; // The last part of array should be NULL.

        for(int digit = bin_size - 1; digit >= 0; digit--){ // Converting binary into decimal #. By little endian and two's complement, last part of binary array would be determinant of negative.
            if(digit != 0)
                result += ((tmp[digit]) * (int)pow(2,bin_size - digit - 1));
            else
                result -= ((tmp[digit]) * (int)pow(2,bin_size - digit - 1));
        }
        char *s_int_to_str;
        s_int_to_str = malloc(12); // int range : -2,147,483,648 ~ 2,147,483,647. Thus, maximum 5 location is needed.
        sprintf(s_int_to_str, "%d", result); // Converting integer value into string.

        int reloc_size = (strlen(return_line) + strlen(s_int_to_str) + 2);
        char* return_mem_add = realloc(return_line, reloc_size); // During realloc, mem add can change due to limited size of original mem location.
        if(return_mem_add == NULL)
            printf("Mem reallocation failed.\n");
        return_line = return_mem_add; // Updating mem add because it can vary during realloc.

        memcpy(return_line + strlen(return_line), s_int_to_str, strlen(s_int_to_str)); // Copying converted string into return_line string.
        char blank[2] = {' ', '\0'}; // Making array of blank space and null to input on last part of string.
        memcpy(return_line + reloc_size - 2, &blank, 2); // Copying blank and null into last part of string.
        free(s_int_to_str);
    }

    return return_line; // Returns mem loc. Because when using realloc, mem add may change.
}

char* bin_to_u_int(char* bin_line, char* return_line, size_t target_size){
    size_t line_len = strlen(bin_line);
    size_t bin_size = 8 * target_size;
    size_t tot_qty = line_len / bin_size;
    size_t start_pos = strlen(return_line);
    
    int tmp[bin_size + 1]; // Make temporary binary store array.
    for(size_t trial = 1; trial <= tot_qty; trial++){
        unsigned int result = 0; // Make this to store calculated value.

        for(size_t pos = 0; pos < bin_size; pos++){ // Putting partial part of binary array into temporary which we want to calculate.
            size_t margin = (line_len - (bin_size * trial) + pos);
            tmp[pos] = *(bin_line + margin) - 48;
        }
        tmp[bin_size] = '\0'; // The last part of array should be NULL.

        for(int digit = bin_size - 1; digit >= 0; digit--){ // Converting binary into decimal #. No negative integer will outcome.
            result += ((tmp[digit]) * (int)pow(2,bin_size - digit - 1));
        }
        char *u_int_to_str;
        u_int_to_str = malloc(12); // int range : 0 ~ 4,294,967,295. Thus, maximum 5 location is needed.
        sprintf(u_int_to_str, "%u", result); // Converting integer value into string.

        int reloc_size = (strlen(return_line) + strlen(u_int_to_str) + 2);
        char* return_mem_add = realloc(return_line, reloc_size); // During realloc, mem add can change due to limited size of original mem location.
        if(return_mem_add == NULL)
            printf("Mem reallocation failed.\n");
        return_line = return_mem_add; // Updating mem add because it can vary during realloc.

        memcpy(return_line + strlen(return_line), u_int_to_str, strlen(u_int_to_str)); // Copying converted string into return_line string.
        char blank[2] = {' ', '\0'}; // Making array of blank space and null to input on last part of string.
        memcpy(return_line + reloc_size - 2, &blank, 2); // Copying blank and null into last part of string.
        free(u_int_to_str);
    }

    return return_line; // Returns mem loc. Because when using realloc, mem add may change.
}

char* bin_to_float(char* bin_line, char* return_line, size_t target_size){
    size_t line_len = strlen(bin_line);
    size_t bin_size = 8 * target_size;
    size_t tot_qty = line_len / bin_size;
    size_t start_pos = strlen(return_line);
    
    int tmp[bin_size + 1]; // Make temporary binary store array.
    for(size_t trial = 1; trial <= tot_qty; trial++){
        float result = 0; // Make this to store calculated value.

        for(size_t pos = 0; pos < bin_size; pos++){ // Putting partial part of binary array into temporary which we want to calculate.
            size_t margin = (line_len - (bin_size * trial) + pos);
            tmp[pos] = *(bin_line + margin) - 48; // bin is saved as char. ASCII of 0 = 48. Thus we subtract 48 to get int type binary.
        }
        tmp[bin_size] = '\0'; // The last part of array should be NULL.

        // Converting binary into float #. By little endian and two's complement, last part of binary array would be determinant of negative.
        // First bit is sign bit.
        result = pow((-1), tmp[0]);
        
        // Second to 9th bit is notating factor of exponent part.
        float e_bias = -127; // Think different.
        for(size_t digit = 8; digit >= 1; digit--)
            e_bias += ((tmp[digit]) * pow(2, 8 - digit));
        result *= pow(2, e_bias);

        // Remaining part is notates mantissa, which XXXXpart of 1.XXXX part. And we can just consider 4 decimals.
        float mantissa = 1;
        for(size_t digit = 9; digit < 32; digit++){
            int square = 8 - digit;
            mantissa += ((tmp[digit]) * pow(2, square));
        }
        result *= mantissa;


        char *float_to_str;
        float_to_str = malloc(30); // float range : 1.175494351e-38 ~ 3.402823466e+38. Thus, maximum 5 location is needed.
        sprintf(float_to_str, "%.4f", result); // Converting integer value into string.
        size_t reloc_size = (strlen(return_line) + strlen(float_to_str) + 2);
        char* return_mem_add = realloc(return_line, reloc_size); // During realloc, mem add can change due to limited size of original mem location.
        if(return_mem_add == NULL)
            printf("Mem reallocation failed.\n");
        return_line = return_mem_add; // Updating mem add because it can vary during realloc.

        memcpy(return_line + strlen(return_line), float_to_str, strlen(float_to_str)); // Copying converted string into return_line string.
        char blank[2] = {' ', '\0'}; // Making array of blank space and null to input on last part of string.
        memcpy(return_line + reloc_size - 2, &blank, 2); // Copying blank and null into last part of string.
        free(float_to_str);
    }

    return return_line; // Returns mem loc. Because when using realloc, mem add may change.
}

char* bin_to_double(char* bin_line, char* return_line, size_t target_size){
    size_t line_len = strlen(bin_line);
    size_t bin_size = 8 * target_size;
    size_t tot_qty = line_len / bin_size;
    size_t start_pos = strlen(return_line);
    
    int tmp[bin_size + 1]; // Make temporary binary store array.
    for(size_t trial = 1; trial <= tot_qty; trial++){
        double result = 0; // Make this to store calculated value.

        for(size_t pos = 0; pos < bin_size; pos++){ // Putting partial part of binary array into temporary which we want to calculate.
            size_t margin = (line_len - (bin_size * trial) + pos);
            tmp[pos] = *(bin_line + margin) - 48; // bin is saved as char. ASCII of 0 = 48. Thus we subtract 48 to get int type binary.
        }
        tmp[bin_size] = '\0'; // The last part of array should be NULL.

        // Converting binary into float #. By little endian and two's complement, last part of binary array would be determinant of negative.
        // First bit is sign bit.
        result = pow((-1), tmp[0]);
        
        // Second to 9th bit is notating factor of exponent part.
        float e_bias = -1023; // Think different.
        for(size_t digit = 11; digit >= 1; digit--)
            e_bias += ((tmp[digit]) * pow(2, 11 - digit));
        result *= pow(2, e_bias);

        // Remaining part is notates mantissa, which XXXXpart of 1.XXXX part. And we can just consider 4 decimals.
        float mantissa = 1;
        for(size_t digit = 12; digit < 64; digit++){
            int square = 11 - digit;
            mantissa += ((tmp[digit]) * pow(2, square));
        }
        result *= mantissa;


        char *double_to_str;
        double_to_str = malloc(30); // Double range : 2.2250738585072014e-308 ~ 1.7976931348623158e+308. Thus, maximum 5 location is needed.
        sprintf(double_to_str, "%.4f", result); // Converting integer value into string.
        size_t reloc_size = (strlen(return_line) + strlen(double_to_str) + 2);
        char* return_mem_add = realloc(return_line, reloc_size); // During realloc, mem add can change due to limited size of original mem location.
        if(return_mem_add == NULL)
            printf("Mem reallocation failed.\n");
        return_line = return_mem_add; // Updating mem add because it can vary during realloc.

        memcpy(return_line + strlen(return_line), double_to_str, strlen(double_to_str)); // Copying converted string into return_line string.
        char blank[2] = {' ', '\0'}; // Making array of blank space and null to input on last part of string.
        memcpy(return_line + reloc_size - 2, &blank, 2); // Copying blank and null into last part of string.
        free(double_to_str);
    }

    return return_line; // Returns mem loc. Because when using realloc, mem add may change.
}