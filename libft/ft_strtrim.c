/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 00:02:17 by micchen           #+#    #+#             */
/*   Updated: 2023/10/29 19:37:04 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trimer(char c, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1);
	if (!s1)
		return (NULL);
	if (!set)
		return (NULL);
	while (trimer(s1[i], set) == 0)
		i++;
	while (trimer (s1[j - 1], set) == 0)
		j--;
	return (ft_substr(s1, i, j - i));
}

static int	trimer(char c, const char *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}
