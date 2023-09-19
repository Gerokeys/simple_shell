#include "shell.h"

/**
 * _print - writes an array of chars in the standard output of the file
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, negative one is returned, and errno is set appropriately.
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}
/**
 * _prints - writes an  array of the chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _prints(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * _print_error_string - writes a array of chars in the standard error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print_error_string(int errorcode, data_of_program *data)
{
	char n_as_string[10] = {'\0'};

	number_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_prints(data->program_name);
		_prints(": ");
		_prints(n_as_string);
		_prints(": ");
		_prints(data->tokens[0]);
		if (errorcode == 2)
			_prints(": Illegal number: ");
		else
			_prints(": can't cd to ");
		_prints(data->tokens[1]);
		_prints("\n");
	}
	else if (errorcode == 127)
	{
		_prints(data->program_name);
		_prints(": ");
		_prints(n_as_string);
		_prints(": ");
		_prints(data->command_name);
		_prints(": not found\n");
	}
	else if (errorcode == 126)
	{
		_prints(data->program_name);
		_prints(": ");
		_prints(n_as_string);
		_prints(": ");
		_prints(data->command_name);
		_prints(": Permission denied\n");
	}
	return (0);
}
