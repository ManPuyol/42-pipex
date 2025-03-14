/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:05:32 by manorteg          #+#    #+#             */
/*   Updated: 2024/10/26 22:26:47 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_digits(long long n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	print_format(char sentence, va_list args)
{
	int	printed_chars;

	printed_chars = 0;
	if (sentence == 'c')
		return (print_char(args));
	if (sentence == 's')
		return (print_string(args));
	if (sentence == 'p')
		return (print_pointer(args));
	if (sentence == 'd' || sentence == 'i')
		return (print_nbr(args, "0123456789"));
	if (sentence == 'u')
		return (print_unsisgned_nbr(args, "0123456789"));
	if (sentence == 'x')
		return (print_unsisgned_nbr(args, "0123456789abcdef"));
	if (sentence == 'X')
		return (print_unsisgned_nbr(args, "0123456789ABCDEF"));
	if (sentence == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	return (printed_chars);
}

int	ft_vprintf(char const *sentence, va_list args)
{
	int	printed_chars;

	printed_chars = 0;
	while (*sentence)
	{
		if (*sentence == '%')
		{
			sentence++;
			printed_chars += print_format(*sentence, args);
		}
		else
		{
			ft_putchar_fd(*sentence, 1);
			printed_chars++;
		}
		sentence++;
	}
	return (printed_chars);
}

int	ft_printf(char const *sentence, ...)
{
	va_list	args;
	int		printed_chars;

	va_start(args, sentence);
	printed_chars = ft_vprintf(sentence, args);
	va_end(args);
	return (printed_chars);
}

// int main()
// {
//     char c = 'A';
//     char *s = "Hello, World!";
//     void *p = (void *)0x12345678;
//     int d = -42;
//     int i = 033;
//     unsigned int u = 3000000000;
//     int x = -1;
//     int X = 0xABCDEF;

//     // Testing each format specifier
//     printf("Standard printf:\n");
//     printf("%%c: %c\n", c);
//     printf("%%s: %s\n", s);
//     printf("%%p: %p\n", p);
//     printf("%%d: %d\n", d);
//     printf("%%i: %i\n", i);
//     printf("%%u: %u\n", u);
//     printf("%%x: %x\n", x);
//     printf("%%X: %X\n", X);
//     printf("%%%%: %%\n");
// 	printf(" %p %p ", LONG_MIN, LONG_MAX);
// 	printf(" %p %p ", ULONG_MAX, -ULONG_MAX);
//     printf("\nYour ft_printf:\n");
//     ft_printf("%%c: %c\n", c);
//     ft_printf("%%s: %s\n", s);
//     ft_printf("%%p: %p\n", p);
//     ft_printf("%%d: %d\n", d);
//     ft_printf("%%i: %i\n", i);
//     ft_printf("%%u: %u\n", u);
//     ft_printf("%%x: %x\n", x);
//     ft_printf("%%X: %X\n", X);
//     ft_printf("%%%%: %%\n");
// 	ft_printf(" %p %p ", LONG_MIN, LONG_MAX);
// 	ft_printf(" %p %p ", ULONG_MAX, -ULONG_MAX);
//     // Testing edge cases
//     printf("\nTesting edge cases:\n");
//     printf("Standard printf:\n");
//     printf("NULL string: %s\n", NULL);
//     printf("INT_MAX: %d\n", INT_MAX);
//     printf("INT_MIN: %d\n", INT_MIN);
//     printf("UINT_MAX: %u\n", UINT_MAX);

//     printf("\nYour ft_printf:\n");
//     ft_printf("NULL string: %s\n", NULL);
//     ft_printf("INT_MAX: %d\n", INT_MAX);
//     ft_printf("INT_MIN: %d\n", INT_MIN);
//     ft_printf("UINT_MAX: %u\n", UINT_MAX);

//     return (0);
// }