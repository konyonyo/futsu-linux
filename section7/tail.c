#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_N_LINES 10

void do_tail(FILE* f){
    int total_line = 0;
    int c;
    int pre;
    while((c = getc(f)) != EOF){
        pre = c;
        if(c == '\n'){
            total_line++;
        }
    }
    if(pre != '\n'){
        total_line++;
    }

    fseek(f, 0, SEEK_SET);

    int line = 0;
    if(total_line <= DEFAULT_N_LINES){
        while((c = getc(f)) != EOF){
            if(putchar(c) < 0) exit(1);
        }
    }else{
        while((c = getc(f)) != EOF){
            if(c == '\n'){
                line++;
                if(line == total_line - DEFAULT_N_LINES){
                    while((c = getc(f)) != EOF){
                        if(putchar(c) < 0) exit(1);
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(stderr, "Usage: %s FILE [FILE ...]\n", argv[0]);
        exit(1);
    }else{
        FILE* f;
        int i;
        for(i=1; i<argc; i++){
            f = fopen(argv[i], "r");
            if(!f){
                perror(argv[i]);
                exit(1);
            }
            do_tail(f);
            fclose(f);
        }
    }

    exit(0);
}
