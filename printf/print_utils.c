/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:07:02 by manorteg          #+#    #+#             */
/*   Updated: 2025/03/14 16:21:44 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (str == NULL)
		str = "(null)";
	ft_putstr_fd(str, 2);
	return (ft_strlen(str));
}

int	print_char(va_list args)
{
	char	str;

	str = va_arg(args, int);
	ft_putchar_fd(str, 2);
	return (1);
}

int	print_nbr(va_list args, char *base)
{
	int	nbr;

	nbr = va_arg(args, int);
	return (ft_putnbr_base(nbr, base));
}

int	print_unsisgned_nbr(va_list args, char *base)
{
	unsigned int	nbr;

	nbr = va_arg(args, unsigned int);
	return (ft_putnbr_base(nbr, base));
}

int	print_pointer(va_list args)
{
	unsigned long long	pointer;

	pointer = va_arg(args, unsigned long long);
	if (pointer == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	return (ft_putptr_base(pointer, "0123456789abcdef") + 2);
}
