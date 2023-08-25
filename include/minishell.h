/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:23:06 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/25 16:11:55 by bverdeci         ###   ########.fr       */
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

t_list		*get_data(t_list *ptr);
int			free_all(void);
void		init_minishell(void);
void		prepare_cmd(t_shell *shell, t_global *g_shell);

// ------- PARSING -------
t_token		*ft_lstnewtoken(enum e_token_type type, char *str);
int			lexer(t_token **token, char *s, int index);
int			handle_string(t_token **token, char *s, int index);
int			insert_token_into_lst(enum e_token_type t, char *value,
				t_token **lst, int i);
// ------- PARSING.2 -------
void		parser(t_parser **cmds, t_token *tokens);
char		*trim_matching_quotes(char *str, char quote);

// EXECUTION
void		execution(t_parser **cmds, t_global *g_shell);

// --------- ENV ---------
void		print_env(t_env *env);
void		copy_env(char **env, t_global *g_shell);
int			env_list(t_env **env_l, char **env_copy);
t_env		*new_el(char *key_value);

// --------- UTILS ---------
void		free_split(char **split);
void		rl_replace_line(const char *text, int clear_undo);
int			strtab_len(char **str_tab);
int			ft_isspace(char c);
void		printinfo(const char *format, ...);

// --------- SIGNALS ---------
void		signal_handler(int signal);

// --------- TERMIOS ---------
void		init_termios(void);

// --------- BUILTINS ---------
int			builtins(char *input, t_global *g_shell);
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

#endif