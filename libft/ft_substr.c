/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:55:14 by micchen           #+#    #+#             */
/*   Updated: 2023/10/25 23:01:19 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int debut, size_t n)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (debut > ft_strlen(s))
		return (ft_strdup(""));
	if (n > ft_strlen (s + debut))
		n = ft_strlen(s + debut);
	str = ft_calloc(n + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s[debut + i];
		i++;
	}
	return (str);
}
