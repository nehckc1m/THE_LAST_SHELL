/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:03:27 by micchen           #+#    #+#             */
/*   Updated: 2025/01/22 02:03:29 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_payload(t_redirection *tmp, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i] && (cmd[i] == '<' || cmd[i] == '>'))
		i++;
	while (cmd[i] && ft_isspace(cmd[i]) == 1)
		i++;
	j = i;
	while (cmd[j] && ft_isspace(cmd[j]) == 0 && \
						(cmd[j] != '<' && cmd[j] != '>'))
		j++;
	tmp->payload = ft_substr(cmd, i, (j - i));
	if (ft_strcmp((char *)tmp->payload, "\"\""))
		tmp->not_null = 0;
	trim_payload_quotes((char *)tmp->payload);
	return (j);
}

int	fill_redirection(t_redirection *redirection_list, char *cmd)
{
	t_redirection	*tmp;
	int				i;

	i = 0;
	tmp = redirection_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (cmd[i] == '<' && cmd[i + 1] == '<')
		tmp->type = HERE_DOC;
	else if (cmd[i] == '>' && cmd[i + 1] == '>')
		tmp->type = APPEND;
	else if (cmd[i] == '<')
		tmp->type = INPUT;
	else if (cmd[i] == '>')
		tmp->type = OUTPUT;
	i += fill_payload(tmp, cmd);
	return (i);
}

void	pass_redirection_and_payload(char **line, int *i)
{
	while ((*line)[*i] && ((*line)[*i] == '<' || (*line)[*i] == '>'))
		*i += 1;
	while ((*line)[*i] && ft_isspace((*line)[*i]) == 0)
		*i += 1;
	while ((*line)[*i] && ft_isspace((*line)[*i]) != 0
		&& (*line)[*i] != '<' && (*line)[*i] != '>')
		*i += 1;
	if ((*line)[*i] != '\0' && (*line)[*i] != '<' && (*line)[*i] != '>')
		*i += 1;
}

void	trim_redirections(char **line)
{
	int		i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '>' || (*line)[i] == '<')
		{
			(*line)[i] = '\0';
			(*line)[i + 1] = '\0';
		}
		i++;
	}
}

/*void	exec_trim(char **line, char **res, int *i, int j)
{
	char	*sub_str;
	char	*tmp;

	tmp = NULL;
	if (*res != NULL)
	{
		tmp = ft_strdup(*res);
		free(*res);
		*res = NULL;
	}
	while ((*line)[*i] && (*line)[*i] != '<' && (*line)[*i] != '>')
		*i += 1;
	sub_str = ft_substr((*line), j, (*i - j));
	if ((*line)[*i] == '\0')
		*res = ft_strjoin(tmp, sub_str);
	else if ((*line)[*i] && is_in_quotes((*line), *i) == 0)
		*res = ft_strjoin(tmp, sub_str);
	free(tmp);
	free(sub_str);
	pass_redirection_and_payload(line, i);
}*/
