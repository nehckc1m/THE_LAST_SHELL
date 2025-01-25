/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:09:15 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/04 15:53:22 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_curr_heredoc(void)
{
	if (access("heredoc.txt", F_OK) == 0)
	{
		unlink("heredoc.txt");
	}
}

void	write_here_doc(char *delimiter, int fd)
{
	char	*line;
	char	*tmp_limit;

	tmp_limit = ft_strjoin(delimiter, "\n");
	while (1)
	{
		write(2, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line && g_exit_status != 130)
		{
			printf("here-doc delimited by EOF (wanted '%s')\n", delimiter);
			break ;
		}
		if (!line)
			break ;
		if (ft_strcmp(line, tmp_limit) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, strlen(line));
		free(line);
	}
	free(tmp_limit);
}

int	ft_here_doc(const char *delimiter)
{
	int			fd;
	const char	*filename = "heredoc.txt";

	fd = ft_open(filename, 1, 0);
	write_here_doc((char *)delimiter, fd);
	ft_close(fd, "heredoc.txt", -1);
	if (g_exit_status == 130)
	{
		unlink("heredoc.txt");
		if (g_exit_status == 130)
			return (1);
	}
	return (0);
}
