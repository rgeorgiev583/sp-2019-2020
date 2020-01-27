#include <stdio.h>
#include <stdlib.h>

#define REQUIRED_ARGUMENTS 0
#define DEFAULT_WIDTH 80

static int widthFlag = 0;
static int width;

static void handle_output_error(int res)
{
    if(res == EOF)
    {
        perror("Fold: ");
        exit(5);
    }
}

static void execute_fold(FILE *fp)
{
    int symbol;
    int currentLineLength = 0;
    int maxLineLength = widthFlag == 1 ? width : DEFAULT_WIDTH;

    while((symbol = getc(fp)) != EOF)
    {
        if(symbol != '\n' && currentLineLength == maxLineLength)
        {
            handle_output_error(putc('\n', stdout));
            currentLineLength = 1;
            
        }
        else if(symbol == '\n')
        {
            currentLineLength = 0;
        }
        else
        {
            ++currentLineLength;
        }

        handle_output_error(putc(symbol, stdout));
    }
}

int main(int argc, char **argv)
{
    if(argc < REQUIRED_ARGUMENTS + 1)
    {
        printf("Not enough arguments!\n");
        exit(1);
    }

    int filesStart = 1;
    if(argc > 1 && argv[1][0] == '-')
    {
        if(argv[1][1] != 'w')
        {
            printf("Not existing option!\n");
            exit(2);
        }
        widthFlag = 1;
        width = atoi(argv[1] + 2);
        if(width == 0)
        {
            printf("Invalid option argument!\n");
            exit(3);
        }
        filesStart = 2;
    }

    if(filesStart >= argc)
    {
        execute_fold(stdin);

        return 0;
    }

    for(int i = filesStart; i < argc; ++i)
    {
        FILE *fp = fopen(argv[i], "r");
        if(fp == NULL)
        {
            perror("Fold: ");
            exit(4);
        }
        execute_fold(fp);
    }

    return 0;
}
