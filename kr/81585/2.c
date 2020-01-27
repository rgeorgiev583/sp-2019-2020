#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<wait.h>

void tr_without_args(const char* set1, const char* set2){
	int e1 = fork();
	if(e1==0){
		execlp("tr", "tr", set1, set2, NULL);
	}
	else{
		int status;
		waitpid(e1, &status, 0);
	}
}


void tr_with_args(const char* set1, const char* set2, const char* filename){
	int e1=fork();
	if(e1==0){
		int fd[2];
		if(pipe(fd) == -1){
			perror("Pipe failure!");
			exit(EXIT_FAILURE);
		}
		int e2=fork();
		if(e2==0){
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			execlp("cat", "cat", filename, NULL);
		}
		else{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			waitpid(e2, NULL, 0);
			execlp("tr", "tr", set1, set2, NULL);
		}

	}
	else{
		int status;
		waitpid(e1, &status, 0);
	}
}


int main(const int argc, const char** argv){
	if(argc < 3){
		perror("Invalid number of arguments!");
		exit(EXIT_FAILURE);
	}
	const char* set1 = argv[1];
	const char* set2 = argv[2];
	if(argc == 3){
		tr_without_args(set1, set2);
		exit(EXIT_SUCCESS);
	}
	for(int i=3; i<argc; i++){
		tr_with_args(set1, set2, argv[i]);
	}


	exit(EXIT_SUCCESS);
}