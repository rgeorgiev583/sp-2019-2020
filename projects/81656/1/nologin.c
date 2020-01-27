#include <stdio.h>
#include <stdlib.h>

#define REQ_ARGS 0

int main(int argc, const char* const* argv) {
	if(argc > REQ_ARGS + 1) {
		exit(EXIT_FAILURE);
	}

	FILE *fp_r = fopen("/etc/nologin.txt", "r");
	if(fp_r == NULL) {
		puts("The account is currently unavailable.");
	}
	else {
		char c;
		while((c = getc(fp_r)) != EOF) {
			putchar(c);
		}
	}

	return 1;
}