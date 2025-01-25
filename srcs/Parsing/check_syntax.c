/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 00:07:00 by micchen           #+#    #+#             */
/*   Updated: 2025/01/18 00:12:03 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_space_between_pipes(char *prompt)
{
	int	i;
	int	j;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '|' && is_in_quotes(prompt, i) == 0)
		{
			j = i + 1;
			while (prompt[i] && ft_isspace(prompt[j]) == 1)
				j++;
			if (prompt[j] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_pipes(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && ft_isspace(prompt[i]) == 1)
		i++;
	if (prompt[i] == '\0')
		return (0);
	if (prompt[i] && prompt[i] == '|' && is_in_quotes(prompt, i) == 0)
		return (0);
	i = ft_strlen(prompt) - 1;
	while (prompt[i] && ft_isspace(prompt[i]) == 1)
		i--;
	if (prompt[i] && prompt[i] == '|' && is_in_quotes(prompt, i) == 0)
		return (0);
	return (1);
}

int	check_quotes(char *prompt)
{
	int			i;
	bool		opened_s_quote;
	bool		opened_d_quote;

	opened_s_quote = 0;
	opened_d_quote = 0;
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' && !opened_d_quote)
			opened_s_quote = !opened_s_quote;
		if (prompt[i] == '\"' && !opened_s_quote)
			opened_d_quote = !opened_d_quote;
		i++;
	}
	return (opened_s_quote || opened_d_quote);
}

int	check_syntax(char *prompt)
{
	if (check_pipes(prompt) == 0)
		return (1);
	if (check_space_between_pipes(prompt) == 0)
		return (1);
	if (check_quotes(prompt) == 1)
		return (1);
	return (0);
}
