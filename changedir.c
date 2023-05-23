#include "shell.h"

/**
 * cd_to_cd - change directory to the current directory
 * @data: data shell structure
 */
void cd_to_cd(sh_dt *data)
{
	char wd[PATH_MAX];
	char *dir, *cp_wd, *cp_to_wd;

	getcwd(wd, sizeof(wd));
	cp_wd = _strdup(wd);
	set_env("OLDPWD", cp_wd, data);

	dir = data->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_wd, data);
		free(cp_wd);
		return;
	}
	if (_strcmp("/", cp_wd) == 0)
	{
		free(cp_wd);
		return;
	}
	cp_to_wd = cp_wd;
	arr_rev(cp_to_wd, _strlen(cp_to_wd));
	cp_to_wd = strtok(cp_to_wd, "/");
	if (cp_to_wd != NULL)
	{
		cp_to_wd = strtok(NULL, "\0");
		if (cp_to_wd != NULL)
			arr_rev(cp_to_wd, _strlen(cp_to_wd));
	}
	if (cp_to_wd != NULL)
	{
		chdir(cp_to_wd);
		set_env("PWD", cp_to_wd, data);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data);
	}
	data->status = 0;
	free(cp_wd);
}

/**
 * cd_to_sd - change directory to specified directory
 * @data: data shell structure
 */
void cd_to_sd(sh_dt *data)
{
	char *hom_dir, *prev_dir, error[PATH_MAX + 20];
	char *wd = NULL, *oldwd = NULL, *dir = data->args[1];

	if (dir == NULL)
	{
		hom_dir = get_env("HOME", data->env);
		if (hom_dir == NULL)
		{
			PRINT_ERR("cd: $HOME not set\n");
			return;
		}
		dir = hom_dir;
	}
	else if (_strcmp(dir, "-") == 0)
	{
		prev_dir = get_env("OLDPWD", data->env);
		if (prev_dir == NULL)
		{
			PRINT_ERR("cd: OLDPWD not set\n");
			return;
		}
		dir = prev_dir;
	}
	wd = getcwd(NULL, 0);
	if (wd == NULL)
	{
		perror("cd");
		free(wd);
		return;
	}
	if (chdir(dir) == -1)
	{
		_sprintf(error, "cd: %s: No such file or directory\n", dir);
		PRINT_ERR(error);
		free(oldwd);
		free(wd);
		return;
	}
	set_env("OLDPWD", oldwd, data);
	set_env("PWD", getcwd(NULL, 0), data);
	free(oldwd);
	free(wd);
	data->status = 0;
}

/**
 * cd_to_pd - change directory to previous directory
 * @data: data shell structure
 */
void cd_to_pd(sh_dt *data)
{
	char *wd = getcwd(NULL, 0), *oldwd = get_env("OLDPWD", data->env);
	char error[PATH_MAX + 20];

	if (oldwd == NULL)
	{
		PRINT_ERR("cd: OLDPWD not set\n");
		free(wd);
		return;
	}
	if (chdir(oldwd) == -1)
	{
		_sprintf(error, "cd: %s: No such file or directory\n", oldwd);
		PRINT_ERR(error);
		free(oldwd);
		free(wd);
		return;
	}
	set_env("OLDPWD", wd, data);
	set_env("PWD", getcwd(NULL, 0), data);
	free(oldwd);
	free(wd);
	data->status = 0;
}

/**
 * cd_to_home - changes directory to home directory
 * @data: data shell structure
 */
void cd_to_home(sh_dt *data)
{
	char error[PATH_MAX + 20];
	char *wd = getcwd(NULL, 0), *hom_dir = get_env("HOME", data->env);

	if (hom_dir == NULL)
	{
		PRINT_ERR("cd: $HOME not set\n");
		free(wd);
		return;
	}
	if (chdir(hom_dir) == -1)
	{
		_sprintf(error, "cd: %s: No such file or directory\n", hom_dir);
		PRINT_ERR(error);
		free(wd);
		return;
	}
	set_env("OLDPWD", wd, data);
	set_env("PWD", getcwd(NULL, 0), data);

	free(wd);
	data->status = 0;
}

/**
 * change_dir - handles teh cd command
 * @data: data shell structure
 *
 * Return: 1 on success
 */
int change_dir(sh_dt *data)
{
	char *wd = data->args[1];

	if (wd == NULL || _strcmp(wd, ".") == 0 || _strcmp(wd, "..") == 0
			|| _strcmp(wd, "~") == 0)
	{
		cd_to_cd(data);
	}
	else if (_strcmp(wd, "-") == 0 || _strcmp(wd, "~") == 0)
	{
		cd_to_pd(data);
	}
	else
	{
		cd_to_sd(data);
	}
	return (1);
}
