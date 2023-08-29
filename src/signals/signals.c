/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:18:23 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/29 19:16:54 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

// static	void	heredoc_sigint_handler(int status __attribute__((unused)))
// {
// 	write(STDOUT_FILENO, "\n", 1);
// 	exit(130);
// }

// void	set_heredoc_signals(void)
// {
// 	static struct sigaction	act_sigint
// 		= {.sa_handler = heredoc_sigint_handler, .sa_flags = SA_RESTART};

// 	signal(SIGQUIT, SIG_IGN);
// 	sigfillset(&act_sigint.sa_mask);
// 	sigaction(SIGINT, &act_sigint, NULL);
// }


