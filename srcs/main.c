/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:49:33 by micchen           #+#    #+#             */
/*   Updated: 2025/01/18 20:49:43 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status;

static int	parsing_prompt(char *prompt, t_env *env);

static int	copy_env(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	env->env = malloc(sizeof(char *) * (i + 1));
	if (!env->env)
	{
		perror("failed malloc env!");
		return (free(env->env), 0);
	}
	i = -1;
	while (envp[++i])
	{
		env->env[i] = ft_strdup(envp[i]);
		if (!env->env[i])
		{
			perror("failed copy env to array!");
			return (free_array(env->env), 0);
		}
	}
	env->head = NULL;
	env->env[i] = NULL;
	env->last_status = 0;
	return (1);
}

int	read_prompt(t_env *env)
{
	char	*prompt;

	prompt = NULL;
	rl_catch_signals = 0;
	while (1)
	{
		signal_listener(0);
		prompt = readline("minihell>");
		if (!prompt)
		{
			free_env(env);
			free_readline();
			free_all_exit(NULL, env->head, -1);
			del_curr_heredoc();
			printf("exit\n");
			return (0);
		}
		else if (prompt && prompt[0] != '\0')
		{
			add_history(prompt);
			if (parsing_prompt(prompt, env) == 0)
				printf("syntax error\n");
		}
		free(prompt);
	}
}

void	print_command_list(t_exec *command)
{
	int i = -1;
	while (command)
	{	
		if (command->cmd)
			printf("cmdlist cmd: %s\n",command->cmd);
		if (command->option)
		{
			while (command->option[++i])
				printf("cmdlist option: %s\n",command->option[i]);
		}
		i = -1;
		command = command->next;
	}
	printf("print cmmand list done\n");
}

static int	parsing_prompt(char *prompt, t_env *env)
{
	t_exec	*command_list;

	(void)env;
	if (check_syntax(prompt))
		return (0);
	command_list = split_prompt(prompt, '|', env);
	print_command_list(command_list);
	if (check_payload(&command_list), 0)
	{
		free_exec_list(&command_list);
		return (0);
	}
	ft_exec(command_list, env);
	free_exec_list(&command_list);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;

	(void)av;
	(void)envp;
	g_exit_status = 0;
	if (ac > 1)
	{
		perror("too much args for minishell!");
		return (0);
	}
	//init_shell(shell);
	//printf("zizi\n");
	if (copy_env(&env, envp) == 0)
		return (0);
	//printf("zizi2\n");
	read_prompt(&env);
	return (g_exit_status);
}
