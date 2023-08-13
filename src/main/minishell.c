/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:16:23 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/13 14:46:10 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_xcode = 0;

void	init_shell(t_shell *cmd)
{
	cmd->nb_of_heredocs = 0;
	cmd->nb_of_pipes = 0;
	cmd->cmd_alloc = 0;
	cmd->tok_alloc = 0;
	cmd->words_per_pipe_alloc = 0;
	cmd->heredoc_arr = NULL;
	cmd->heredoc_string = NULL;
	cmd->pid_alloc = 0;
}

int	minishell_start_null(t_shell *cmd)
{
	free(cmd->line);
	ft_putstr_fd(EXIT_MSG, STDERR_FILENO);
	free_all_inside_loop(cmd);
	g_xcode = 0;
	return (-1);
}

int	minishell_start(t_shell *cmd)
{
	init_signals();
	init_shell(cmd);
	cmd->line = readline(READLINE_MSG);
	add_history(cmd->line);
	if (cmd->line == NULL)
		return (minishell_start_null(cmd));
	clear_line_space(cmd);
	if (ft_strncmp(cmd->line, "", ft_strlen(cmd->line)))
	{
		cmd->tok_lst = tokenization(cmd);
		expand_var(cmd);
		if (!parser(cmd) || g_xcode == 130)
		{
			free_all_inside_loop(cmd);
			return (1);
		}
		g_xcode = 0;
		g_xcode = pre_executor(cmd);
		free_all_inside_loop(cmd);
	}
	return (0);
}

t_shell	*main_bis(t_shell *cmd)
{
	cmd = malloc(sizeof(t_shell));
	if (!cmd)
	{
		ft_putstr_fd("Malloc cmd allocation failed", STDERR_FILENO);
		exit(1);
	}
	cmd->env_alloc = 0;
	return (cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*cmd;
	int		check;

	check = 42;
	argv = NULL;
	cmd = NULL;
	if (argc != 1)
		ft_putstr_fd("Error, program should not take any arguments\n",
			STDERR_FILENO);
	else
	{
		cmd = main_bis(cmd);
		cmd->env_lst = init_envp(envp, cmd);
		while (42)
		{
			check = minishell_start(cmd);
			if (check < 0)
				break ;
		}
		rl_clear_history();
		free_all_exit(cmd);
		free(cmd);
	}
	return (g_xcode);
}
