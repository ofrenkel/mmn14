#include <ctype.h>
#include "utils.h"

/*
 * Trim (strip white spaces) the given string in place, returning a pointer to
 * the start of the trimmed string.
 *
 * Parameter str: The string to trim.
 * Returns: A pointer to the start of the trimmed string.
 */
char *trim(char *str) {
	char *end;

	/* Trim leading spaces. */
	for (; isspace(*str); str++);

	/* If string is all spaces, return immediately. */
	if (*str == 0) {
    	    return str;
	}

	/* Point end to last char at str */
	end = str + strlen(str) - 1;

	/* Trim trailing spaces. */
	for (; isspace(*end); end--);

	/* Set last place after end to NULL (0). */
	*(end + 1) = 0;

	return str;
}