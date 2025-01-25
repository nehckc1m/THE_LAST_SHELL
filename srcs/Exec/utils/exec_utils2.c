/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:54:22 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/15 18:27:41 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_output(t_exec_list **exec, t_redirection	*redirect)
{
	if ((*exec)->fd_out > 2)
		close ((*exec)->fd_out);
	if (redirect->type == OUTPUT)
		(*exec)->fd_out = ft_open(redirect->payload, 1, 0);
	else
		(*exec)->fd_out = ft_open(redirect->payload, 0, 1);
	(*exec)->outfile = redirect->payload;
	if ((*exec)->fd_out == -1)
		perror((*exec)->outfile);
}

void	set_heredoc(char *name, t_exec_list **exec, int cancel)
{
	t_exec_list	*current;

	current = *exec;
	if (cancel == 1)
	{
		while (current)
		{
			current->cancel = 1;
			current = current->next;
		}
		del_curr_heredoc();
	}
	else if (access(name, F_OK) == 0)
	{
		(*exec)->fd_in = ft_open(name, 0, 0);
		(*exec)->infile = name;
	}
}

void	check_input(t_exec_list **exec, t_redirection *redirect)
{
	if ((*exec)->fd_in > 2)
		close ((*exec)->fd_in);
	if (redirect->type == INPUT)
	{
		(*exec)->fd_in = ft_open(redirect->payload, 0, 0);
		(*exec)->infile = redirect->payload;
	}
	else
	{
		signal_listener(2);
		if (redirect->payload == NULL && redirect->not_null)
			ft_here_doc("\0");
		else
			set_heredoc("heredoc.txt", exec, ft_here_doc(redirect->payload));
		signal_listener(1);
	}
	if ((*exec)->fd_in == -1)
	{
		(*exec)->args = add_str((*exec)->args, (char *)redirect->payload);
		perror((*exec)->infile);
	}
}

void	open_all_heredoc(t_exec_list **exec)
{
	t_exec_list		*curr_exec;
	t_redirection	*current;

	curr_exec = *exec;
	while (curr_exec)
	{
		current = curr_exec->redirec_list;
		while (current)
		{
			if (current->type == HERE_DOC)
				check_input(&curr_exec, current);
			current = current->next;
		}
		curr_exec = curr_exec->next;
	}
}

int	check_redirection(t_exec_list **exec)
{
	t_exec_list		*curr_exec;
	t_redirection	*current;

	curr_exec = *exec;
	open_all_heredoc(exec);
	while (curr_exec)
	{
		current = curr_exec->redirec_list;
		while (current)
		{
			if (current->type == INPUT)
				check_input(&curr_exec, current);
			else if (current->type == OUTPUT || current->type == APPEND)
				check_output(&curr_exec, current);
			current = current->next;
		}
		curr_exec = curr_exec->next;
	}
	return (SUCCESS);
}
