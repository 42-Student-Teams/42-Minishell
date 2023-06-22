/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:35:39 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/06/22 17:00:34 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	char input[100];  // Assuming the input will be at most 100 characters long

	while (1)
	{
		printf("Minishell~$: ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("Error reading input.\n");
			break ;
		}
        // Remove the newline character from the end of the input
		input[strcspn(input, "\n")] = '\0';
        // Process the command here
		if (ft_strcmp(input, "exit") == 0)
			break ;
	}
	//Finish programme with free function
	return (0);
}
