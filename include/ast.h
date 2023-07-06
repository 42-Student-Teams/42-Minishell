#ifndef AST_H
# define AST_H

enum e_type
{
	BUILTIN, // echo, cd, pwd, export, unset, env, exit
	PIPE,	// |
	AND,	// &
	OR,		// ||
	REDIR_IN,	// <
	REDIR_OUT,	// >
	REDIR_HEREDOC, // <<
	REDIR_APPEND, // >>
	CMD,	// "ls -l"
	END,	// \0
};


typedef struct s_tree
{
	char			*cmd;
	enum e_type		type;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;


#endif