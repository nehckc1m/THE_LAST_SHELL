/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 22:28:50 by micchen           #+#    #+#             */
/*   Updated: 2025/01/19 22:28:51 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_rl(int sig_state)
{
	if (sig_state == SIGINT)
	{
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = sig_state + 128;
	}
}

void	signal_handler_exec(int sig_state)
{
	if (sig_state == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_status = sig_state + 128;
	}
	else if (sig_state == 3)
	{
		printf("Quit (core dumped)\n");
		g_exit_status = sig_state + 128;
	}
}

void	signal_handler_here_doc(int sig_state)
{
	if (sig_state == SIGINT)
	{
		printf("\n");
		g_exit_status = sig_state + 128;
		rl_on_new_line();
	}
	if (sig_state == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		g_exit_status = sig_state + 128;
	}
}

void	signal_listener(int sig_state)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_int.sa_flags = SA_RESTART;
	sig_quit.sa_flags = SA_RESTART;
	sigemptyset(&(sig_int.sa_mask));
	sigemptyset(&(sig_quit.sa_mask));
	if (sig_state == 0)
	{
		sig_int.sa_handler = signal_handler_rl;
		sig_quit.sa_handler = SIG_IGN;
	}
	else if (sig_state == 1)
	{
		sig_int.sa_handler = signal_handler_exec;
		sig_quit.sa_handler = signal_handler_exec;
	}
	else if (sig_state == 2)
	{
		sig_int.sa_handler = signal_handler_here_doc;
		sig_quit.sa_handler = signal_handler_here_doc;
		sig_int.sa_flags = 0;
	}
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}
