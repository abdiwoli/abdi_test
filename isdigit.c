#include <stdio.h>
#include <ctype.h>
/**
 * all_digits - function name
 * @s: string
 * Return: 1 or 0
 */
int all_digits(char *s)
{
	while (*s != '\0')
	{
		if (!isdigit(*s))
		{
			return (0);
		}
		s++;
	}
	return (1);
}
