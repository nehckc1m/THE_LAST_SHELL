/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:52:18 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/24 15:19:38 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec_list	*new_exec_node(t_exec *exec)
{
	t_exec_list	*res;

	res = ft_calloc(sizeof(t_exec_list), 1);
	if (!res)
		return (NULL);
	res->fd_in = STDIN_FILENO;
	res->fd_out = STDOUT_FILENO;
	res->cancel = 0;
	res->cmd = ft_strdup(exec->cmd);
	res->args = get_args(exec);
	res->redirec_list = exec->redirection_list;
	res->exec = NULL;
	return (res);
}

void	add_exec_node(t_exec_list **head, t_exec_list *new_node)
{
	t_exec_list	*current;

	if (!(*head))
		(*head) = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
}

t_exec_list	*get_exec_list(t_exec *exec)
{
	t_exec		*current;
	t_exec_list	*res;

	current = exec;
	res = NULL;
	while (current != NULL)
	{
		add_exec_node(&res, new_exec_node(current));
		current = current->next;
	}
	return (res);
}

/*
void	free_exec_node(t_exec_list **node)
{
	if ((*node)->outfile)
		free
	free(*node);
}
*/
void	free_ex_list(t_exec_list **head)
{
	t_exec_list	*current;

	while (head != NULL)
	{
		current = (*head)->next;
		if ((*head)->args)
			ft_free_str_list((*head)->args);
		free(*head);
		head = &current;
	}
}

t_exec_list	*verif_exec(t_exec_list	*exec, t_env_list **env)
{
	t_exec_list	*current;
	int			i;

	current = exec;
	while (current)
	{
		replace_abs_path(&(current->cmd), env);
		i = 0;
		while (current->args[i])
		{
			replace_abs_path(&(current->args[i]), env);
			i++;
		}
		current = current -> next;
	}
	return (exec);
}
