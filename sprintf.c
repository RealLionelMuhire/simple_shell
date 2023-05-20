#include "shell.h"



/**
 * write_str - write string in for sprintf
 * @buffer: buffer char
 * @str: strinfg to writen
 * @len: length of string
 * Return: number of written chars
 */
int write_str(char *buffer, const char *str, int len)
{
	int i;

	for (i = 0; i < len && str[i] != '\0'; i++)
		buffer[i] = str[i];
	return (i);
}

/**
 * write_int - Function to write an integer to the buffer *
 * @buffer: buffer
 * @num: integer to be written
 * Return: number of written number
 */
int write_int(char *buffer, int num)
{
	int i = 0;
	int remainder, j;
	int isNegative = 0;
	char temp;

	if (num == 0)
	{
		buffer[i++] = '0';
		return (i);
	}

	if (num < 0)
	{
		isNegative = 1;
		num = -num;
	}

	while (num > 0)
	{
		remainder = num % 10;
		buffer[i++] = '0' + remainder;
		num = num / 10;
	}

	if (isNegative)
		buffer[i++] = '-';

	/* Reverse the string */
	for (j = 0; j < i / 2; j++)
	{
		temp = buffer[j];
		buffer[j] = buffer[i - j - 1];
		buffer[i - j - 1] = temp;
	}

	return (i);
}


/**
 * _sprintf - Custom implementation of sprintf
 * @str: Buffer to store the formatted string
 * @format: Format string
 * Return: Number of characters written to the
 * --------buffer (excluding null terminator)
 */
int _sprintf(char *str, const char *format, ...)
{
	char *s;
	va_list args;
	int j = 0, n, len;

	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++; /* skip '%' */
			switch (*format)
			{
				case 's':
					s = va_arg(args, char *);
					len = 0;
					while (s[len] != '\0')
						len++;
					j += write_str(str + j, s, len);
				break;
				case 'd':
					n = va_arg(args, int);
					j += write_int(str + j, n);
				break;
				default:
				str[j++] = *format;
				break;
			}
		}
		else
		{
			str[j++] = *format;
		}
		format++;
		}
		va_end(args);
		str[j] = '\0'; /* null-terminate the string */
		return (j);
}

