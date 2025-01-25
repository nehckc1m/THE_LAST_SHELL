/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:33:23 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/24 15:44:52 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	display_exec(t_exec_list *exec)
{
	int	i;

	i = -1;
	dprintf(2, "---------DISPLAY EXEC----------\n");
	dprintf(2, "cmd = |%s|\n", exec->cmd);
	while (exec->args[++i])
		dprintf(2, "args[%d] = |%s|\n", i, exec->args[i]);
	dprintf(2, "args[%d] = |%s|\n", i, exec->args[i]);
	dprintf(2, "---------DISPLAY END-----------\n");
}

void	ft_close(int fd, const char *filename, int pipe_entry)
{
	if (fd > 2)
		close(fd);
	(void)filename;
	(void)pipe_entry;
	if (pipe_entry != -1)
		dprintf(2, "\033[34mClosing pipe_fd[%d] \033[0m=> \
		fd : %d\n", pipe_entry, fd);
	else
		dprintf(2, "\033[34mClosing %s \033[0m=> fd : %d\n", filename, fd);
}

int	ft_open(const char *filename, int trunc, int append)
{
	int	fd;

	if (trunc)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (fd);
	if (fd == 0)
		dprintf(2, "\033[31mWARNING STDIN CLOSED PREVIOUSLY\033[0m\n");
	else if (fd == 1)
		dprintf(2, "\033[31mWARNING STDOUT CLOSED PREVIOUSLY\033[0m\n");
	else if (fd == 2)
		dprintf(2, "\033[31mWARNING STDERR CLOSED PREVIOUSLY\033[0m\n");
	dprintf(2, "\033[33mOpening %s \033[0m=> fd : %d\n", filename, fd);
	return (fd);
}*/

void	ft_close(int fd, const char *filename, int pipe_entry)
{
	(void)filename;
	(void)pipe_entry;
	if (fd > 2)
		close(fd);
}

int	ft_open(const char *filename, int trunc, int append)
{
	int	fd;

	if (trunc)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (fd);
	return (fd);
}

char	**get_args(t_exec *exec)
{
	char	**res;
	int		j;
	int		i;

	i = 0;
	if (exec->option)
	{
		while (exec->option[i])
			i++;
	}
	res = malloc (sizeof(char *) * (i + 2));
	j = 0;
	res[j] = ft_strdup((char *)exec->cmd);
	while (++j < i + 1)
		res[j] = ft_strdup((char *)exec->option[j - 1]);
	res[j] = NULL;
	i = -1;
	return (res);
}

char	**add_str(char **tab, char *elmt)
{
	char	**res;
	int		j;
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			i++;
	}
	res = malloc (sizeof(char *) * (i + 2));
	j = -1;
	while (++j < i)
		res[j] = ft_strdup((char *)tab[j]);
	res[j] = ft_strdup((char *)elmt);
	res[++j] = NULL;
	i = -1;
	ft_free_str_list(tab);
	return (res);
}

int	check_builtin(t_exec_list *exec)
{
	if (!ft_strcmp(exec->cmd, "echo"))
		return (SUCCESS);
	else if (!ft_strcmp(exec->cmd, "cd"))
		return (SUCCESS);
	else if (!ft_strcmp(exec->cmd, "exit"))
		return (SUCCESS);
	else if (!ft_strcmp(exec->cmd, "unset"))
		return (SUCCESS);
	else if (!ft_strcmp(exec->cmd, "export"))
		return (SUCCESS);
	else if (!ft_strcmp(exec->cmd, "env"))
		return (SUCCESS);
	else if (!ft_strcmp(exec->cmd, "pwd"))
		return (SUCCESS);
	else
		return (FAIL);
}
