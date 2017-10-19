#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <getopt.h>

static struct option longopts[] = {
    {"tab", no_argument, NULL, 't'},
    {"newline", no_argument, NULL, 'n'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0}
};

enum Option{
    TAB = 1,
    NEWLINE = 2,
};

int get_option(int argc, char* argv[]){
    int opt;
    int result = 0;
    while((opt = getopt_long(argc, argv, "tnh", longopts, NULL)) != -1){
        switch(opt){
            case 't':
                result |= TAB;
                break;
            case 'n':
                result |= NEWLINE;
                break;
            case 'h':
                fprintf(stdout, "Usage: %s [-t] [-n] [FILE ...]\n",
                    argv[0]);
                exit(0);
            case '?':
                fprintf(stderr, "Usage: %s [-t] [-n] [FILE ...]\n",
                    argv[0]);
                exit(1);
        }
    }
    return result;
}

void do_cat(FILE* f, int option){
    int c;
    if(option == TAB){
        while((c = fgetc(f)) != EOF){
            switch(c){
                case '\t':
                    if(putchar('\\') < 0 || putchar('t') < 0) exit(1);
                    break;
                default:
                    if(putchar(c) < 0) exit(1);
            }
        }
    }else if(option == NEWLINE){
        while((c = fgetc(f)) != EOF){
            switch(c){
                case '\n':
                    if(putchar('$') < 0 || putchar('\n') < 0) exit(1);
                    break;
                default:
                    if(putchar(c) < 0) exit(1);
            }
        }
    }else if(option == (TAB | NEWLINE)){
        while((c = fgetc(f)) != EOF){
            switch(c){
                case '\t':
                    if(putchar('\\') < 0 || putchar('t') < 0) exit(1);
                    break;
                case '\n':
                    if(putchar('$') < 0 || putchar('\n') < 0) exit(1);
                    break;
                default:
                    if(putchar(c) < 0) exit(1);
            }
        }
    }else{
        while((c = fgetc(f)) != EOF){
            if(putchar(c) < 0) exit(1);
        }
    }
}

int main(int argc, char* argv[]){
    int option = get_option(argc, argv);

    if(optind == argc){
        do_cat(stdin, option);
    }else{
        int i;
        for(i=optind; i<argc; i++){
            FILE* f;
            f = fopen(argv[i], "r");
            if(!f){
                perror(argv[i]);
                exit(1);
            }

            do_cat(f, option);

            fclose(f);
        }
    }
    exit(0);
}
