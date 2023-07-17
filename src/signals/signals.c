/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:56:50 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/17 11:30:08 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//return (EXIT_SUCCESS);
	}
}

void sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		write(1, "exit", 4);
		write(1, "\n", 1);
		//return (EXIT_SUCCESS);
	}
}

void init_signals()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
