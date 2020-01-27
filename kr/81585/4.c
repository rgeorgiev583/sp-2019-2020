#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<wait.h>


int main(const int argc, char** argv){
	int e1=fork();
	if(e1==0){
		int fd[2];
		pipe(fd);
		int e2=fork();
		if(e2==0){
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			argv[0]="pidof";
			execvp("pidof", argv);
		}
		else{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			waitpid(e2, NULL, 0);
			execlp("xargs", "xargs", "kill", NULL);
		}

	}
	else{
		int status;
		waitpid(e1, &status, 0);
	}

	exit(EXIT_SUCCESS);
}