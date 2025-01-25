/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:56:31 by micchen           #+#    #+#             */
/*   Updated: 2025/01/25 01:56:41 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_exit_status_alloc(t_env *env, int *i, int *j)
{
	char	*value;

	if (g_exit_status > 0)
	{
		value = ft_itoa(g_exit_status);
		*j += ft_strlen(value);
		*i += 2;
		free(value);
	}
	else
	{
		value = ft_itoa(env->last_status);
		*j += ft_strlen(value);
		*i += 2;
		free(value);
	}
}

void	search_exit_status(t_env *env, int *i, int *j, char **res)
{
	char	*value;

	if (g_exit_status > 0)
	{
		value = ft_itoa(g_exit_status);
		*res = ft_strcat(*res, value);
		*j += ft_strlen(value);
		*i += 2;
		g_exit_status = 0;
		free(value);
	}
	else
	{
		value = ft_itoa(env->last_status);
		*res = ft_strcat(*res, value);
		*j += ft_strlen(value);
		*i += 2;
		free(value);
	}
}
/*void	ft_expand(char **res, char **env_var_value, int *i, int *j)
{
	if (env_var_value)
	{
		*res = ft_strcat(*res, env_var_value);
		*j += ft_strlen(env_var_value);
		*i += ft_strlen(word);
		free(env_var_value);
	}
	else
		*i += ft_strlen(word);
	free(word);
}*/

void	ft_expand_alloc(t_env *env, int *i, int *size, char *str)
{
	char	*word;
	char	*env_var_value;

	word = extract_word(&str[*i + 1]);
	if (word)
	{
		env_var_value = get_env_value(env->env, word);
		if (env_var_value)
		{
			*i += ft_strlen(word);
			*size += ft_strlen(env_var_value);
			free(env_var_value);
		}
		else
			*i += ft_strlen(word);
		free(word);
	}
	else
		(*size)++;
}
