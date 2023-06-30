/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:23:06 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/06/30 13:52:07 by lsaba-qu         ###   ########.fr       */
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

/*
** Faire categorie par structure et mettre en commentaire
*/

typedef struct s_env t_env;
typedef struct s_lst t_lst;
typedef struct s_node t_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_node
{
	char	*data;
	int		type;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;


typedef struct s_lst
{
	t_node	*start;
	t_node	*end;
	int		size;
}	t_lst;

enum e_type
{
	PIPE,	// |
	SEMICOLON,	// ;
	REDIR_IN,	// <
	REDIR_OUT,	// >
	REDIR_HEREDOC, // <<
	REDIR_APPEND, // >>
	CMD,	// "ls -l"
	END,	// \0
};

t_list	*get_data(t_list *ptr);
int		free_all(void);
void	init_minishell(void);

#endif