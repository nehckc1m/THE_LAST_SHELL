/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 03:18:11 by micchen           #+#    #+#             */
/*   Updated: 2025/01/23 03:18:20 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *copy)
{
	int	i;

	i = 0;
	while (copy->env[i])
		free(copy->env[i++]);
	free(copy->env);
}

void	free_readline(void)
{
	clear_history();
	rl_clear_pending_input();
	rl_clear_signals();
	rl_clear_history();
	rl_free_line_state();
	rl_deprep_terminal();
}

void	free_redirection_list(t_redirection **list)
{
	t_redirection	*nav;

	while (*list)
	{
		nav = (*list)->next;
		free((void *)(*list)->payload);
		free((*list));
		*list = nav;
	}
	free(*list);
	*list = NULL;
}

void	free_exec_list(t_exec **exec)
{
	t_exec	*nav;
	int		i;

	while (*exec)
	{
		nav = (*exec)->next;
		free_redirection_list(&(*exec)->redirection_list);
		if ((*exec) != NULL && (*exec)->cmd != NULL)
		{
			free((*exec)->cmd);
			(*exec)->cmd = NULL;
		}
		i = 0;
		if ((*exec)->option)
			while ((*exec)->option[i])
				free((*exec)->option[i++]);
		free((*exec)->option);
		(*exec)->option = NULL;
		free(*exec);
		*exec = nav;
	}
	free(*exec);
	*exec = NULL;
}
