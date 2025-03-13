/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:12:38 by manorteg          #+#    #+#             */
/*   Updated: 2024/09/21 23:12:38 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	length;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	if (size <= i)
		return (ft_strlen(src) + size);
	else
		length = ft_strlen(dest) + ft_strlen(src);
	while (src[j] && j < size - 1 && i < size - 1)
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (length);
}
