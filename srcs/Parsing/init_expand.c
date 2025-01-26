/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:25:42 by micchen           #+#    #+#             */
/*   Updated: 2025/01/26 16:25:52 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strcat_char(char *dest, char c)
{
	int	len;

	len = ft_strlen(dest);
	dest[len] = c;
	dest[len + 1] = '\0';
	return (dest);
}

void	if_word(char **res, int *i, char *word, t_env *env)
{
	char	*env_var_value;

	env_var_value = get_env_value(env->env, word);
	if (env_var_value)
	{
		*res = ft_strcat(*res, env_var_value);
		*i += ft_strlen(word);
		free(env_var_value);
	}
	else
		*i += ft_strlen(word);
	free(word);
}

void	if_expand(char **res, char *prompt, int *i, t_env *env)
{
	char	*word;

	if (prompt[*i] == '$' && is_in_quotes(prompt, *i) != 1)
	{
		if (prompt[*i + 1] == '?' && is_in_quotes(prompt, *i) != 1)
			search_exit_status(env, i, res);
		else
		{
			word = extract_word(&prompt[*i + 1]);
			if (word)
				if_word(res, i, word, env);
		}
	}
	else
		*res = ft_strcat_char(*res, prompt[*i]);
	if (!*res)
		return ;
	(*i)++;
}
