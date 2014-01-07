#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

/**
 * Returns a randomly generated int.
 * Uses /dev/urandom
 * @TODO Has to be improved to work on non unix system
 */
unsigned int utils_get_random_int(unsigned int min, unsigned int max)
{
	unsigned int rInt;

#ifdef _WIN32
	srand(time(NULL));
	rInt = min + (rand() % max);
#else
	int randomData = open("/dev/urandom", O_RDONLY);
	read(randomData, &rInt, sizeof rInt);

	rInt = rInt % (max - min) + min;
	close(randomData);
#endif

	return rInt;
}

/**
 * Function to read a char* from stdin
 * from paxdiablo, http://stackoverflow.com/questions/4023895/how-to-read-string-entered-by-user-in-c
 */
int utils_get_line(const char *prmpt, char *buff, size_t sz)
{
	int ch, extra;

	// Get line with buffer overrun protection.
	if (prmpt != NULL) {
		printf("%s", prmpt);
		fflush(stdout);
	}
	if (fgets(buff, (int) sz, stdin) == NULL)
		return INPUT_EMPTY;

	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (buff[strlen(buff)-1] != '\n') {
		extra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF))
			extra = 1;
		return (extra == 1) ? INPUT_TOO_LONG : INPUT_OK;
	}

	// Otherwise remove newline and give string back to caller.
	buff[strlen(buff)-1] = '\0';

	return INPUT_OK;
}
