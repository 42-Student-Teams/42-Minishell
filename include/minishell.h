/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:23:06 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/07/20 16:39:52 by lsaba-qu         ###   ########.fr       */
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
}	t_global;

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

t_global	g_shell;

t_list	*get_data(t_list *ptr);
int		free_all(void);
void	init_minishell(void);

// --------- ENV ---------
int		init_env(t_shell *shell, char **env);
void	print_env(t_env *env);

// --------- UTILS ---------
void	free_split(char **split);

// --------- BUILTINS ---------
int		test_builtins(char *input);


// CD
int		my_cd(char **args);
int		exec_cd(char *path);

// ECHO
void	my_echo(char **args);

#endif