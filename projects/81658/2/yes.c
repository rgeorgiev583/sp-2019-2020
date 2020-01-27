#include<err.h>
#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, char* const* argv)
{

    if(argc<=1)
    {
        bool flag=true;
        while(flag)
        {

        puts("y");

        }
    }
    else
    {
        bool flag=true;
        while(flag)
        {
        int i;
        for(i=1;i<argc;i++)
        {
        write(1,argv[i],strlen(argv[i]));
        write(1," ",1);
        }
        write(1,"\n",1);
        }
    }

    return 0;
}
