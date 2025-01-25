/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:50:23 by micchen           #+#    #+#             */
/*   Updated: 2023/11/15 16:10:38 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int		i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return ((int)ft_strlen(str));
}

int	ft_putnbr(int n)
{
	ft_putnbr_fd(n, 1);
	return (countnbr(n));
}

int	ft_puthex(unsigned long n, int min)
{
	char	tmp;
	char	*base;
	int		count;

	count = 0;
	base = "0123456789ABCDEF";
	if (n >= 16)
	{
		count += ft_puthex(n / 16, min);
		count += ft_puthex(n % 16, min);
	}
	else
	{
		if (min)
		{
			tmp = ft_tolower(base[n]);
			write(1, &tmp, 1);
		}
		else
		{
			write(1, &base[n], 1);
		}
		count++;
	}
	return (count);
}

int	putunbr(unsigned int n)
{
	if (n < 10)
		ft_putchar(n + '0');
	if (n >= 10)
	{
		putunbr(n / 10);
		putunbr(n % 10);
	}
	return (countunbr(n));
}
