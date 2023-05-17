#include "shell.h"

/**
 * free_l_sep - free list of sep linked list
 * @h: head of linked list
 */

void free_l_sep(l_sep **h)
{
	l_sep *c = *h, *tmp;

	while (c)
	{
		tmp = c;
		c = c->next;
		free(tmp);
	}

	*h = NULL;
}

/**
 * free_cmd_st - free linked list of command store
 * @h: head of linked list
 */
void free_cmd_st(cmd_st **h)
{
	cmd_st *c = *h, *tmp;

	while (c)
	{
		tmp = c;
		c = c->next;
		free(tmp);
	}

	*h = NULL;
}

/**
 * *_dp_realloc - reallocate the memory in a double pointer
 * @ptr: the ptr that is initially allocated
 * @old_size: size of pre-allocated memory
 * @new_size: size of new reallocated memory
 * Return: new_ptr at success, ptr when both sizes are equal, otherwise NULL
 */
void *_dp_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
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

	if (new_size > old_size)
	{
		void **double_ptr = (void **)ptr;
		*double_ptr = realloc(*double_ptr, new_size);
		new_ptr = *double_ptr;
	}
	else
	{
		new_ptr = malloc(new_size);
		if (new_ptr != NULL)
		{
			_memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
			free(ptr);
		}
	}

	return (new_ptr);
}
