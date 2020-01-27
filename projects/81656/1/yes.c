#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define REQ_ARGS 1

int main(int argc, const char* const* argv) {
	char y[] = "y";
	bool i_l = true;
	int n = 1;
/*bez argumenti*/
	if(argc < REQ_ARGS + 1) {
		while(il) {
			puts(y);
		}
	}
	else {
		while(i_l) {
			n = 1;
			for(n; n < argc - 1; n++) {
				fputs(argv[n], stdout);
				fputs(" ", stdout);
			}

			puts(argv[n]);
		}
	}

	return 0;
}
