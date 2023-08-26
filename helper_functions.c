#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
#include <errno.h>
#include <ctype.h>
#define L 256

/**
 * terminate - function to terminate a function process and exit
 * @args: array
 * @path: string to free
 * @line: to free
 * @program: name of program
 * Return: 1 on success
 */

int terminate(char **args, char *path, char *line, char *program)
{
	int status, i = 0;

	if (args[1] == NULL)
		return (1);
	if (all_digits(args[1]))
		status = atoi(args[1]);
	else
	{
		other_error(args, program);
		status = 2;
	}
	exit_status(status);
	while (args[i] != NULL)
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	if (line != NULL)
		free(line);
	free(path);
	if (args != NULL)
		free(args);
	if (status < 0)
		status = 2;
	exit(status);
	return (0);
}

/**
 * error_handle - function name
 * @input: string
 * @program: program name
 * @path_copy: string to free
 * @args: array
 */
void error_handle(char *path_copy, char *program, char *input, char **args)
{
	int n = 0;
	char errorMessage[100];

	while (args[n] != NULL)
		n++;
	free(path_copy);
	exit_status(2);
	sprintf(errorMessage, "%s: %d: %s: not found\n", program, n, input);
	fprintf(stderr, "%s", errorMessage);
}

/**
 * handle_path - function
 * @input: string
 * @args: array
 * @program: name
 * @line: to free
 * @st: int
 * Return: 1 on success
 */
int handle_path(char *input, char **args, char *program, char *line, int st)
{
	char *path = getenv("PATH"), *token;
	char *path_copy = strdup(path);
	static char status[20];

	if (st > 2)
		st = 2;
	snprintf(status, sizeof(status), "%d", st);
	if (access(input, X_OK) == 0)
	{
		free(path_copy);
		return (0);
	}
	token = _strtok(path_copy, ":");
	if (strcmp(input, "exit") == 0 && terminate(args, path_copy, line, program))
	{
		args[1] = strdup(status);
		args[2] = NULL;
		terminate(args, path_copy, line, program);
	}
	while (token != NULL)
	{
		char full_path[1024];

		snprintf(full_path, sizeof(full_path), "%s/%s", token, input);
		if (access(full_path, X_OK) == 0)
		{
			free(args[0]);
			args[0] = NULL;
			args[0] = strdup(full_path);
			free(path_copy);
			return (0);
		}

		token = _strtok(NULL, ":");
	}
	error_handle(path_copy, program, input, args);
	snprintf(status, sizeof(status), "2");
	return (2);
}


/**
 * token_input - function name
 * @input: string
 * @args: aray
 * @program: name
 * @line: to free
 * @st: int
 * Return: 1 on success
 */
int token_input(char input[], char **args, char *program, char *line, int st)
{
	char *token;
	int i = 0;

	token = _strtok(input, " ");
	while (token != NULL)
	{
		args[i] = strdup(token);
		token = _strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	return (handle_path(args[0], args, program, line, st));
}


/**
 * child_process - function
 * @args: the input line
 * Return: 1
 * @line: to free
 * @line: to free
 */
int child_process(char **args, char *line)
{
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
	if (args[1] != NULL && strcmp(args[1], "$?") == 0)
	{
		read_exit_status(args);
	}
	if (args[1] != NULL && strcmp(args[1], "$$") == 0)
	{
		pid_t pid = getpid();
		char pid_str[20];

		snprintf(pid_str, sizeof(pid_str), "%d", pid);
		args[1] = strdup(pid_str);
	}
	if (execve(args[0], args, NULL) == -1)
	{
		exit(EXIT_FAILURE);
	}
	return (0);
}
