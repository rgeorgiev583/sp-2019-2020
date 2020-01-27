#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int viz(char a){
	return ((int)a>=32 && (int)a<=126);
}

void string(const char* filename){
	int fd = open(filename, O_RDONLY);
	int cnt=0;
	char arr[4], buff[1];
	int r;
	while((r=read(fd, buff, 1)) == 1){
		if(viz(buff[0])){
			arr[cnt%4]=buff[0];
			cnt++;
			if(cnt==4){
				printf("%s", arr);
			}
			else if(cnt>4){
				printf("%c", buff[0]);
			}
		}
		else{
			if(cnt>=4){
				printf("\n");
			}
			cnt=0;
		}
	}
}


int main(const int argc, const char** argv){
	if(argc == 1){
		char* filename;
		scanf("%s", filename);
		string(filename);
		exit(EXIT_SUCCESS);
	}
	
	for(int i=1; i<argc; i++){
		string(argv[i]);
	}


	exit(EXIT_SUCCESS);

}