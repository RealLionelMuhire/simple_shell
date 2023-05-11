#include "shell.h"
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
