/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:20:56 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/15 18:26:47 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option_n(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void	ft_echo(t_exec_list *exec)
{
	int	i;
	int	n;

	if (!exec->args[1])
	{
		write(1, "\n", 1);
		return ;
	}
	n = check_option_n(exec->args[1]);
	i = n;
	while (exec->args[++i])
	{
		if (i - 1 != n)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(exec->args[i], 1);
	}
	if (!check_option_n(exec->args[n]))
		ft_putchar_fd('\n', 1);
}

int	find_and_set(t_env_list	**env, char *my_var, char	*new_val)
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
			current->val = new_val;
			return (SUCCESS);
		}
		current = current->next;
	}
	return (FAIL);
}

int	valid_name(char *name)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = -1;
	while (++i < len)
	{
		if (name[i] == '\\')
			return (0);
		if (name[i] == '+' && ((i + 1 < len) && name[i + 1] != '='))
			return (0);
		if (name[i] == '-')
			return (0);
		if (name[i] == '*')
			return (0);
		if (name[i] == '%')
			return (0);
		if (name[i] == '.')
			return (0);
	}
	return (1);
}
