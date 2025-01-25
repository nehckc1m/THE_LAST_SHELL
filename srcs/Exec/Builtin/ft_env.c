/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:34:15 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/15 18:26:59 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env_list *env)
{
	t_env_list	*current;

	current = env;
	while (current != NULL)
	{
		if (current->val && ft_strcmp("", current->val))
			printf("%s%s\n", current->name, current->val);
		else if (ft_strchr(current->name, '='))
			printf("%s\n", current->name);
		current = current->next;
	}
}

void	update_env(t_env_list **env)
{
	char	**new_env_list;

	new_env_list = list_to_char(env);
	ft_free_str_list((*env)->env->env);
	(*env)->env->env = new_env_list;
}

void	append_val(t_env_list **elmt, char	*app_val, t_env_list **env)
{
	char	*new_name;
	char	*new_val;
	char	*tmp;

	tmp = ft_substr(app_val, 0, ft_strchr_pos(app_val, '+') - 1);
	new_name = ft_strjoin(tmp, "=");
	new_val = ft_substr(app_val, ft_strchr_pos(app_val, '='), \
				ft_strlen(app_val));
	free(tmp);
	if (!(*elmt))
	{
		(*elmt) = new_env(new_name, new_val, NULL);
		add_end(env, (*elmt));
		free(new_name);
	}
	else
	{
		tmp = ft_strjoin((*elmt)->val, new_val);
		free((*elmt)->val);
		free((*elmt)->name);
		(*elmt)->name = new_name;
		(*elmt)->val = tmp;
	}
	free(new_val);
}

char	*get_correct_val(char *name, int *plus, int *equal)
{
	char	*res;

	*equal = ft_strchr_pos(name, '=');
	*plus = ft_strchr_pos(name, '+');
	if (((*equal) == ((*plus) + 1))
		|| ((*equal) == -1 && (*plus) == ((int) ft_strlen(name) - 1)))
		res = ft_substr(name, 0, ((*plus) - 1));
	else if ((*equal) != -1 && (*plus) == -1)
		res = ft_substr(name, 0, (*equal) - 1);
	else
		res = ft_strdup(name);
	if (!valid_name(res) || (*equal == -1 && *plus != (int)ft_strlen(name)))
	{
		free(res);
		return (NULL);
	}
	return (res);
}

t_env_list	*find_env(t_env_list **head, char	*name, int *plus)
{
	t_env_list	*current;
	int			equal;
	char		*tmp;
	char		*tmp2;

	current = *head;
	tmp = get_correct_val(name, plus, &equal);
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(tmp, "=");
	while (current)
	{
		if (!ft_strcmp(current->name, tmp2) || !ft_strcmp(current->name, tmp))
		{
			free(tmp2);
			free(tmp);
			return (current);
		}
		current = current->next;
	}
	free(tmp);
	free(tmp2);
	return (NULL);
}
