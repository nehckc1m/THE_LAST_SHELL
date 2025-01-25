/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:27:43 by micchen           #+#    #+#             */
/*   Updated: 2025/01/23 01:27:54 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_payload_quotes(char *option)
{
	int	i;
	int	state;

	state = 0;
	i = 0;
	while (option[i])
	{
		state = is_in_quotes(option, i);
		if ((option[i] == '\"' && state != 1)
			|| (option[i] == '\'' && state != 2))
			shift_str((option + i), 1);
		else if (i < (int)ft_strlen(option))
			i++;
	}
}

void	shift_str(char *str, int length)
{
	int	i;

	i = 0;
	while (str[i + length])
	{
		str[i] = str[i + length];
		i++;
	}
	str[i] = '\0';
}
