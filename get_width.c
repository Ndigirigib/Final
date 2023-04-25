#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int temp;
	int width = 0;

	for (temp = *i + 1; format[temp] != '\0'; temp++)
	{
		if (is_digit(format[temp]))
		{
			width *= 10;
			width += format[temp] - '0';
		}
		else if (format[temp] == '*')
		{
			temp++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = temp - 1;

	return (width);
}
