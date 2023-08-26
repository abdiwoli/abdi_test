#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/**
 * is_empty_spaces - function name
 * @strs: string
 * Return: int
 */
int is_empty_spaces(char *strs)
{
	char *str = strdup(strs);

	while (*str)
	{
		if (!isspace((unsigned char)*str))
		{
			free(str);
			return (0);
		}
		str++;
	}
	free(str);
	return (1);
}
