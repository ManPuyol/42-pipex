/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 08:19:41 by manorteg          #+#    #+#             */
/*   Updated: 2024/09/28 08:19:41 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	k = ft_strlen(s1);
	while (k > i && ft_strchr(set, s1[k - 1]))
		k--;
	str = (char *)malloc(k - i + 1);
	if (!str)
		return (NULL);
	while (i < k)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
