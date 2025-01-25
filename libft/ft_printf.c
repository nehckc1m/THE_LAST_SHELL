/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:10:11 by micchen           #+#    #+#             */
/*   Updated: 2023/11/14 19:19:09 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdio.h>

int	ft_putchar(int c)
{
	write (1, &c, 1);
	return (1);
}

int	countnbr(int n)
{
	int		i;

	i = 0;
	if (!n)
		return (1);
	if (n == -2147483648)
		i += 10;
	if (n <= 0)
	{
		n *= -1;
		++i;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	print_format(va_list *pf, char c)
{
	int		count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(*pf, int));
	else if (c == 's')
		count += ft_putstr(va_arg(*pf, char *));
	else if (c == 'p')
		count += ft_putptr(va_arg(*pf, void *));
	else if (c == 'd')
		count += ft_putnbr(va_arg(*pf, int));
	else if (c == 'i')
		count += ft_putnbr(va_arg(*pf, int));
	else if (c == 'u')
		count += putunbr(va_arg(*pf, unsigned int));
	else if (c == 'x')
		count += ft_puthex(va_arg(*pf, unsigned int), 1);
	else if (c == 'X')
		count += ft_puthex(va_arg(*pf, unsigned int), 0);
	else if (c == '%')
		count += ft_putchar('%');
	return (count);
}

static int	aff(const char *str, va_list *pf)
{
	size_t		i;
	int			len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += print_format(pf, str[i + 1]);
			i += 2;
		}
		else
		{
			i += ft_putchar(str[i]);
			len++;
		}
	}
	return (len);
}

int	ft_printf(char const *str, ...)
{
	va_list		pf;
	int			len;

	va_start(pf, str);
	len = aff(str, &pf);
	va_end(pf);
	return (len);
}
