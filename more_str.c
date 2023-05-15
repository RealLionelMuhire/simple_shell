#include "shell.h"

size_t _strcspn(const char *str1, const char *str2)
{
	const char *p, *spanp;
	char c, sc;

/*
 * Skip any characters in str2, excluding the terminating null.
 */
	cont:
	c = *str1++;
	for (spanp = str2; (sc = *spanp++) != 0;)
	{
		if (sc == c)
		goto cont;
}

/*
* If c is the terminating null, we're done.
*/
if (c == 0)
return (str1 - 1 - start);

/*
* Otherwise, advance through str1 until we find another
* character from str2, or until we hit the terminating null.
*/
p = str1;
while ((c = *p++) != 0) {
spanp = str2;
do {
if ((sc = *spanp++) == c)
return (p - 1 - start);
} while (sc != 0);
}

return (p - 1 - start);
}

