#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// global var for width with default value 80
// because the func uses fgets() it reads only n-1 bytes so +1 is added
static long int wN = 81;

static void fold(FILE* fp){
    char buff[wN];
    // we need file current possition so we won't miss if a file starts with '\n'
    long int file_curr_pos = 0;
    // count newlines that are next to each other for if the buffer contains only the '\n'
    // from a line that contains more then the '\n' it won't put an extra '\n'
    int count_nl = 0;
    while(1){
        if (file_curr_pos == 0)
            file_curr_pos = ftell(fp);
        fgets(buff, wN, fp);
        if(feof(fp)) break;
        if (!strcmp(buff, "\n")){
            count_nl++;
            if(count_nl == 1 && file_curr_pos != 0)
                continue;
            puts(""); // or we can use fwrite(&buff...) for the buffer contains only '\n'
         }
        else if (strchr(buff, '\n')){
            size_t len_buff = strlen(buff);
            // it is used fwrite instead of puts so no exrtra '\n' is displayed on console
            fwrite(&buff, sizeof(char), len_buff, stdout);
            // we count the '\n' to be sure that we wont't miss to display a newline
            // if we are in the first statement the next cycle
            count_nl++;
        }
        else{
            puts(buff);
            count_nl = 0;
        }
    }
}

int main (int argc, const char *const *argv) {
    if (argc > 1){
        int i = strstr(argv[1], "-w") != NULL ? 2 : 1;
        if (strstr(argv[1], "-w") != NULL){
            wN = atol(argv[1]+2) + 1;
            if (argc == 2)
                fold(stdin);
        }
        for (i; i < argc; i++){
            FILE *fp = fopen(argv[i], "r");
            if (NULL == fp){
               perror("fopen");
               exit(EXIT_FAILURE);
            }
            fold(fp);
            if (EOF == fclose(fp)){
                perror("fclose");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
        fold(stdin);

    return EXIT_SUCCESS;
}
