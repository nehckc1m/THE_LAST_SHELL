/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 02:29:01 by micchen           #+#    #+#             */
/*   Updated: 2025/01/21 02:29:03 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirection	*get_redirection(char *cmd)
{
	t_redirection	*current;
	int				i;

	current = NULL;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
		{
			if (is_in_quotes(cmd, i) == 0)
			{
				current = redirection_list_add_back(current, \
						redirection_list_new_node());
				i += fill_redirection(current, &cmd[i]);
			}
			else
				i++;
		}
		if (cmd[i] && cmd[i] != '<' && cmd[i] != '>')
			i++;
	}
	return (current);
}

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

char	*remove_quotes(char *prompt)
{
	char	*res;
	int		i;
	int		j;
	int		in_quotes;

	j = 0;
	in_quotes = 0;
	res = malloc(sizeof(char) * (ft_strlen(prompt) + 1));
	i = -1;
	while (prompt[++i])
	{
		if ((prompt[i] == '\'' || prompt[i] == '\"') && in_quotes == 0)
			in_quotes = prompt[i];
		else if (prompt[i] == in_quotes)
			in_quotes = 0;
		else
			res[j++] = prompt[i];
	}
	res[j] = '\0';
	return (res);
}

char	*trim_quote(char *tmp)
{
	char	*trim;
	char	*res;	

	trim = ft_strtrim(tmp, " ");
	res = remove_quotes(trim);
	free(trim);
	return (res);
}

char	*get_command(char *cmd, int *i, t_env *env)
{
	int		j;
	char	*res;
	char	*tmp;

	(void)env;
	res = NULL;
	tmp = NULL;
	while (cmd[*i] && ft_isspace(cmd[*i]) == 1)
		(*i)++;
	j = (*i);
	while (cmd[j] && ft_isspace(cmd[j]) == 0)
		j++;
	if (ft_isspace(cmd[j]) && is_in_quotes(cmd, (j)))
	{
		j = has_quote(cmd, j);
		tmp = ft_substr(cmd, (*i), j + 1);
		res = remove_quotes(tmp);
		(*i) = j;
		free(tmp);
		return (res);
	}
	tmp = ft_substr(cmd, (*i), j);
	res = trim_quote(tmp);
	free(tmp);
	return (res);
}

char	**get_option(char *cmd, int *i, t_env *env)
{
	char	**res;
	int		j;
	char	*trim;

	(void)env;
	j = -1;
	res = NULL;
	trim = remove_quotes(cmd);
	if ((size_t)(*i) == ft_strlen(trim))
		return (NULL);
	while (trim[*i] && ft_isspace(trim[*i]) == 0)
		(*i)++;
	while (trim[*i] && ft_isspace(trim[*i]) == 1)
		(*i)++;
	if (trim[*i])
		res = ft_split(&trim[*i], ' ');
	free(trim);
	return (res);
}
