/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 08:36:30 by manorteg          #+#    #+#             */
/*   Updated: 2024/09/28 08:36:30 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>*/

size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

char	*get_next_word(const char **s, char c)
{
	const char	*word_start;
	size_t		len;

	while (**s == c)
		(*s)++;
	word_start = *s;
	while (**s && **s != c)
		(*s)++;
	len = *s - word_start;
	return (ft_substr(word_start, 0, len));
}

void	free_all(char **result, size_t i)
{
	while (i--)
		free(result[i]);
	free(result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		result[i] = get_next_word(&s, c);
		if (!result[i])
			return (free_all(result, i), NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}
/*
int main ()
{
	char **result;
	char *str = ",,,,,,,,,,,,,,,,,,,,,,,,";

	result = ft_split(str, ',');
	if (result == NULL)
		return (0);

	while (*result)
	{
		printf("%s\n", *result);
		result++;
	}
 	return (0);	
}
*/