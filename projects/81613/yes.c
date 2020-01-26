#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define REQUIRED_ARG_COUNT 1

int main(int argc, const char* const* argv) {
	char y[] = "y";
	bool infinityLoop = true;
	int i = 1;
	
	if(argc < REQUIRED_ARG_COUNT + 1) {
		while(infinityLoop) {
			puts(y);
		}
	}
	else {
		while(infinityLoop) {
			i = 1;
			for(i; i < argc - 1; ++i) {
				fputs(argv[i], stdout);
				fputs(" ", stdout);
			}
			
			puts(argv[i]);
		}
	}
	
	return 0;
}
			