#include "assignment4.h"

int main(){
    struct mem_info info_arr[128];
    size_t t_qty = 0;
    size_t e_pos = 0;

    char* heap_area = malloc(128);

    while(1){
        size_t menu = 0, rst = 0;
        printf("Do you want to allocate data (1) or deallocate data (2) ?\n");
        scanf("%ld", &menu);
        //getchar();
        if(menu == 1){ // If menu == 1 which is allocating data.
            printf("Input the type of data you want to allocate and the name of the data\n");
            scanf("%s", info_arr[t_qty].type);
            getchar();
            scanf("%s", info_arr[t_qty].name);
            getchar();
            for(size_t i = 0; i < t_qty; i++){
                if(!strcmp(info_arr[i].name, info_arr[t_qty].name))
                    rst = 3;
            }
            if(rst == 0){
                printf("Please input a value for the data type\n");
                rst = allocate(info_arr + t_qty, heap_area, &e_pos);
                t_qty++;
            }
        }
        else if(menu == 2){ // If menu == 2, which is deallocating data.
            printf("Input the name of data you want to deallocate\n");
            char d_name[51];
            scanf("%s", d_name);
            getchar();
            rst = 3;
            for(size_t i = 0; i < t_qty; i++){
                if(!strcmp(info_arr[i].name, d_name))
                    rst = 0;
            }
            if(rst == 0){
                deallocate(info_arr, heap_area, d_name, &t_qty, &e_pos);
                printf("%s has been deallocated\n", d_name);
            }
        }
        if(rst == 0){
            printf("There is memory dump!\n");
            dump_mem(heap_area, 128);
            printf("\n-----Data you have now-----\n");
            for(size_t i = 0; i < t_qty; i++){
                //printf("%s\n", info_arr[i].name);
                printf("%s %s %ld %ld\n", info_arr[i].type, info_arr[i].name, info_arr[i].s_pos, info_arr[i].t_len);
            }
            printf("last pos : %ld\n", e_pos);
        }
        else if(rst == 1){ // Wrong type, value error case.
            t_qty--;
        }
        else if(rst == 2){ // Not enough mem case.
            printf("There is not enough memory for the data which you require, you can only use %ld byte(s).\n", 128 - e_pos);
            t_qty--;
        }
        else if(rst == 3){ // Dup | non existing name error case
            //Do nothing.
        }
        //break;
    }

    free(heap_area);
    return 0;
}