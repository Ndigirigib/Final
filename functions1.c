#include "main.h"

/**Function to print an unsigned number**/
/**
 * print_unsigned - Prints unsigned number.
 * @types: list of arguments
 * @buffer: buffer array
 * @flags: active flags
 * @width: get width
 * @precision: precision
 * @size: size
 * Return: Number of printed characters
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = (number % 10) + '0';
		number /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**Function to print unsigned number in octal**/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: list of arguments
 * @buffer: buffer array
 * @flags: active flags
 * @width: get width
 * @precision: precision
 * @size: size
 * Return: Number of printed characters
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_num = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = (number % 8) + '0';
		number /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**Function to print an unsigned number in hexadecimal**/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 *  @types: list of arguments
 * @buffer: buffer array
 * @flags: active flags
 * @width: get width
 * @precision: precision
 * @size: size
 * Return: Number of printed characters
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**Function to print number in unsigned upper hexadecimal**/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 *  @types: list of arguments
 * @buffer: buffer array
 * @flags: active flags
 * @width: get width
 * @precision: precision
 * @size: size
 * Return: Number of printed characters
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**Funtion to print hexadecimal number in lower or upper**/
/**
 * print_hexa - to print hexadecimal number in lower or upper.
 * @types: list of arguments
 * @map_to: an array of values to map number to.
 * @buffer: buffer array
 * @flags: active flags
 * @flag_ch: finds active flags.
 * @width: get width
 * @precision: precision
 * @size: size
 * Return: Number of printed character.
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_num = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = map_to[number % 16];
		number /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
