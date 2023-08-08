/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:56:50 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/08 20:25:54 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_heredoc(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
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
	// rl_replace_line("", 0); // to put again
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

void	sigterm_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("Exit\n", STDERR_FILENO);
	//rl_replace_line("", 0); // to be put again
	rl_on_new_line();
	rl_redisplay();
	exit(0);
}
