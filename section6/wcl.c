#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int i;
    int line = 0;

    for(i=1; i<argc; i++){
        FILE* f;
        int c;

        f = fopen(argv[i], "r");
        if(!f){
            perror(argv[i]);
            exit(1);
        }

        int pre;
        while((c = fgetc(f)) != EOF){
            pre = c;
            if(c == '\n') line++;
        }

        if(pre != '\n') line++;
    }

    printf("%d\n", line);
    exit(0);
}
