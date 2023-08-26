#include "main.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
#define  L 1024

/**
 * non_inter_active_mode - function name
 * @program: program name
 */

void non_inter_active_mode(char *program)
{
	char *line = NULL, input[L];
	int handle = 0, status = 0;
	int len = 0;
	char **args, *tken, cd[L];

	while (1)
	{
		args = malloc(sizeof(char) * L);
		line = NULL;
		if (_getline(&line, &len, stdin) == -1)
		{
			free(line);
			break;
		}
		strncpy(input, line, sizeof(input));
		input[strcspn(input, "\n")] = '\0';
		line[strcspn(line, "\n")] = '\0';
		tken = _strtok(line, " ");
		while (tken == NULL && line == NULL)
			tken = _strtok(NULL, " ");
		if (tken == NULL || strcmp(tken, "") == 0 || strcmp(tken, " ") == 0)
			continue;
		handle = token_input(input, args, program, line, handle);
		if (strcmp(tken, "cd") == 0)
			perror(args[1]);
		if (process(tken, handle, args, cd, line))
			continue;
		handle = important(args, line, status, handle);
		status = 0;
		memory(args, line);
	}
	exit_status(handle);
	exit(handle);
}
