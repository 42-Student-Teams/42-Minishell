/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:23:06 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/06 12:09:11 by bverdeci         ###   ########.fr       */
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
# include "ast.h"

# define SUCCESS 0
# define ERROR 1

typedef struct s_global
{
	int		status;
	char	**env_copy;
}	t_global;

// VARIABLE GLOBALE 
t_global	g_shell;

/*
** Faire categorie par structure et mettre en commentaire
*/

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char			*input;
	struct s_env	*env;
	pid_t			pid;
}	t_shell;

t_list	*get_data(t_list *ptr);
int		free_all(void);
void	init_minishell(void);

// --------- ENV ---------
int		init_env(t_shell *shell);
void	print_env(t_env *env);
void	copy_env(char **env);

// --------- UTILS ---------
void	free_split(char **split);
void	rl_replace_line(const char *text, int clear_undo);

// --------- SIGNALS ---------
void	signal_handler(int signal);

// --------- TERMIOS ---------
void	init_termios(void);

// --------- BUILTINS ---------
int		test_builtins(char *input);

// CD
int		my_cd(char **args);
int		exec_cd(char *path);

// ECHO
void	my_echo(char **args);

// PWD
void	my_pwd(void);

#endif