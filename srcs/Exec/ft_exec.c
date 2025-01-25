/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:42:14 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/24 15:45:10 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_exec_list *exec, t_env_list **env, int in_child)
{
	if (g_exit_status == 130 && exec->cancel)
		return (SUCCESS);
	dup_in_out(exec);
	if (!ft_strcmp(exec->cmd, "echo"))
		ft_echo(exec);
	else if (!ft_strcmp(exec->cmd, "cd") && !in_child)
		ft_cd(exec->args, env);
	else if (!ft_strcmp(exec->cmd, "exit") && !in_child)
		ft_exit(exec, *env);
	else if (!ft_strcmp(exec->cmd, "unset") && !in_child)
		ft_unset(env, exec->args);
	else if (!ft_strcmp(exec->cmd, "export"))
		ft_export(env, exec->args);
	else if (!ft_strcmp(exec->cmd, "env"))
		ft_env(*env);
	else if (!ft_strcmp(exec->cmd, "pwd"))
		ft_pwd();
	else
		return (FAIL);
	return (SUCCESS);
}

void	execute_cmd(t_exec_list	*exec_list, t_env_list **env_list, t_exec *exec)
{
	char				**env_str;
	char				*path;

	env_str = list_to_char(env_list);
	if (exec_list->cmd[0] == '\0')
		exec_list->cancel = 1;
	if (env_list && check_builtin(exec_list) == SUCCESS && g_exit_status != 130)
	{
		exec_builtin(exec_list, env_list, 1);
		return (free_child(env_str, exec_list, *env_list, exec));
	}
	else if (!exec_list->cancel && g_exit_status != 130 && g_exit_status != 131)
	{
		path = ft_get_path(exec_list->cmd, env_list);
		execve(path, exec_list->args, env_str);
		write(2, exec_list->cmd, ft_strlen(exec_list->cmd));
		write(2, ERR_CMD_NOT_FOUND, ft_strlen(ERR_CMD_NOT_FOUND));
		g_exit_status = 127;
		return (free_child(env_str, exec_list, *env_list, exec));
	}
	else
		return (free_child(env_str, exec_list, *env_list, exec));
}

void	parent_process(t_exec_list **exec_list)
{
	t_exec_list	*current;

	current = *exec_list;
	while (current->next)
		current = current->next;
	ft_close (current->pipe_fd[0], NULL, 0);
	while (current)
	{
		waitpid(current->pid, (int *)&g_exit_status, 0);
		if (WIFSIGNALED(g_exit_status))
			g_exit_status = 128 + WTERMSIG(g_exit_status);
		else if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		current = current->prev;
	}
}

void	child_process(t_exec_list **exec_list, \
			t_env_list **env_list, t_exec *exec)
{
	if (pipe((*exec_list)->pipe_fd) == -1)
	{
		perror("pipe");
		free_all_exit(*exec_list, *env_list, EXIT_FAILURE);
	}
	(*exec_list)->pid = fork();
	if ((*exec_list)->pid < -1)
	{
		perror("pid");
		free_all_exit(*exec_list, *env_list, EXIT_FAILURE);
	}
	else if (!(*exec_list)->pid)
	{
		dup_in_out(*exec_list);
		close_all_fd(exec_list);
		ft_close((*exec_list)->pipe_fd[0], NULL, 0);
		execute_cmd(*exec_list, env_list, exec);
	}
	if ((*exec_list)->prev)
		ft_close((*exec_list)->prev->pipe_fd[0], NULL, 0);
	ft_close((*exec_list)->pipe_fd[1], NULL, 1);
}

void	ft_exec(t_exec *exec, t_env *env)
{
	t_exec_list			*exec_list;
	t_exec_list			*head;

	signal_listener(1);
	if (!env->head)
		env->head = create_list_from_tab(env->env);
	env->head->env = env;
	head = verif_exec(get_exec_list(exec), &(env->head));
	head->exec = exec;
	exec_list = head;
	if (exec_list->next == NULL && check_builtin(exec_list) == SUCCESS)
		solo_builtins(exec_list, &(env->head));
	else
	{
		check_redirection(&exec_list);
		while (exec_list)
		{
			child_process(&exec_list, &(env->head), exec);
			exec_list = exec_list->next;
		}
		parent_process(&head);
	}
	env->last_status = g_exit_status;
	g_exit_status = 0;
	return (close_all_fd(&head), free_all_exit(head, NULL, -1));
}
