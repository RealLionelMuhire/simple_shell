#include "shell.h"

/**
 */
char *create_copy(char *name, char *value)
{
	int name_len = _strlen(name);
	int value_len = _strlen(value);
	char *new, *ptr;

	new = malloc(sizeof(char) * (name_len + value_len + 2));
	if(new == NULL)
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

	data-> env = env_new;

	return (1);
}
