#include <stdio.h>

int main(){
    printf("rodata rodata rodata Can you modify this?\n");
    printf("rodata rodata rodata Can you modify this?\n");
    printf("rodata rodata rodata Can you modify this?\n");
    const int i = 0;
    printf("rodata rodata rodata |Can you modify this?\n");
    printf("rodata rodata rodata Can you modify this?\n");
    printf("rodata rodata rodata Can you modify this?\n");

    return 0;
}