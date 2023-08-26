#include <stdio.h>
#include <unistd.h>

void non_inter_active_mode(char *arg);
void inter_active_mode(char *arg);

/**
 * main - the program main
 * Return: 0;
 * @argc: int
 * @argv: array
 */

int main(int argc, char **argv)
{
	argc = 0;

	if (!isatty(fileno(stdin)))
		non_inter_active_mode(argv[argc]);
	else
		inter_active_mode(argv[argc]);
	return (0);
}
