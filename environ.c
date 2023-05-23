#include "shell.h"

/**
 * create_copy -  copies the name and value to a new string
 * @name: string name
 * @value: string value
 *
 * Return: pointer to newly string. NULL on failure
 */
char *create_copy(char *name, char *value)
{
	int name_len = _strlen(name);
	int value_len = _strlen(value);
	char *new, *ptr;

	new = malloc(sizeof(char) * (name_len + value_len + 2));
	if (new == NULL)
		return (NULL);

	ptr = new;
	while (*name)
		*ptr++ = *name++;

	*ptr++ = '=';
	while (*value)
		*ptr++ = *value++;

	*ptr = '\0';

	return (new);
}

/**
 * handle_setenv - sets environment variable and creates a new one
 * @data: pointer to shell structure
 *
 * Return: 1 on success, 0 on failure
 */
int handle_setenv(sh_dt *data)
{
	char *name = data->args[1];
	char *value = data->args[2];
	char **env = data->env;
	int i, count_env = i + 2;
	char *env_var, *env_name, **env_new;

	for (i = 0; env[i]; i++)
	{
		env_var = _strdup(env[i]);
		env_name = strtok(env_var, "=");
		if (_strcmp(env_name, name) == 0)
		{
			free(env[i]);
			env[i] = create_copy(env_name, value);
			free(env_var);
			return (1);
		}
		free(env_var);
	}

	env_new = _dp_realloc(env, i, sizeof(char *) * env_count);
	if (env_new == NULL)
		return (0);

	env_new[i] = create_copy(name, value);
	env_new[i + 1] = NULL;

	data->env = env_new;

	return (1);
}

/**
 * handle_unsetenv - deletes an environment varibale
 * @data: pointer to shell structure
 *
 * Return: 1 on success, -1 on failure
 */
int handle_unsetenv(sh_dt *data)
{
	char *name = data->args[1], **env = data->env;
	int i, j = 0, count_env = 0;
	char *env_var, env_name, **env_new;

	if (name == NULL)
	{
		get_erro(data, -1);
		return (-1);
	}
	for (i = 0; env[i]; i++)
	{
		env_var = _strdup(env[i]);
		env_name = strtok(env_var, "=");
		if (_strcmp(env_name, name) != 0)
			count_env++;
		free(env_var);
	}
	env_new = malloc(sizeof(char *) * (count_env + 1));
	if (env_new == NULL)
	{
		get_error(data, -1);
		return (1);
	}
	for (i = 0; env[i]; i++)
	{
		env_var = _strdup(env[i]);
		nv_name = strtok(env_var, "=");
		if (_strcmp(env_name, name) != 0)
		{
			env_new[j] = env[i];
			j++;
		}
		else
			free(env[i]);
		free(env_var);
	}
	env_new[j] = NULL;
	free(env);
	env = nev_new;
	return (1);
}

