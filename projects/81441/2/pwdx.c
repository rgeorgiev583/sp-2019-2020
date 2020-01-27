#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>



int main(int argc, const char* const* argv)
{
    if (argc <= 1)
    {
        return 1;
    }

    int i = 1;
    for (i; i < argc; i++)
    {
        char location[20] = "proc/";
        strcat(location, argv[i]);
        strcat(location, "/cwd");
        char buffer;
        ssize_t count;
        int fd = open(location, O_RDONLY);

        if (fd == -1)
        {
            perror(argv[1]);
            return 2;
        }

        while((count = read(fd, &buffer, 1)) != 0)
        {
            write(STDOUT_FILENO, &buffer, 1);
        }
    }


    return 0;
}
