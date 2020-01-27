#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
const int FN = 81585;

int main(const int argc, const char** argv){
	if(argc != 4){
		perror("Invalid number of arguments!");
		exit(EXIT_FAILURE);
	}
	const int N = atoi(argv[1]);
	int f1 = open(argv[2], O_RDONLY);
	if(f1 == -1){
		perror("Invalid open");
		exit(EXIT_FAILURE);
	}
	int f2 = open(argv[3], O_WRONLY);
	if(f2 == -1){
		perror("Invalid open");
		exit(EXIT_FAILURE);
	}
	const int OFFSET = N+FN%31+5;
	if(lseek(f2, OFFSET, SEEK_END) == -1){
		perror("Invalid lseek");
		exit(EXIT_FAILURE);
	}
	char* buff[BUFSIZ];
	int r;
	while((r=read(f1, buff, BUFSIZ)) > 0){
		write(f2, buff, r);
	}
	close(f1);
	close(f2);
	exit(EXIT_SUCCESS);

}