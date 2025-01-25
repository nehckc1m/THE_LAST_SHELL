/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:21:50 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/15 18:27:49 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*new_env(char *name, char *value, t_env_list *prev)
{
	t_env_list	*res;

	if (!name)
		return (NULL);
	res = ft_calloc(sizeof(t_env_list), 1);
	res->prev = prev;
	if (!value && ft_strchr_pos(name, '=') != -1)
	{
		res->val = ft_substr(name, ft_strchr_pos(name, '='), ft_strlen(name));
		res->name = ft_substr(name, 0, ft_strchr_pos(name, '='));
	}
	else if (!value)
		res->name = ft_substr(name, 0, ft_strlen(name));
	else
	{
		res->name = ft_strdup((const char *)name);
		res->val = ft_strdup((const char *)value);
	}
	res->env = NULL;
	return (res);
}

void	add_end(t_env_list **env, t_env_list *new_elmt)
{
	t_env_list	*current;

	if (!env)
	{
		*env = new_elmt;
		return ;
	}
	current = *env;
	while (current->next != NULL)
		current = current->next;
	new_elmt->prev = current;
	current->next = new_elmt;
}

void	rm_elmt(t_env_list **env, t_env_list *elmt)
{
	t_env_list	*tmp;

	if (elmt->prev == NULL)
		*env = (*env)->next;
	else if (elmt->next == NULL)
		elmt->prev->next = NULL;
	else
	{
		tmp = elmt->prev;
		tmp->next = elmt->next;
		elmt->next->prev = tmp;
	}
	free_elmt(&elmt);
}

t_env_list	*find_elmt(t_env_list **env, char	*elmt)
{
	int			i;
	t_env_list	*current;
	char		*tmp_var;
	t_env_list	*res;

	i = ft_strchr_pos(elmt, '=');
	if (i > 0)
		tmp_var = ft_substr(elmt, 0, i);
	else
		tmp_var = ft_strjoin(elmt, "=");
	current = *env;
	while (current)
	{
		if (!ft_strcmp(tmp_var, current->name)
			|| !ft_strcmp(elmt, current->name))
		{
			res = current;
			free(tmp_var);
			return (res);
		}
		current = current->next;
	}
	free(tmp_var);
	return (NULL);
}
