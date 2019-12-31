#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* const* argv) {
	int i = 1;
	char c;
	const char proc[] = "/proc/";
	const char cwd[] = "/cwd";
	
	for(i; i<argc; ++i) {
		char pidLocation[128] = "";
		strcat(pidLocation, proc);
		strcat(pidLocation, argv[i]);
		strcat(pidLocation, cwd);
		
		FILE *fp = fopen(pidLocation, "r");
		if(fp == NULL) {
			perror(argv[i]);
			exit(EXIT_FAILURE);
		}
		
		fputs(argv[i], stdout);
		fputs(": ", stdout);
		
		while((c = getc(fp)) != EOF) {
			putchar(c);
		}
		
		fputs("\n", stdout);
	}
	
	return 0;
}
		