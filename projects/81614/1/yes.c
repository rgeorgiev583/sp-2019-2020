#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
int main(int argc, const char* argv[])
{
	while(true)
	{
		if(argc<=1)
		{
			write(STDOUT_FILENO,"y\n",2);
		}
		else
		{
			int i;
			for(i=1;i<argc;i++)
			{
				write(STDOUT_FILENO,argv[i],strlen(argv[i]));
				if(argv[i] != argv[argc])
				{
					write(STDOUT_FILENO," ",1);
				}
			}
			write(STDOUT_FILENO,"\n",1);
		}
	}
	return EXIT_SUCCESS;
}
