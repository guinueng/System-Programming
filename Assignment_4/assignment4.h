#include <stdio.h> // Use for printf, scanf, etc...
#include <stdlib.h> // Use for malloc, free.
#include <string.h> // Use for strcmp.

enum data_type { Short, Char, Float, Long, Int, Struct };

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
    if(!strcmp(target -> type, "Short")){ // Short has 2 bytes.
        size_t data;
        scanf("%ld", &data);
        if(data >= 0 && data < 32768){
            target -> s_pos = *s_pos;
            target -> t_len = 2;
            for(size_t i = 0; i < 2; i++){
                *(mem_area + *s_pos + i) = (data % 256);
                data /= 256;
            }
            *s_pos += 2;
        }
        else{
            printf("Wrong Value.\nDo nothing.\n");
            return 1;
        }
        printf("Complete\n");
    }
    else if(!strcmp(target -> type, "Char")){ // Char has 1 bytes. -> Does we get input by letter or just number?
        printf("Char!\n");
        char data;
        scanf("%c", &data); // Get input by number.
        getchar(); // <- 
        printf("Got value : %d\n",data);
        if(data >= 0 && data < 128){
            target -> s_pos = *s_pos;
            target -> t_len = 1;
            *(mem_area + *s_pos) = data;
            *s_pos += 1;
        }
        else{
            printf("Wrong Value.\nDo nothing.\n");
            return 1;
        }
    }
    else if(!strcmp(target -> type, "Float") || !strcmp(target -> type, "float")){ // Float has 4 bytes.
        printf("Float\n");
        // by using union input float -> print unsigned int
    }
    else if(!strcmp(target -> type, "Long")){ // Long has 8 bytes (Range given by assignment description).
        unsigned  long data;
        scanf("%ld", &data);
        if(data >= 0 && data <= 9223372036854775807){
            target -> s_pos = *s_pos;
            target -> t_len = 8;
            for(size_t i = 0; i < 8; i++){
                *(mem_area + *s_pos + i) = (data % 256);
                data /= 256;
            }
            *s_pos += 8;
        }
        else{
            printf("Wrong Value.\nDo nothing.\n");
            return 1;
        }
    }
    else if(!strcmp(target -> type, "Int")){ // Int has 4 bytes.
        long data;
        scanf("%ld", &data);
        if(data >= 0 && data < 2147483648){
            target -> s_pos = *s_pos;
            target -> t_len = 4;
            for(size_t i = 0; i < 4; i++){
                *(mem_area + *s_pos + i) = (data % 256);
                data /= 256;
            }
            *s_pos += 4;
        }
        else{
            printf("Wrong Value.\nDo nothing.\n");
            return 1;
        }
    }
    else if(!strcmp(target -> type, "Struct")){ // Struct has vary size.
        printf("Struct\n");
    }
    else{
        printf("Wrong type.\nDo nothing.\n");
        return 1;
    }

    return 0;
}

void deallocate(struct mem_info* target, char* mem_area, char* name, size_t* qty, size_t* e_pos){
    size_t indicate = 0;
    printf("qty : %d\n", *qty);
    for(size_t i = 0; i < *qty; i++){
        printf("%d th trial\n", i);
        if(!indicate && !strcmp(target[i].name, name)){
            printf("Target detected\n");
            indicate++;
        }
        if(indicate){
            printf("Target to move : %s %s %ld %ld\n",target[i + 1].type, target[i + 1].name, target[i + 1].s_pos, target[i + 1].t_len);
            printf("Target pos : %s %s %ld %ld\n", target[i].type, target[i].name, target[i].s_pos, target[i].t_len);
            if(i < *qty - 1){
                printf("Target i : %d\n", i);
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
                *e_pos = target[i - 1].s_pos + target[i - 1].t_len;
            }
        }
    }
    *qty -= 1;
}