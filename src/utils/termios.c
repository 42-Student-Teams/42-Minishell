/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 22:01:17 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/05 18:12:02 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_termios(int mode)
{
	struct termios		termios;
	struct sigaction	s;

	if (mode == 1)
		s.sa_handler = &signal_handler;
	if (mode == 2)
		s.sa_handler = &signal_cmd;
	if (mode == 3)
		s.sa_handler = &signal_heredoc;
	sigaction(SIGINT, &s, NULL);
	sigaction(SIGQUIT, &s, NULL);
	if (tcgetattr(STDIN_FILENO, &termios) == -1)
		return (-1);
	termios.c_lflag &= ~ECHOCTL;
	if ((tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios)) == -1)
		return (-1);
	return (0);
}
