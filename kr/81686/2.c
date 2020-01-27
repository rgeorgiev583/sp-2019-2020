#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main(int argc,char** argv)
{

    //�������� �� � ��������� � ���� unresolved reference ��� �������� �� pipe(fd) ������ ������� �������)
    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if(pid == 0){
        close(fd[0]);
        dup2(fd[0],STDIN_FILENO);
        execlp("sort","sort",argv);

    }

    if(pid>0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);

        wait(NULL);

        execv("uniq",NULL);

    }
    close(fd[1]);
    close(fd[0]);


    return 0;
}
