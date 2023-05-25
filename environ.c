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
	size_t name_len = _strlen(name);
	size_t value_len = _strlen(value);
	char *new;

	new = malloc(sizeof(char) * (name_len + value_len + 2));
	if (new == NULL)
		return (NULL);

	_strcpy(new, name);
	new[name_len] = '=';
	_strcpy(new + name_len + 1, value);

	return (new);
}

/**
 * set_env - stes new environment
 * @name: string name
 * @value: string value
 * @data: pointer to shell structure
 */
void set_env(char *name, char *value, sh_dt *data)
{
	int i, j;
	size_t env_size;
	char *var_env, *name_env, **new_env;

	for (i = 0; data->env[i] != NULL; i++)
	{
		var_env = _strdup(data->env[i]);
		name_env = strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(data->env[i]);
			data->env[i] = create_copy(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}
	env_size = (i + 2) * sizeof(char *);
	new_env = malloc(env_size);
	if (new_env == NULL)
		return;
	for (j = 0; j < i; j++)
		new_env[j] = data->env[j];

	data->env[i] = create_copy(name, value);
	data->env[i + 1] = NULL;

	free(data->env);
	data->env = new_env;
}

/**
 * handle_setenv - sets environment variable and creates a new one
 * @data: pointer to shell structure
 *
 * Return: 1 on success, 0 on failure
 */
int handle_setenv(sh_dt *data)
{
	char **args = data->args;

	if (args[1] == NULL || args[2] == NULL)
	{
		write(STDERR_FILENO, "Missing arguments for setenv\n", 29);
		/*get_err(data, -1);*/
		data->status = 2;
		return (1);
	}

	set_env(args[1], args[2], data);
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
	char *env_var, *env_name, **env_new;

	if (name == NULL)
	{
		get_err(data, -1);
		return (-1);
	}
	for (i = 0; env[i] != NULL; i++)
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
		get_err(data, -1);
		return (-1);
	}
	for (i = 0; env[i] != NULL; i++)
	{
		env_var = _strdup(env[i]);
		env_name = strtok(env_var, "=");
		if (_strcmp(env_name, name) != 0)
		{
			env_new[j] = env[i];
			j++;
		}
		else
			free(env[i]);
		free(env_var);
	}
	env_new[count_env] = NULL;
	free(env);
	data->env = env_new;
	return (1);
}
