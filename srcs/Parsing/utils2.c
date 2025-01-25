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
	//printf("cmd dans get_redirec: %s\n", cmd);
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
		{
			if (is_in_quotes(cmd, i) == 0)
			{
				printf("izi\n");
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
	//printf("payload1:%s\n", current->payload);
	//if (current->next)
	//	printf("YA UN TRUC SA MERE\n");
	//printf("done get_redirection\n");
	return (current);
}


char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++; // Localise la fin de dest
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0'; // Ajoute le caractère nul
	return (dest);
}

/*
char	*ft_triming(char *cmd)
{
	char	*res;
	int	i;

	i = 0;
	res = ft_strtrim(cmd, " ");
	while (res[i])
	{
		if (is_in_quotes(cmd, i))
		{
			
		
		}
	}
	res = ft_strtrim(cmd, " ");
	return (res);
}*/

char	*get_command(char *cmd, int *i, t_env *env)
{
	int	j;
	char	*res;
	char	*tmp;
	(void)env;
	res = NULL;
	tmp = NULL;

	printf("cmd dans get command:%s\n",cmd);
	while (cmd[*i] && ft_isspace(cmd[*i]) == 1)
		(*i)++;
	j = (*i);
	while (cmd[j] && ft_isspace(cmd[j]) == 0)
		j++;
	if (ft_isspace(cmd[j]) && is_in_quotes(cmd, (j)))
	{
		j = has_quote(cmd, j);
		tmp = ft_substr(cmd, (*i), j);
		res = ft_strtrim(tmp, " ");
		(*i) = j;
		free(tmp);
		return (res);
	}
	tmp = ft_substr(cmd, (*i), j);
	res = ft_strtrim(tmp, " ");
	printf("res:%s\n",res);
	free(tmp);
	return (res);
}

char	**get_option(char *cmd, int *i, t_env *env)
{
	char	**res;
	int	j;
	(void)env;
	j = -1;
	res = NULL;
	if ((size_t)(*i) == ft_strlen(cmd))
		return (NULL);
	while (cmd[*i] && ft_isspace(cmd[*i]) == 0)
		(*i)++;
	while (cmd[*i] && ft_isspace(cmd[*i]) == 1)
		(*i)++;
	if (cmd[*i])
		res = ft_split(&cmd[*i], ' ');
	//while (res[++j])
	//	res[j] = handle_expand(res[j], env);
	return (res);

}
