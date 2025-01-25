/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:41:16 by micchen           #+#    #+#             */
/*   Updated: 2023/11/08 23:07:29 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(unsigned long long *ptr)
{
	unsigned long	ulptr;

	ulptr = (unsigned long)ptr;
	if (!ulptr)
		return (ft_putstr("(nil)"));
	ft_putstr("0x");
	return (ft_puthex(ulptr, 1) + 2);
}

int	countunbr(unsigned int n)
{
	int		i;

	i = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}
