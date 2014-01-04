#include <stdio.h>
#include <string.h>
#include "test.h"

void assert_str_equals(const char *val1, const char *val2)
{
	if (strncmp(val1, val2, strlen(val1)) == 0 && strncmp(val2, val1, strlen(val2)) == 0)
		printf("\033[00;32mOK: Asserting that %s equals %s\033[00m\n", val1, val2);
	else
		printf("\033[31mKO: Asserting that %s equals %s\033[00m\n", val1, val2);
}

void assert_int_equals(const int val1, const int val2)
{
	if (val1 == val2)
		printf("\033[00;32mOK: Asserting that %d equals %d\033[00m\n", val1, val2);
	else
		printf("\033[31mKO: Asserting that %d equals %d\033[00m\n", val1, val2);
}

void assert_long_equals(const long val1, const long val2)
{
	if (val1 == val2)
		printf("\033[00;32mOK: Asserting that %ld equals %ld\033[00m\n", val1, val2);
	else
		printf("\033[31mKO: Asserting that %ld equals %ld\033[00m\n", val1, val2);
}

void assert_null(void *val)
{
	if (val == NULL)
		printf("\033[00;32mOK: The given value is null\033[00m\n");
	else
		printf("\033[31mKO: The given value is not null\033[00m\n");
}



void assert_str_not_equals(const char *val1, const char *val2)
{
	if (strncmp(val1, val2, strlen(val1)) != 0 || strncmp(val2, val1, strlen(val2)) != 0)
		printf("\033[00;32mOK: Asserting that %s is different than %s\033[00m\n", val1, val2);
	else
		printf("\033[31mKO: Asserting that %s is different than %s\033[00m\n", val1, val2);
}

void assert_int_not_equals(const int val1, const int val2)
{
	if (val1 != val2)
		printf("\033[00;32mOK: Asserting that %d is different than %d\033[00m\n", val1, val2);
	else
		printf("\033[31mKO: Asserting that %d is different than %d\033[00m\n", val1, val2);
}

void assert_long_not_equals(const long val1, const long val2)
{
	if (val1 != val2)
		printf("\033[00;32mOK: Asserting that %ld is different than %ld\033[00m\n", val1, val2);
	else
		printf("\033[31mKO: Asserting that %ld is different than %ld\033[00m\n", val1, val2);
}

void assert_not_null(void *val)
{
	if (val != NULL)
		printf("\033[00;32mOK: The given value is not null\033[00m\n");
	else
		printf("\033[31mKO: The given value is null\033[00m\n");
}
