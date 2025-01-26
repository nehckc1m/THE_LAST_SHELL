/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:01:31 by micchen           #+#    #+#             */
/*   Updated: 2024/11/16 21:54:57 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../gnl/get_next_line.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <limits.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <termios.h>
# include <curses.h>
# include <dirent.h>

# define SUCCESS			0
# define FAIL				1
# define TRUE				1
# define FALSE				0

# define TLL_MAX			9223372036854775807ULL

# define EXIT_NO_NUM_ERR	"exit : numeric argument required\n"
# define EXIT_ARGS_ERROR	"exit : too many arguments\n"
# define ERR_CMD_NOT_FOUND	" : command not found\n"

//		global var//
extern volatile int			g_exit_status;

typedef struct s_env_list
{
	struct s_env_list	*next;
	struct s_env_list	*prev;
	char				*name;
	char				*val;
	struct s_env		*env;
}				t_env_list;

typedef struct s_env
{
	char					**env;
	int						last_status;
	struct s_env_list		*head;
}				t_env;

typedef enum e_redirection_type
{
	NONE,
	INPUT,
	OUTPUT,
	HERE_DOC,
	APPEND,
}			t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type			type;
	const char					*payload;
	int							not_null;
	struct s_redirection		*next;
}				t_redirection;

typedef struct s_exec
{
	t_redirection				*redirection_list;
	char						*cmd;
	char						**option;
	struct s_exec				*next;
}				t_exec;

typedef struct s_exec_list
{
	struct s_exec		*exec;
	struct s_exec_list	*next;
	struct s_exec_list	*prev;
	int					pipe_fd[2];
	pid_t				pid;
	const char			*outfile;
	const char			*infile;
	int					fd_in;
	int					fd_out;
	char				*cmd;
	char				**args;
	int					cancel;
	t_redirection		*redirec_list;
}				t_exec_list;

//ft_expand.c
void						ft_expand(char **res, char **env_var_value, \
							int *i, int *j);
void						ft_expand_alloc(t_env *env, int *i, \
						int *j, char *str);
void						search_exit_status_alloc(t_env *env, \
						int *i, int *j);
void						search_exit_status(t_env *env, int *i, char **res);
//signal_handler.c
void						signal_listener(int sig_state);

//env.c
t_env						*list_env(char **env);
//t_env	*export_env(t_shell *shell, char **env_var);
void						free_env_list(t_env *env_list);
void						print_list(t_env *list_env);
//	init_expand.c
void						if_word(char **res, int *i, char *word, t_env *env);
void						if_expand(char **res, char *prompt, \
							int *i, t_env *env);
char						*ft_strcat_char(char *dest, char c);
char						*ft_strcat(char *dest, const char *src);
//void	commands(t_shell *shell);

/*	split_prompt.c	*/
t_exec						*split_prompt(char const *prompt, \
						char c, t_env *env);

//export.c
t_env						*sort_env(t_env *env, t_env *copy);
//echo.c
char						*get_env_value(char **env, char *var);
char						*extract_word(char *str);
//check_syntax.c
int							check_quotes(char *prompt);
int							check_syntax(char *prompt);
int							check_payload(t_exec **exec);
//utils.c
void						free_array(char **array);
int							is_in_quotes(char *cmd, int i);
int							has_quote(char *prompt, int j);
char						*handle_expand(char *prompt, t_env *env);
//               utils2.c
char						*get_command(char *cmd, int *i);
char						**get_option(char *cmd, int *i, t_env *env);
char						*ft_strcat(char *dest, const char *src);
t_redirection				*get_redirection(char *cmd);
//	utils3.c
int							ft_isspace(int c);
int							ft_strcmp(char *s1, char *s2);
char						*ft_strndup(const char *s, size_t n);
void						free_array(char **array);
char						*extract_word(char *str);
//	node_utils.c
t_exec						*create_new_node(void);
//	redirection_list.c
t_redirection				*redirection_list_new_node(void);
t_redirection				*redirection_list_last(t_redirection *lst);
t_redirection				*redirection_list_add_back(t_redirection *exec, \
					t_redirection *neww);
//	redirection_utils.c
void						exec_trim(char **line, char **res, int *i, int j);
void						trim_redirections(char **line);
void						pass_redirection_and_payload(char **line, int *i);
int							fill_redirection(t_redirection *redirection_list, \
								char *instruction_line);
int							fill_payload(t_redirection *tmp, \
								char *instruction_line);
//	redirection_utils2.c
void						trim_payload_quotes(char *option);
void						shift_str(char *str, int length);
//	ft_free.c
void						free_env(t_env *copy);
void						free_exec_list(t_exec **exec);
void						free_redirection_list(t_redirection **list);
void						free_readline(void);

/* builtin */
void						ft_echo(t_exec_list *exec);
void						ft_cd(char **path, t_env_list **env);
void						ft_pwd(void);
void						ft_export(t_env_list **env, char **args);
/* env */
void						ft_env(t_env_list *env);
void						update_env(t_env_list **env);
t_env_list					*find_env(t_env_list **head, char *name, int *plus);
void						append_val(t_env_list **elmt, char	*app_val, \
							t_env_list **head);
int							valid_name(char *name);
/* end env */
void						ft_unset(t_env_list	**env, char **my_var);
void						ft_exec(t_exec *exec, t_env *env);
void						ft_exit(t_exec_list *exec, t_env_list *env);
/* end builtin */
/* exec */

/* heredoc */

int							ft_here_doc(const char *delimiter);
void						del_curr_heredoc(void);

/* exec_utils.c */

char						*ft_get_path(char	*cmd, t_env_list	**envp);
char						**copy_tab(char	**env, int *size);
int							ft_strchr_pos(const char *s, int c);
int							count_params(char	**params);
char						**list_to_char(t_env_list **env);

int							check_redirection(t_exec_list **exec);
void						dup_in_out(t_exec_list *exec);
void						check_pipe(t_exec **exec, int in_parent, \
											int fd_last_pipe, int *pipe_fd);
/* linkedlist_utils 1 & 2*/

t_env_list					*new_env(char *name, char *value, t_env_list *prev);
void						add_end(t_env_list **env, t_env_list *new_elmt);
void						rm_elmt(t_env_list **env, t_env_list *elmt);
t_env_list					*find_elmt(t_env_list **env, char	*elmt);
t_env_list					*create_list_from_tab(char **env);
int							list_size(t_env_list *mylist);
void						free_list(t_env_list *list);
void						free_elmt(t_env_list **elmt);
t_env_list					*copy_list(t_env_list *env);
int							set_value(t_env_list **env, char *str);

/* EXEC NODE LIST (DOUBLE LINKED LIST)*/

t_exec_list					*get_exec_list(t_exec *exec);

/* trim_quotes.c */

void						is_a_quote(char c, int *state);
void						trim_quotes(char **option, t_env *copy);
void						trim_command_quotes(char *cmd, t_env *copy);
void						trim_payload_quotes(char *option);

/* free_exec_list.c */

void						free_exec_list(t_exec **exec);

/* check_quotes.c */

int							check_quotes(char *input);

/* env_variable_utils.c */

char						*keep_intact(char **input, int *i);
int							is_in_set_to_keep(char c);

/* ft_free_exec.c */

void						ft_free_str_list(char **str_list);
void						free_all_exit(t_exec_list *exec, t_env_list *env, \
								int exit_code);
void						free_child(char	**str_tab, t_exec_list *exec_list, \
								t_env_list *env_list, t_exec *exec);
void						close_all_fd(t_exec_list	**exec);
int							exec_builtin(t_exec_list *exec, t_env_list **env, \
								int in_child);
void						solo_builtins(t_exec_list *exec, t_env_list **env);

/* DEBUG */
char						**add_str(char **tab, char *elmt);
void						display_exec(t_exec_list *exec);
void						ft_close(int fd, const char *filename, \
								int pipe_entry);
int							ft_open(const char	*name, int trunc, int append);
int							check_builtin(t_exec_list *exec);
char						**get_args(t_exec *exec);
void						replace_abs_path(char	**str, t_env_list **env);
t_exec_list					*verif_exec(t_exec_list	*exec, t_env_list **env);

#endif
