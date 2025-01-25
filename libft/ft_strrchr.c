/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:02:02 by micchen           #+#    #+#             */
/*   Updated: 2023/10/22 01:09:03 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int x)
{
	int		i;
	char	c;
	char	*r;

	i = 0;
	c = x;
	r = 0;
	while (s[i])
	{
		if (s[i] == c)
			r = (char *) &s[i];
		i++;
	}
	if (s[i] == c)
		r = (char *) &s[i];
	return (r);
}
