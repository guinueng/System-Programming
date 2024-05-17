#include <stdio.h> // Use for printf, scanf, etc...
#include <stdlib.h> // Use for malloc, free.
#include <string.h> // Use for strcmp.
#include <stdint.h> // To use uint32_t.

enum data_type { Short, Char, Float, Long, Int, Struct };

union floating_point{
    float value;
    uint32_t conv_value;
};
struct mem_info{
    char    name[51];
    char    type[7];
    size_t  s_pos;
    size_t  t_len;
};

void dump_mem(const void *mem, size_t len){ // Code given by assignment explain pdf file. Printing specific mem area.
    const char *buffer = mem;
    size_t i;
    for (i=0; i<len; i++){
        if (i>0 && i%16 == 0){
            printf("\n");
        }
        printf("%02x ", buffer[i] & 0xff);
    }
    puts("");
}

size_t allocate(struct mem_info* target, char* mem_area, size_t* s_pos){

    //printf("Given Type : %s, Name : %s\n", target -> name)
    if(!strcmp(target -> type, "Short") || !strcmp(target -> type, "short")){ // Short has 2 bytes.
        unsigned long long data;
        scanf("%llu", &data);
        getchar();
        if(*s_pos > 126) // Check there is enough mem space.
            return 2;
        else if(data >= 0 && data < 32768){ // Check data input range.
            target -> s_pos = *s_pos; // Inside range, input data into mem.
            target -> t_len = 2;
            for(size_t i = 0; i < 2; i++){
                *(mem_area + *s_pos + i) = (data % 256);
                data /= 256;
            }
            *s_pos += 2;
        }
        else{ // If given data exceed range, do nothing.
            printf("There is invalid input\n");
            return 1;
        }
    }
    else if(!strcmp(target -> type, "Char") || !strcmp(target -> type, "char")){ // 1. Char has 1 bytes. -> Does we get input by letter or just number?
        char data;
        scanf("%c", &data); // 4. Get input by number or char?
        getchar(); // <- Need to check else case.
        if(*s_pos > 127)
            return 2;
        else if(data >= 0 && data < 128){
            target -> s_pos = *s_pos;
            target -> t_len = 1;
            *(mem_area + *s_pos) = data;
            *s_pos += 1;
        }
        else{
            printf("There is invalid input\n");
            return 1;
        }
    }
    else if(!strcmp(target -> type, "Float") || !strcmp(target -> type, "float")){ // Float has 4 bytes.
        // by using union input float -> print unsigned int
        union floating_point point;
        scanf("%f", &point.value);
        getchar();
        if(*s_pos > 124)
            return 2;
    
        uint32_t calc_val = point.conv_value;
        target -> s_pos = *s_pos;
        target -> t_len = 4;
        for(size_t i = 0; i < 4; i++){
            *(mem_area + *s_pos + i) = (calc_val % 256);
            calc_val /= 256;
        }
        *s_pos += 4;

    }
    else if(!strcmp(target -> type, "Long") || !strcmp(target -> type, "long")){ // Long has 8 bytes (Range given by assignment description).
        unsigned long long data;
        scanf("%llu", &data);
        getchar();

        if(*s_pos > 120)
            return 2;
        else if(data >= 0 && data <= 9223372036854775807){
            target -> s_pos = *s_pos;
            target -> t_len = 8;
            for(size_t i = 0; i < 8; i++){
                *(mem_area + *s_pos + i) = (data % 256);
                data /= 256;
            }
            *s_pos += 8;
        }
        else{
            printf("There is invalid input\n");
            return 1;
        }
    }
    else if(!strcmp(target -> type, "Int") || !strcmp(target -> type, "int")){ // Int has 4 bytes.
        unsigned long long data;
        scanf("%llu", &data);
        getchar();
        if(*s_pos > 124)
            return 2;
        else if(data >= 0 && data < 2147483648){
            target -> s_pos = *s_pos;
            target -> t_len = 4;
            for(size_t i = 0; i < 4; i++){
                *(mem_area + *s_pos + i) = (data % 256);
                data /= 256;
            }
            *s_pos += 4;
        }
        else{
            printf("There is invalid input\n");
            return 1;
        }
    }
    else if(!strcmp(target -> type, "Struct") || !strcmp(target -> type, "struct")){ // Struct has vary size.
        printf("Struct\n");
        printf("How many data should be in the struct\n");
        target -> s_pos = *s_pos;
        target -> t_len = 0;
        size_t qty, rst;
        scanf("%ld", &qty);
        getchar();
        printf("Please input each type and its value\n");
        for(size_t i = 0; i < qty; i++){ // Allocating element of struct.
            struct mem_info tmp;
            scanf("%s", tmp.type); // Get type.
            getchar(); // Rm space.
            tmp.name[0] = (char)i; // Make fake name.
            rst = allocate(&tmp, mem_area, s_pos);
            if(rst == 0)
                target -> t_len += tmp.t_len;
            else
                break; // On piazza, there was answer that we can dealt w/ any exception exec timing on long value input on struct.
                // Such as we can exec exception by checking val on by one like this case, or get all the value and exec exception case.
        }
        if(rst != 0){ // When returned wrong type | wrong value error(1) or not enough mem space error(2).
            printf("Returned 1\n");
            for(size_t i = 0; i < target -> t_len; i++)
                mem_area[target -> s_pos + i] = 0;
            *s_pos = target -> s_pos;
            if(rst == 4){
                while( getchar() != '\n' );
                return 1;
            }
            else if (rst == 1)
                return 1;
            else
                return 2; // 2. Need to fix or consider when mem alloc failed on struct building, does we have to print remaining mem size?
        }
    }
    else{
        printf("Invalid type\n");
        return 4;
    }

    return 0;
}

void deallocate(struct mem_info* target, char* mem_area, char* name, size_t* qty, size_t* e_pos){
    size_t indicate = 0;
    printf("qty : %ld\n", *qty);
    for(size_t i = 0; i < *qty; i++){
        printf("%ld th trial\n", i);
        if(!indicate && !strcmp(target[i].name, name)){
            printf("Target detected\n");
            indicate++;
        }
        if(indicate){
            printf("Target to move : %s %s %ld %ld\n",target[i + 1].type, target[i + 1].name, target[i + 1].s_pos, target[i + 1].t_len);
            printf("Target pos : %s %s %ld %ld\n", target[i].type, target[i].name, target[i].s_pos, target[i].t_len);
            if(i < *qty - 1){
                printf("Target i : %ld\n", i);
                //size_t len = target[i + 1].e_pos - target[i + 1].s_pos;
                for(size_t j = 0; j < target[i + 1].t_len; j++)
                    *(mem_area + target[i].s_pos + j) = *(mem_area + target[i + 1].s_pos + j);
                strcpy(target[i].name, target[i + 1].name);
                strcpy(target[i].type, target[i + 1].type);
                target[i].t_len = target[i + 1].t_len;
                target[i + 1].s_pos = target[i].s_pos + target[i].t_len;

                printf("Moved target : %s %s %ld %ld\n", target[i].type, target[i].name, target[i].s_pos, target[i].t_len);
            }
            else{
                printf("Else case\n");
                for(size_t j = target[i].s_pos; j < *e_pos; j++)
                    *(mem_area + j) = '\0';
                if(i != 0)
                    *e_pos = target[i - 1].s_pos + target[i - 1].t_len;
                else
                    *e_pos = 0;
            }
        }
    }
    *qty -= 1;
}