#include "main.h"

/* Function to print pointer */
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: list of arguments
 * @buffer: buffer array
 * @flags: active flags
 * @width: width
 * @precision: precision
 * @size: size
 * Return: Number of printed characters
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int index = BUFF_SIZE - 2, len = 2, padd_start = 1; /* len=2, for '0x' */
	unsigned long num_address;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_address = (unsigned long)address;

	while (num_address > 0)
	{
		buffer[index--] = map_to[num_address % 16];
		num_address /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', len++;
	else if (flags & F_SPACE)
		extra_c = ' ', len++;

	index++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, index, len,
		width, flags, padd, extra_c, padd_start));
}

/* Function to print non printables */
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: list of arguments
 * @buffer: buffer array
 * @flags: active flags
 * @width: get width
 * @precision: precision
 * @size: size
 * Return: Number of printed characters
*/

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int index = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[index] != '\0')
	{
		if (is_printable(str[index]))
			buffer[index + offset] = str[index];
		else
			offset += append_hexa_code(str[index], buffer, index + offset);

		index++;
	}

	buffer[index + offset] = '\0';

	return (write(1, buffer, index + offset));
}

/*Function to print a reversed string*/
/**
 * print_reverse - Prints reverse string.
 * @types: list of arguments
 * @buffer: buffer array
 * @flags: active flags
 * @width: get width
 * @precision: precision
 * @size: size
 * Return: Number of printed characters
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, temp = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		temp++;
	}
	return (temp);
}

/* Function to print a string in rot13 */

/**
 * print_rot13string - Print a string in rot13.
 * @types: list of arguments
 * @buffer: buffer array
 * @flags: active flags
 * @width: get width
 * @precision: precision
 * @size: size
 * Return: Number of printed characters
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int temp = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				temp++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			temp++;
		}
	}
	return (temp);
}
