#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int parse_args(const int argc, const char** argv, int* c, int* d, int* set1, int* set2){
	*c=0;
	*d=0;
	*set1=-1;
	*set2=-1;
	for(int i=1; i<argc; i++){
		if(strcmp(argv[i], "-c")==0)*c=1;
		else if(strcmp(argv[i], "-d")==0)*d=1;
		else if(*set1==-1)*set1=i;
		else if(*set2==-1)*set2=i;
		else return -1;
	}
	return 0;
}

int in(const char c, const char* set){
	int n=strlen(set);
	for(int i=0; i<n; i++){
		if(c==set[i])return i;
	}
	return -1;
}

char transformation(const int pos, const char* set){
	int n=strlen(set);
	if(pos>n)return set[n-1];
	else return set[pos];
}

void delete(const char* set, int complimentary){
	char buff[BUFSIZ];
	char str[BUFSIZ];
	int r, j;
	while((r=read(STDIN_FILENO, buff, BUFSIZ))!=-1){
		j=0;
		for(int i=0; i<r; i++){
			if(in(buff[i], set)!=-1 && complimentary==1){
				str[j]=buff[i];
				j++;
			}
			else if(in(buff[i], set)==-1 && complimentary==0){
				str[j]=buff[i];
				j++;
			}
		}
		write(STDOUT_FILENO, str, j);
	}
}

void transform(const char* set1, const char* set2){
	char buff[BUFSIZ];
	char str[BUFSIZ];
	int r;
	while((r=read(STDIN_FILENO, buff, BUFSIZ))!=-1){
		for(int i=0; i<r; i++){
			int p=in(buff[i], set1);
			if(p!=-1){
				str[i]=transformation(p, set2);
			}
			else{
				str[i]=buff[i];
			}
		}
		write(STDOUT_FILENO, str, r);
	}
}

void transform_compimentary(const char* set1, const char* set2){
	char buff[BUFSIZ];
	char str[BUFSIZ];
	const char c=set2[strlen(set2)-1];
	int r;
	while((r=read(STDIN_FILENO, buff, BUFSIZ))!=-1){
		for(int i=0; i<r; i++){
			int p=in(buff[i], set1);
			if(p==-1 && buff[i]!='\n'){
				str[i]=c;
			}
			else{
				str[i]=buff[i];
			}
		}
		write(STDOUT_FILENO, str, r);
	}
}




int main(const int argc, const char **argv){
	int c, d, p1, p2;
	char *set1, *set2;
	if(parse_args(argc, argv, &c, &d, &p1, &p2)!=0 || p1==-1){
		perror("Invalid arguments");
		exit(EXIT_FAILURE);
	}
	
	if(c==1){
		if(d==0){
			if(p2==-1){
				perror("Invalid arguments");
				exit(EXIT_FAILURE);
			}
			transform_compimentary(argv[p1], argv[p2]);
		}
		else{
			if(p2!=-1){
				perror("Invalid arguments");
				exit(EXIT_FAILURE);
			}
			delete(argv[p1], 1);
		}
	}
	else if(d==1){
		if(p2!=-1){
			perror("Invalid arguments");
			exit(EXIT_FAILURE);
		}
		delete(argv[p1], 0);
	}
	else{
		if(p2==-1){
			perror("Invalid arguments");
			exit(EXIT_FAILURE);
		}
		transform(argv[p1], argv[p2]);
	}


	exit(EXIT_SUCCESS);	
}