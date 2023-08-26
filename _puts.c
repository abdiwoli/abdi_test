# include "main.h"
/**
 * _puts -  prints string of the param
 * @str: string pram
 *
 */
void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}

}
