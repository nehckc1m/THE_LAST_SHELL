/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehuang <hehuang@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:54:37 by hehuang           #+#    #+#             */
/*   Updated: 2024/11/23 17:07:38 by hehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_atoll(const char *string, int *err)
{
	int					neg;
	unsigned long long	res;
	int					i;

	res = 0;
	i = 0;
	neg = 1;
	while ((string[i] >= '\t' && string[i] <= '\r') || string[i] == ' ')
		i++;
	if (string[i] == '-' || string[i] == '+')
	{
		if (string[i++] == '-')
			neg *= -1;
	}
	while (string[i])
	{
		if (ft_isdigit(string[i]))
			res = (res * 10) + (string[i] - '0');
		else
			*err = -1;
		if ((neg == 1 && res > TLL_MAX) || (neg == -1 && res > TLL_MAX + 1))
			*err = -1;
		i++;
	}
	return ((int)((res * (unsigned long long)neg) % 256));
}

void	exit__with_code(t_exec_list *exec, t_env_list *env, \
				int exit_code, int exit_bool)
{
	g_exit_status = exit_code;
	if (exit_bool)
	{
		free_readline();
		free_env(env->env);
		free_exec_list(&(exec->exec));
		free_all_exit(exec, env, exit_code);
	}
}

void	ft_exit(t_exec_list *exec, t_env_list *env)
{
	int	err;
	int	res_signal;
	int	param_nb;

	err = 0;
	param_nb = count_params(exec->args);
	if (param_nb == 2)
	{
		res_signal = ft_check_atoll(exec->args[1], &err);
		if (err == -1)
		{
			write(2, EXIT_NO_NUM_ERR, ft_strlen(EXIT_NO_NUM_ERR));
			exit__with_code(exec, env, 2, TRUE);
		}
		exit__with_code(exec, env, res_signal, TRUE);
	}
	else if (param_nb > 2)
	{
		write(2, EXIT_ARGS_ERROR, ft_strlen(EXIT_ARGS_ERROR));
		exit__with_code(exec, env, 1, FALSE);
	}
	else
		exit__with_code(exec, env, EXIT_SUCCESS, TRUE);
}
