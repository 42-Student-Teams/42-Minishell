/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:35:39 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/06/30 16:40:14 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(void)
{
	char	*input;
	t_list data;

	while (42)
	{
		input = readline("Minishell$ ");
		if (input == NULL || ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		//parser
		// Add the input to the history
		add_history(input);
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_lst	lst;

	(void)ac;
	(void)av;
	(void)env;

	lst = (t_lst){};
	get_data(&lst);
	init_minishell();
	// free_all();
	return (0);
}
