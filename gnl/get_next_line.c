/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 08:44:08 by micchen           #+#    #+#             */
/*   Updated: 2023/12/19 16:38:27 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1] = {0};	
	int				res_read;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strchr_gnl(buffer, '\n'))
	{
		clean_buffer(buffer);
		line = ft_strjoin_gnl(line, buffer);
	}
	res_read = 1;
	while (res_read >= 1 && !ft_strchr_gnl(buffer, '\n'))
	{
		res_read = read(fd, buffer, BUFFER_SIZE);
		if (res_read == -1)
		{
			free(line);
			return (NULL);
		}
		buffer[res_read] = '\0';
		line = ft_strjoin_gnl(line, buffer);
	}
	return (line);
}

/*
int	main()
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}*/
