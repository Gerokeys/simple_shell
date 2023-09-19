#include "shell.h"

/**
 * recurrent_data - frees the fields needed for each of the loop
 * @data: struct of the program's data
 * Return:  absolutely Nothing
 */
void recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_data - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing at all
 */
void free_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	recurrent_data(data);
	free_pointers(data->env);
	free_pointers(data->alias_list);
}

/**
 * free_pointers - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: absolutely nothing
 */
void free_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
