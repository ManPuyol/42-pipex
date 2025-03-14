/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:03:51 by manorteg          #+#    #+#             */
/*   Updated: 2024/10/19 20:03:51 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <aio.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/libft.h"

int		ft_printf(char const *sentence, ...);
int		ft_putnbr_base(long num, char *base);
int		ft_putptr_base(long unsigned int num, char *base);

int		count_digits(long long n);

int		print_pointer(va_list args);
int		print_unsisgned_nbr(va_list args, char *base);
int		print_nbr(va_list args, char *base);
int		print_char(va_list args);
int		print_string(va_list args);

// temp
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

#endif