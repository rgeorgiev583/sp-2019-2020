#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>

int len(const char* word)
{
    int index = 0;
    while(word[index] != '\0')
    {
        index++;
    }
    return index;
}

void print(char* sentance)
{
    write(STDOUT_FILENO, sentance, len(sentance));
}

int main(int argc, const char* const* argv)
{
    if (argc <= 1)
    {
        bool infinity = true;
        while(infinity)
        {
            write(STDOUT_FILENO, "y", 1);
            write(STDOUT_FILENO, "\n", 1);
        }
    }
    else
    {
        bool infinity = true;
        while(infinity)
        {
            int i = 1;
            for(i; i < argc; i++)
            {
                print(argv[i]);
                write(STDOUT_FILENO, " ", 1);
            }
            write(STDOUT_FILENO, "\n", 1);
        }
    }

    return 0;
}
