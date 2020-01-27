#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>


int main(int argc, const char* const* argv)
{
    if (argc > 1)
    {
        return 1;
    }

    int fd = open("etc/nologin.txt", O_RDONLY);

    if(fd != -1)
    {
        ssize_t count;
        char buffer;
        while((count = read(fd, &buffer, 1)) != 0)
        {
            write(STDOUT_FILENO, &buffer, 1);
        }
    }
    else
    {
        write(STDOUT_FILENO, "The account is currently unavailable.", 37);
    }

    return 1;
}
