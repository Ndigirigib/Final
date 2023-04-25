#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int temp = *i + 1;
	int precision = -1;

	if (format[temp] != '.')
		return (precision);

	precision = 0;

	for (temp += 1; format[temp] != '\0'; temp++)
	{
		if (is_digit(format[temp]))
		{
			precision *= 10;
			precision += format[temp] - '0';
		}
		else if (format[temp] == '*')
		{
			temp++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = temp - 1;

	return (precision);
}
