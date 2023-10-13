/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:01:25 by bverdeci          #+#    #+#             */
/*   Updated: 2023/10/13 15:52:44 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "define.h"

typedef struct s_parser
{
	char			*cmd;
	char			**args;
	char			*fullpath;
	int				infile;
	int				outfile;
	int				redirect;
	int				pid;
	int				nb_args;
	int				index;
	struct s_parser	*next;
}	t_parser;

/*
    Représente un token généré par l'analyseur lexical avec ses informations.
    
    - str : Chaîne de caractères représentant le contenu du token.
    - type : Type du token (identifiant, opérateur, etc.).
*/
typedef struct s_token
{
	char				*str;
	enum e_token_type	type;
	struct s_token		*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_global
{
	int				status;
	int				nb_cmds;
	char			**env_copy;
	struct s_env	*env_l;
	struct s_env	*vars;
}	t_global;

typedef struct s_shell
{
	char			*input;
	pid_t			pid;
}	t_shell;

#endif