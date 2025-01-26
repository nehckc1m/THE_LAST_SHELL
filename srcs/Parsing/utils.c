/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:22:14 by micchen           #+#    #+#             */
/*   Updated: 2025/01/19 18:22:30 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_quotes(char *prompt, int i)
{
	int	in_quotes;
	int	index;

	in_quotes = 0;
	index = 0;
	while (index < i)
	{
		if (prompt[index] == '\'' && in_quotes == 0)
			in_quotes = 1;
		else if (prompt[index] == '\'' && in_quotes == 1)
			in_quotes = 0;
		else if (prompt[index] == '"' && in_quotes == 0)
			in_quotes = 2;
		else if (prompt[index] == '"' && in_quotes == 2)
			in_quotes = 0;
		index++;
	}
	if (in_quotes == 0)
		return (0);
	else
		return (in_quotes);
}

int	has_quote(char *prompt, int j)
{
	int	in_quotes;

	in_quotes = 0;
	while (prompt[j])
	{
		if (prompt[j] == '\'' && in_quotes != 2)
		{
			if (in_quotes == 1)
				in_quotes = 0;
			else
				in_quotes = 1;
			return (j);
		}
		else if (prompt[j] == '\"' && in_quotes != 1)
		{
			if (in_quotes == 2)
				in_quotes = 0;
			else
				in_quotes = 2;
			return (j);
		}
		j++;
	}
	return (j);
}

char	*get_env_value(char **env, char *var)
{
	char	*value;
	char	*tmp;
	int		i;

	value = NULL;
	i = 0;
	while (env[i])
	{
		tmp = ft_strndup(env[i], ft_strchr(env[i], '=') - env[i]);
		if (!tmp)
			return (NULL);
		if (ft_strcmp(var, tmp) == 0)
		{
			free(tmp);
			value = ft_strdup(ft_strchr(env[i], '=') + 1);
			if (!value)
				return (NULL);
			return (value);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

int	alloc_size(char *str, t_env *env)
{
	int		i;
	int		size;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_in_quotes(str, i) != 1)
		{
			if (str[i + 1] == '?' && is_in_quotes(str, i) != 1)
				search_exit_status_alloc(env, &i, &size);
			else
				ft_expand_alloc(env, &i, &size, str);
		}
		else
			size++;
		i++;
	}
	return (size);
}

char	*handle_expand(char *prompt, t_env *env)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	res = malloc(sizeof(char) * alloc_size(prompt, env) + 1);
	ft_memset(res, '\0', alloc_size(prompt, env) + 1);
	while (prompt[i])
		if_expand(&res, prompt, &i, env);
	return (res);
}
