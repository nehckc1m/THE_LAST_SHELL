/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 01:41:11 by micchen           #+#    #+#             */
/*   Updated: 2023/10/29 19:36:09 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count(const char *str, char c)
{
	size_t	i;
	size_t	count;
	int		word;

	word = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c && word == 0)
		{
			word = 1;
			count++;
		}
		else if (str[i] == c)
			word = 0;
		i++;
	}
	return (count + 1);
}

static char	*fill(const char *s, int start, int end)
{
	char	*tab;
	int		i;

	i = 0;
	tab = ft_calloc((end - start + 1), sizeof(char));
	if (!tab)
		return (NULL);
	while (start < end)
		tab[i++] = s[start++];
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	size_t	j;
	size_t	i;
	int		index;

	i = 0;
	j = 0;
	index = -1;
	split = ft_calloc((count(s, c)), sizeof (char *));
	if (!split || !s)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = fill(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
