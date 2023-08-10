/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:56:50 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/10 17:08:40 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

// void	sigint_heredoc(int sig)
// {
// 	ioctl(STDIN_FILENO, TIOCSTI, "");
// 	g_xcode = 130;
// 	(void)sig;
// }
// ISSUE !!!!!
void sigint_heredoc(int sig)
{
    (void)sig;
	write(2, "\n", 1);
	g_xcode = 130;
}

void	sigint_child(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	sigint_handler(int sig)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_xcode = 130;
	(void)sig;
}

void	sigquit_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	g_xcode = 131;
}
