/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:04:11 by manorteg          #+#    #+#             */
/*   Updated: 2024/10/26 22:29:21 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	invalid_base(char *base)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (base[i])
	{
		j = 0;
		count = 0;
		while (base[j])
		{
			if (base[i] == base[j])
				count++;
			j++;
		}
		if (base[i] == '+' || base[i] == '-' || count > 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_putnbr_base_recursive(long unsigned int num, char *base,
									int lenght, int *chars)
{
	if (num >= (long unsigned int)lenght)
		ft_putnbr_base_recursive(num / lenght, base, lenght, chars);
	write(1, &(char){base[num % lenght]}, 1);
	(*chars)++;
}

int	ft_putnbr_base(long num, char *base)
{
	int		base_lenght;
	int		chars;

	base_lenght = ft_strlen(base);
	chars = 0;
	if (base_lenght <= 1 || invalid_base(base) == 1)
		return (0);
	if (num < 0)
	{
		write(1, "-", 1);
		chars++;
		num *= -1;
	}
	if (num >= base_lenght)
		ft_putnbr_base_recursive(num / base_lenght, base, base_lenght, &chars);
	write(1, &(char){base[num % base_lenght]}, 1);
	chars++;
	return (chars);
}

int	ft_putptr_base(long unsigned int num, char *base)
{
	int		base_lenght;
	int		chars;

	base_lenght = ft_strlen(base);
	chars = 0;
	if (base_lenght <= 1 || invalid_base(base) == 1)
		return (0);
	if (num < 0)
	{
		write(1, "-", 1);
		chars++;
		num *= -1;
	}
	if (num >= (long unsigned int)base_lenght)
		ft_putnbr_base_recursive(num / base_lenght, base, base_lenght, &chars);
	write(1, &(char){base[num % base_lenght]}, 1);
	chars++;
	return (chars);
}
