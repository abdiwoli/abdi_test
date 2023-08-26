#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
extern char **environ;
int is_empty_spaces(char *str);
int important(char **args, char *line, int status, int handle);
void other_error(char **args, char *program);
void status_writer(int number);
int all_digits(char *);
void memory(char **, char *);
void print_number(int n);
void exit_status(int);
void read_exit_status(char **);
int _getline(char **, int *, FILE *);
int _putchar(char c);
void _puts(char *);
void inter_active_mode(char *);
char *get_file_name(char *input);
int handle_path(char *input, char **, char *, char *, int);
int token_input(char input[], char **args, char *, char *, int);
int child_process(char **args, char *);
void non_inter_active_mode(char *);
char *_strtok(char *str, const char *delimiters);
void _getenv(void);
int process(char *tken, int handle, char **args, char *cd, char *);
void commentAfterHash(char str[]);
int Main(void);
#endif
