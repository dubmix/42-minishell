/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:56:50 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/05 22:04:40 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_signals = 130;
}

void sigint_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0); // TO PUT AGAIN
	rl_redisplay();
	(void) sig;
}

void sigquit_handler(int sig)
{
	printf("Quit: %d\n", sig);
}

void init_signals()
{
	// rl_event_hook = event; // TO PUT AGAIN
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}