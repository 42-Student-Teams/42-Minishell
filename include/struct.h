/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:01:25 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/16 12:53:35 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "define.h"

/*
    - fullcmd : Tableau de chaînes représentant la commande et ses arguments.
    - fullpath : Tableau de chaînes contenant les chemins complets associés à chaque commande.
    - infile : Descripteur de fichier pour l'entrée (stdin) de la commande.
    - outfile : Descripteur de fichier pour la sortie (stdout) de la commande.
    - redirect : Indicateur pour la redirection de flux (peut être un booléen).
    - pid : ID du processus associé à la commande.
    - nb_args : Nombre total d'arguments dans la commande.
    - next : Pointeur vers la prochaine structure de commande (dans une liste chaînée).
*/
typedef struct s_parser
{
	char			**fullcmd;
	char			**fullpath;
	int				infile;
	int				outfile;
	int				redirect;
	int				pid;
	int				nb_args;
	struct s_cmd	*next;
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
	char			**env_copy;
	struct s_env	*env_l;
}	t_global;

typedef struct s_shell
{
	char			*input;
	pid_t			pid;
}	t_shell;

#endif