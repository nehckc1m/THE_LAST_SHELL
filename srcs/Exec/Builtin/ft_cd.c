/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:57:58 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/24 15:47:39 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_env_list **env)
{
	t_env_list	*current;
	char		cwd[1024];

	current = *env;
	while (current)
	{
		if (!ft_strncmp(current->name, "OLDPWD", 6))
		{
			free(current->val);
			current->val = ft_strdup(find_elmt(env, "PWD")->val);
		}
		if (!ft_strncmp(current->name, "PWD", 3))
		{
			free(current->val);
			current->val = ft_strdup(getcwd(cwd, sizeof(cwd)));
		}
		current = current->next;
	}
}

void	ft_cd(char **path, t_env_list **env)
{
	int		param_nb;
	char	*home_path;
	int		err;

	param_nb = count_params(path);
	err = 0;
	if (param_nb == 2)
	{
		if (path[1][0] == '~')
		{
			home_path = ft_strjoin(find_elmt(env, "HOME")->val, path[1] + 1);
			err = chdir(home_path);
			free(home_path);
		}
		else
			err = chdir(path[1]);
	}
	else if (param_nb == 1)
		err = chdir((find_elmt(env, "HOME"))->val);
	if (err != 0)
	{
		perror("cd");
		return ;
	}
	return (update_pwd(env), update_env(env));
}

void	ft_pwd(void)
{
	char	cwd[1024];

	ft_putstr_fd(getcwd(cwd, sizeof(cwd)), 1);
	ft_putchar_fd('\n', 1);
}
