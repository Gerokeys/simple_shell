#include "shell.h"
/**
 * main - initialize the variables of the program.
 * @argc: number of values received from the command line.
 * @argv: values received from the command line.
 * @env: number of values received f rom the command line.
 * Return: returns zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	inicialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;
	gidi(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype used in the function
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * inicialize_data - inicialize the struct with the info of the program
 * @data: pointer to the structure of the data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line prompt
 */
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_prints(data->program_name);
			_prints(": 0: Can't open ");
			_prints(argv[1]);
			_prints("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * gidi - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed on the screen
 * @data: its an infinite loop that shows the prompt on the screen
 */
void gidi(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = Getlines(data);

		if (error_code == EOF)
		{
			free_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			variables_expand(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* if a text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error_string(error_code, data);
			}
			recurrent_data(data);
		}
	}
}
