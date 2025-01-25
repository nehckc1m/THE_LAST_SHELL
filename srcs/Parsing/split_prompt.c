/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 00:14:07 by micchen           #+#    #+#             */
/*   Updated: 2025/01/18 01:03:29 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_count_commands(const char *prompt, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!prompt || *prompt == '\0')
		return (0);
	while (prompt[i])
	{
		while ((prompt[i] != c || (prompt[i] == c \
		&& (is_in_quotes((char *)prompt, i) != 0))) && prompt[i])
			i++;
		if (prompt[i] == c && prompt[i])
			i++;
		count++;
	}
	return (count);
}

t_exec	*filling_node(t_exec *current, char *cmd, t_env *env)
{
	int		i;
	char	*tmp;

	tmp = ft_strdup(cmd);
	i = 0;
	current->redirection_list = get_redirection(tmp);
	if (current->redirection_list)
		trim_redirections(&cmd);
	current->cmd = get_command(tmp, &i, env);
	//i = ft_strlen(current->cmd);
	current->option = get_option(tmp, &i, env);
	free(tmp);
	return (current);
}

void	fill_cmd_list(t_exec *command_list, \
		char const *prompt, char c, t_env *env)
{
	int		i;
	int		j;
	t_exec	*current;
	char	*tmp;

	current = command_list;
	i = 0;
	j = 0;
	while (prompt[i])
	{
		j = i;
		while ((prompt[i] != c || (prompt[i] == c \
		&& (is_in_quotes((char *)prompt, i) != 0))) && prompt[i])
			i++;
		tmp = ft_substr(prompt, j, i - j);
		filling_node(current, tmp, env);
		free(tmp);
		while (prompt[i] == c && prompt[i])
			i++;
		current = current->next;
	}
}

t_exec	*create_command_list(int index)
{
	int		i;
	t_exec	*head;
	t_exec	*tmp;

	i = 0;
	head = create_new_node();
	if (!head)
		return (NULL);
	tmp = head;
	while (++i <= index)
	{
		if (index > i)
		{
			tmp->next = create_new_node();
			tmp = tmp->next;
		}
	}
	return (head);
}

t_exec	*split_prompt(char const *prompt, char c, t_env *env)
{
	t_exec		*command_list;
	int			count_cmd;
	char		*expanded_cmd;

	if (!prompt)
		return (NULL);
	count_cmd = ft_count_commands(prompt, c);
	command_list = create_command_list(count_cmd);
	expanded_cmd = handle_expand((char *)prompt, env);
	if (!expanded_cmd)
	{
		free(expanded_cmd);
		return (NULL);
	}
	fill_cmd_list(command_list, expanded_cmd, c, env);
	free(expanded_cmd);
	return (command_list);
}
/*int main (int ac, char **av)
{
	int	i = 0;
	t_exec	*test;
	test = NULL;
	test = split_prompt("ls -l | grep .c | wc -l | zizi", '|');
	while (test)
	{
		printf("SUCESS:%s\n", test->cmd);
		test = test->next;
	}
	return (1);
}*/
