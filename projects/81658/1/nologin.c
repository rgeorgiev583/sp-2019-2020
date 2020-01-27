#include <sys/cdefs.h>
#include <stdio.h>
#include <syslog.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	const char *user, *tt;

	if ((tt = ttyname(0)) == NULL)
		tt = "UNKNOWN";
	if ((user = getlogin()) == NULL)
		user = "UNKNOWN";
	openlog("nologin", LOG_CONS, LOG_AUTH);
	syslog(LOG_CRIT, "Attempted login by %s on %s", user, tt);
	closelog();

	printf("%s", "This account is currently unavailable");
	return 1;
}




