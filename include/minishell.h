/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:23:06 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/19 16:17:44 by bverdeci         ###   ########.fr       */
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

t_list	*get_data(t_list *ptr);
int		free_all(void);
void	init_minishell(void);

// --------- ENV ---------
void	print_env(t_env *env);
void	copy_env(char **env, t_global *g_shell);
int		env_list(t_env **env_l, char **env_copy);
t_env	*new_el(char *key_value);

// --------- UTILS ---------
void	free_split(char **split);
void	rl_replace_line(const char *text, int clear_undo);
int		strtab_len(char **str_tab);

// --------- SIGNALS ---------
void	signal_handler(int signal);

// --------- TERMIOS ---------
void	init_termios(void);

// --------- BUILTINS ---------
int		builtins(char *input, t_global *g_shell);

// CD
int		exec_cd(char *path);
int		my_cd(char **args, t_env **env_l);

// ECHO
int		my_echo(char **args);

// PWD
int		my_pwd(void);

// ENV
int		my_env(char **args, t_global *g_shell);

// EXPORT
int		my_export(char **args, t_env **env_l);
int		is_equal_in(char *s);
int		key_in_env(char *key, t_env *env_l);

// UNSET
int		my_unset(t_env **env_l, char **args, int i);

// EXIT
int		my_exit(char **args);

#endif