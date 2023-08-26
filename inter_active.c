#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
#define  L 1024

/**
 * important - function name
 * @args: array
 * @line: string
 * @status: int
 * @handle: int
 * Return: int
 */
int important(char **args, char *line, int status, int handle)
{
	pid_t pid;

		pid = fork();
		if (pid == 0)
		{
			handle = child_process(args, line);
		}
		else if (pid > 0)
		{
			status = 0;
			waitpid(pid, &status, 0);
			if (status > 2)
				status = 2;
			exit_status(status);
			return (status);
		}
		else
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		return (handle);
}
/**
 * memory - function name
 * @args: array
 * @line: string
 */
void memory(char **args, char *line)
{
	int i = 0;

	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
		for (i = 0; args[i] != NULL; i++)
		{
			free(args[i]);
			args[i] = NULL;
		}
		free(args);
		args = NULL;
}

/**
 * process - function name
 * @tken: tokren word
 * @handle: int
 * @args: array
 * @cd: char
 * @line: to free string
 * Return: int
 */

int process(char *tken, int handle, char **args, char *cd, char *line)
{
		if (is_empty_spaces(tken))
		{
			memory(args, line);
			return (1);
		}

		if (strcmp(tken, "clear") == 0)
		{
			memory(args, line);
			_puts("\033[2J\033[H");
			return (1);
		}
		if (strcmp(tken, "env") == 0)
		{
			memory(args, line);
			_getenv();
			return (1);
		}
		if (strcmp(tken, "cd") == 0 && chdir(args[1]) == 0)
		{
			memory(args, line);
			getcwd(cd, sizeof(cd));
			return (1);
		}
		if (handle)
		{
			memory(args, line);
			return (1);
		}
		return (0);
}

/**
 * inter_active_mode - function to check if interactive mode
 * @program: name
 */

void inter_active_mode(char *program)
{
	char *line = NULL, input[L];
	int handle = 0, len = 0, status = 0;
	char **args, *tken, cd[L];

	while (1)
	{
		args = malloc(sizeof(char) * L);
		line = NULL;
		_puts("$ ");
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
		{
			memory(args, line);
			continue;
		}

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
