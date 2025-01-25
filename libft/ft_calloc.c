/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 23:09:09 by micchen           #+#    #+#             */
/*   Updated: 2023/10/23 23:24:53 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t s)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	tmp = malloc(count * s);
	if (!tmp)
		return (NULL);
	while (i < count * s)
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}
