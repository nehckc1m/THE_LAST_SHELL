/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 01:56:16 by micchen           #+#    #+#             */
/*   Updated: 2025/01/22 01:56:42 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*redirection_list_new_node(void)
{
	t_redirection	*new;

	new = malloc(sizeof(t_redirection));
	if (!new)
		return (NULL);
	new->type = NONE;
	new->payload = NULL;
	new->not_null = 1;
	new->next = NULL;
	return (new);
}

t_redirection	*redirection_list_last(t_redirection *lst)
{
	t_redirection	*last;

	if (!lst)
	{
		printf("RIEN\n");
		return (NULL);
	}
	last = lst;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_redirection	*redirection_list_add_back(t_redirection *exec, \
		t_redirection *neww)
{
	t_redirection	*last;

	last = redirection_list_last(exec);
	if (last)
		last->next = neww;
	else
	{
		printf("ouais\n");
		exec = neww;
	}
	return (exec);
}
