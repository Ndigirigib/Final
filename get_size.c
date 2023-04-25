#include "main.h"

/**
 * get_size - Calculates the size to cast.
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int temp = *i + 1;
	int size = 0;

	if (format[temp] == 'l')
		size = S_LONG;
	else if (format[temp] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = temp - 1;
	else
		*i = temp;

	return (size);
}
