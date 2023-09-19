#include "shell.h"

/**
 * variables_expand - expand the   variables
 * @data: a pointer to a struct ofhe program's data
 *
 * Return: nothing, but sets errno.
 */
void variables_expand(data_of_program *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	add_buffer(line, data->input_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			number_to_string(errno, expansion, 10);
			add_buffer(line, expansion);
			add_buffer(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			number_to_string(getpid(), expansion, 10);
			add_buffer(line, expansion);
			add_buffer(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = env_get_keys(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			add_buffer(expansion, line + i + j);
			temp ? add_buffer(line, temp) : 1;
			add_buffer(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - expanss aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errnor.
 */
void expand_alias(data_of_program *data)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	add_buffer(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			add_buffer(expansion, line + i + j);
			line[i] = '\0';
			add_buffer(line, temp);
			line[str_length(line)] = '\0';
			add_buffer(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * add_buffer - append string at end of the buffer
 * @buffer: buffer that is supposed to be filled
 * @str_to_add: string to be copied into the buffer
 * Return: nothing, but sets errno.
 */
int add_buffer(char *buffer, char *str_to_add)
{
	int length, i;

	length = str_length(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
