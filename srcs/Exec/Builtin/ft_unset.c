/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:46:49 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/15 18:27:18 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_and_rm(t_env_list	**env, char *my_var)
{
	t_env_list	*current;
	int			len;

	current = *env;
	len = ft_strlen(my_var);
	while (current != NULL)
	{
		if (!ft_strncmp(current->name, my_var, len)
			&& (!my_var[len]
				|| (current->name[len] == '=' && current->name[len + 1])))
		{
			rm_elmt(env, current);
			return (SUCCESS);
		}
		current = current->next;
	}
	return (FAIL);
}

void	ft_unset(t_env_list	**env, char **params)
{
	int	i;

	i = -1;
	while (params[++i])
		find_and_rm(env, params[i]);
	update_env(env);
}
