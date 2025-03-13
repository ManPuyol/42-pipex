/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:03:40 by manorteg          #+#    #+#             */
/*   Updated: 2024/09/23 20:03:40 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb * size > INT_MAX)
		return ('\0');
	ptr = malloc(nmemb * size);
	if (!ptr)
		return ('\0');
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
