/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:48:01 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/24 15:45:20 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char	*cmd, t_env_list **env)
{
	char		**paths;
	char		*exec;
	char		*path;
	t_env_list	*node;
	int			i;

	if (ft_strchr_pos(cmd, '/') >= 0)
		return (cmd);
	i = -1;
	node = find_elmt(env, "PATH");
	if (!node)
		return (cmd);
	paths = ft_split(node->val, ':');
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(path, cmd);
		if (access(exec, F_OK | X_OK) == 0)
			return (free(path), ft_free_str_list(paths), exec);
		free(path);
		free (exec);
	}
	return (ft_free_str_list(paths), cmd);
}

char	**copy_tab(char	**env, int *size)
{
	int		i;
	char	**copy;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	*size = i;
	copy = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		copy[i] = env[i];
	copy[i] = NULL;
	return (copy);
}

int	ft_strchr_pos(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != (char)c && s[i] != '\0')
		i++;
	if (s[i] == (char)c)
		return (i + 1);
	return (-1);
}

int	count_params(char	**params)
{
	int	i;

	i = 0;
	if (!params)
		return (i);
	while (params[i])
		i++;
	return (i);
}

char	**list_to_char(t_env_list **env)
{
	int			len;
	int			i;
	char		**res;
	t_env_list	*current;

	len = list_size(*env);
	res = ft_calloc(sizeof(char *), (len + 1));
	current = *env;
	i = -1;
	while (++i < len)
	{
		res[i] = ft_strjoin(current->name, current->val);
		if (!res[i])
		{
			ft_free_str_list(res);
			return (NULL);
		}
		current = current->next;
	}
	return (res);
}
