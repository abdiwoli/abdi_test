#include <stdio.h>
#include <string.h>

/**
 * commentAfterHash - function that comments out everything after hash
 * @str: string
 *
 */

void commentAfterHash(char str[])
{
	int i, hashIndex, len;

	len = strlen(str);

	for (i = 0; i < len; i++)
{
	if (str[i] == '#')
{ /* Find the hash character */
	hashIndex = i;
	break;
}
}

for (i = hashIndex + 1; i < len; i++)
{
str[i] = '\0'; /* Replace each character after the hash character with a '/' */
}
	printf("Commented String: %s\n", str);
}
