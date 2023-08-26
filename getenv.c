#include <stdio.h>
#include "main.h"
/**
 * _getenv - a function to get the environment
 */

void _getenv(void)
{
	int i;

	if (environ == NULL)
		return;


	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
