/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:58:45 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/24 15:28:43 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	free_child(char	**str_tab, t_exec_list *exec_list, \
				t_env_list *env_list, t_exec *exec)
{
	ft_free_str_list(str_tab);
	if (env_list->env)
		free_env(env_list->env);
	free_exec_list(&exec);
	clear_history();
	rl_clear_history();
	rl_clear_signals();
	free_all_exit(exec_list, env_list, g_exit_status);
}

void	dup_in_out(t_exec_list *exec)
{
	if (exec->prev && exec->fd_in <= 2)
	{
		dup2(exec->prev->pipe_fd[0], STDIN_FILENO);
		exec->fd_in = exec->prev->pipe_fd[0];
	}
	if (exec->next != NULL && exec->fd_out <= 2)
	{
		dup2(exec->pipe_fd[1], STDOUT_FILENO);
		exec->fd_out = exec->pipe_fd[1];
	}
	if (exec->fd_in > 2)
		dup2(exec->fd_in, STDIN_FILENO);
	if (exec->fd_out > 2)
		dup2(exec->fd_out, STDOUT_FILENO);
	ft_close(exec->pipe_fd[0], NULL, 0);
	ft_close(exec->pipe_fd[1], NULL, 1);
}

void	close_all_fd(t_exec_list	**exec)
{
	t_exec_list	*current;

	current = *exec;
	while (current)
	{
		if (current->fd_in > 2)
			ft_close(current->fd_in, current->infile, -1);
		if (current->fd_out > 2)
			ft_close(current->fd_out, current->outfile, -1);
		current = current->next;
	}
}

void	solo_builtins(t_exec_list *exec, t_env_list **env)
{
	int	save_stdout;
	int	save_stdin;

	if (!ft_strcmp(exec->cmd, "exit"))
	{
		exec_builtin(exec, env, 0);
		return ;
	}
	save_stdout = dup(STDOUT_FILENO);
	save_stdin = dup(STDIN_FILENO);
	check_redirection(&exec);
	exec_builtin(exec, env, 0);
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdin);
	close(save_stdout);
}

void	replace_abs_path(char	**str, t_env_list **env)
{
	char	*new_val;

	new_val = NULL;
	if (*str && *str[0] == '~')
		new_val = ft_strjoin(find_elmt(env, "HOME")->val, *str + 1);
	if (new_val)
	{
		free(*str);
		*str = new_val;
	}
}
