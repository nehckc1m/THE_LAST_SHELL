/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:58:43 by micchen           #+#    #+#             */
/*   Updated: 2023/10/20 22:04:11 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmps;
	char	*tmpd;

	if (dst == 0 && src == 0)
		return (0);
	tmpd = (char *) dst;
	tmps = (char *) src;
	if (tmps < tmpd && tmps + len > tmpd)
	{
		tmps += len;
		tmpd += len;
		while (len > 0)
		{
			*(--tmpd) = *(--tmps);
			len--;
		}
	}
	else
	{
		while (len-- > 0)
		{
			*(tmpd++) = *(tmps++);
		}
	}
	return (dst);
}
