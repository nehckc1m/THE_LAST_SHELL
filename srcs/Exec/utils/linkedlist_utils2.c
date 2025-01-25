/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:25:51 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/15 18:27:56 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_size(t_env_list *mylist)
{
	int	i;

	i = 0;
	while (mylist)
	{
		mylist = mylist->next;
		i++;
	}
	return (i);
}

t_env_list	*copy_list(t_env_list *env)
{
	t_env_list	*res;
	t_env_list	*current;

	current = env->next;
	res = new_env(env->name, env->val, NULL);
	while (current != NULL)
	{
		add_end(&res, new_env(current->name, current->val, current));
		current = current->next;
	}
	return (res);
}

int	set_value(t_env_list **node, char *str)
{
	char	*val;
	char	*tmp;

	if (ft_strchr_pos(str, '='))
	{
		val = ft_substr(str, ft_strchr_pos(str, '='), ft_strlen(str));
		if (ft_strchr_pos((*node)->name, '=') == -1)
		{
			tmp = ft_strjoin((*node)->name, "=");
			free((*node)->name);
			(*node)->name = tmp;
		}
		if ((*node)->val)
			free((*node)->val);
		(*node)->val = val;
	}
	return (FAIL);
}

t_env_list	*create_list_from_tab(char **env)
{
	int			i;
	t_env_list	*res;
	t_env_list	*current;

	i = 0;
	if (env && env[i])
	{
		res = new_env(env[i], NULL, NULL);
		current = res;
		while (env[++i])
		{
			current->next = new_env(env[i], NULL, current);
			current = current->next;
		}
		return (res);
	}
	return (NULL);
}
