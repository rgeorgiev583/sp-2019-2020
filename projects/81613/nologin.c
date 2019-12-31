#include <stdio.h>
#include <stdlib.h>

#define REQUIRED_ARG_COUNT 0

int main(int argc, const char* const* argv) {
	if(argc > REQUIRED_ARG_COUNT + 1) {
		puts("Invalid option argument.");
		exit(2);
	}
	
	FILE *fp = fopen("/etc/nologin.txt", "r");
	if(fp == NULL) {
		char message[] = "The account is currently unavailable.";
		puts(message);
	}
	else {
		char c;
		while((c = getc(fp)) != EOF) {
			putchar(c);
		}
	}
	
	return 1;
}

		
	