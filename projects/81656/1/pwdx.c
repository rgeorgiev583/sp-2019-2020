#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* const* argv) {
	int i = 1;
	char c;
	const char pr[] = "/proc/";
	const char cwd[] = "/cwd";

	for(i; i<argc; ++i) {
/*Sazdavane na patq do faila, koito shte bade otvoren za chetene*/
		char pidLoc[128] = "";
		strcat(pid_Loc, pr);
		strcat(pid_Loc, argv[i]);
		strcat(pid_Loc, cwd);

		FILE *fp = fopen(pid_Loc, "r");
		if(fp == NULL) {
			perror(fopen);
			exit(EXIT_FAILURE);
		}
                fputs("Dir for PID ", stdout);
		fputs(argv[i], stdout);
		fputs(": ", stdout);

		while((c = getc(fp)) != EOF) {
			putchar(c);
		}

		fputs("\n", stdout);
	}

	return 0;
}