#include "shell.h"

/*This file contains all memory managemens functions*/

/**
 * *_memset - fills first byte of memory area pointed to by s with const byte b
 * @s: final destination of the memory
 * @b: initial locationof the memory
 * @n: size of memory to be set
 * Return: s when success
 */

void *_memset(void *s, char b, size_t n)
{
	unsigned char *ptr = s;
	size_t i;

	for (i = 0; i < n; i++)
	{
		ptr[i] = (unsigned char)b;
	}
	return (ptr);
}


/**
 * *_memcpy - copy the data from src to dest,with size of n
 * @dest: final destination of data
 * @src: the source of data
 * @n: size of data to be copied
 * Return: always dest at success
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i = 0;

	for (; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

/**
 * *_realloc - reallocate the memory
 * @ptr: the ptr that is initially allocated
 * @new_size: size of new reallocated memory
 * @old_size: size of pre allocated memory
 * Return: new_ptr at success, ptr when both sizes are eqaul, otherwise NULL
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		return (new_ptr);
	}

	if (new_size == old_size)
	{
		return (ptr);
	}

	new_ptr = malloc(new_size);

	if (new_ptr != NULL)
	{
		_memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
		free(ptr);
	}
	return (new_ptr);


}

/**
 * free_d - frees all the data in the struct
 * @data: struct contains the data
 * Return: 0 at sucess
 */

int free_d(sh_dt *data)
{
	int i = 0;

	for (; data->env[i]; i++)
	{
		free(data->env[i]);
	}
	free(data->env);
	free(data->pid);

	return (0);
}

/**
 * free_lv - frees linked list of variables
 * @head: head node;
 */

void free_lv(l_v **head)
{
	l_v *tmp;
	l_v *current;

	if (!head)
	{
		current = *head;
		while ((tmp = current))
		{
			current = current->next;
			free(tmp);
		}
		*head = NULL;
	}
}
