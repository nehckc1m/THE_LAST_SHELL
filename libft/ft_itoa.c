/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 01:54:16 by micchen           #+#    #+#             */
/*   Updated: 2023/10/30 18:12:13 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static int	lenght(long nbr);

static char	*tab(int len)
{
	char	*m;

	m = ft_calloc(len, sizeof(char));
	if (!m)
		return (NULL);
	m[0] = '0';
	return (m);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;
	long	nbr;

	nbr = n;
	len = lenght(nbr);
	result = tab(len + 1);
	if (!result)
		return (NULL);
	result[len] = 0;
	if (nbr < 0)
		nbr = -nbr;
	len = len - 1;
	while (nbr != 0)
	{
		result[len--] = ((nbr % 10) + 48);
		nbr = nbr / 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}

static int	lenght(long nbr)
{
	int		cpt;

	cpt = 0;
	if (nbr < 0)
	{
		cpt++;
		nbr = -nbr;
	}
	if (nbr == 0)
		cpt++;
	while (nbr > 0)
	{
		nbr = nbr / 10;
		cpt++;
	}
	return (cpt);
}
