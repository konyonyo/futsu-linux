#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int i;

    for(i=1; i<argc; i++){
        FILE* f;
        int c;

        f = fopen(argv[i], "r");
        if(!f){
            perror(argv[i]);
            exit(1);
        }

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
        fclose(f);
    }
    exit(0);
}
