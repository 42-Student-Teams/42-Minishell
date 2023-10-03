/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:23:06 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/03 17:55:50 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "define.h"
# include "struct.h"
# include "errno.h"
# include <sys/ioctl.h>

int			g_status;

t_list		*get_data(t_list *ptr);
int			free_all(void);
void		init_minishell(void);
void		prepare_cmd(t_shell *shell, t_global *g_shell);

// ------- TOKENIZER -------
t_token		*ft_lstnewtoken(enum e_token_type type, char *str);
char		*change_str(char *str, t_global *g_shell);
int			lexer(t_global *g_shell, t_token **token, char *s, int index);
int			check_quotes(char *str);
int			check_next_quote(char *str, char c, int *i);
int			new_len(char *str, t_env *env_l, t_env *vars);
void		new_str(char *str, char *new, t_env *env_l, t_env *vars);
void		add_variable(char *new, char *var, t_env *env, int *i);
int			len_value(char *var, t_env	*vars);
int			handle_string(t_global *g_shell, t_token **token,
				char *s, int index);
int			insert_token_into_lst(enum e_token_type t, char *value,
				t_token **lst, int i);
// ------- PARSING -------
void		parser(t_parser **cmds, t_token *tokens, t_global *g_shell);

// ------- PARSING UTILS -------
char		*trim_matching_quotes(char *str, char quote);
void		trim_first_quote(char *command);

// COMMANDS
void		lst_add_cmd(t_parser **cmds, t_parser *cmd);
void		add_cmd_args(t_parser **cmd, t_token **tokens);
void		init_cmd(t_parser **cmd);
t_parser	*create_cmd(t_token **tokens);

// HEREDOC
int			heredoc(char *delimiter);
t_parser	*create_heredoc(t_token *tokens, t_global *g_shell);
int			add_heredoc_args(t_parser **cmd, t_token *tokens);

// EXECUTION
void		execution(t_parser **cmds, t_global *g_shell);

// EXECUTION - CMD
void		exec_cmd(t_parser *cmd, t_global *g_shell, int i);

// EXECUTION - PROCESS 
void		process_exec(t_parser *cmd, t_global *g_shell);
void		prepare_exec(t_parser *tmp, int **pipes, int *i, int nb_cmds);
void		waiting_pid(t_parser *cmds, int *status);
void		ft_process(t_parser *cmds, t_parser *tmp,
				int **pipes, t_global *g_shell);

// EXECUTION - UTILS
char		**get_paths(t_env *env);
int			parser_len(t_parser *lst);
char		**from_chaintotab(t_env *env);
int			**create_pipes(int nb_cmds);

// --------- ENV ---------
void		print_env(t_env *env);
void		copy_env(char **env, t_global *g_shell);
int			env_list(t_env **env_l, char **env_copy);
t_env		*new_el(char *key_value);

// --------- UTILS ---------
void		free_strtab(char **split);
void		rl_replace_line(const char *text, int clear_undo);
int			strtab_len(char **str_tab);
int			ft_isspace(char c);
void		printinfo(const char *format, ...);
void		throw_error(char *str);
void		free_pipes(int **pipes, int len);

// --------- SIGNALS ---------
void		signal_handler(int signal);
void		signal_cmd(int signal);
void		signal_heredoc(int signal);

// --------- TERMIOS ---------
int			init_termios(int mode);

// --------- BUILTINS ---------
void		builtins(t_parser *cmd, t_global *g_shell);
int			is_builtin(char *cmd);
int			is_spe_builtin(char *cmd);
int			my_cd(char **args, t_env **env_l);
int			exec_cd(char *path);
int			my_echo(char **args);
int			my_pwd(void);
int			my_env(char **args, t_global *g_shell);
int			my_export(char **args, t_env **env_l);
int			is_equal_in(char *s);
int			key_in_env(char *key, t_env *env_l);
int			my_unset(t_env **env_l, char **args, int i);
int			my_exit(char **args);
int			my_vars(char **args, t_env **env_l);

#endif