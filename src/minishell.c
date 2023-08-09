/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:16:23 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/09 17:00:48 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_xcode = 0;

void	init_shell(t_shell *cmd)
{
	cmd->nb_of_heredocs = 0;
	cmd->nb_of_pipes = 0;
}

void	clear_line_space(char *line, t_shell *cmd)
{
	int		i;
	char	*temp;
	int		j;

	j = 0;
	temp = ft_strdup(line);
	i = ft_strlen(line) - 1;
	while (i > 0)
	{
		if (temp[i] != ' ')
			break ;
		i--;
	}
	while (temp[j] != '\0' && temp[j] == ' ')
		j++;
	i++;
	free(cmd->line);
	cmd->line = ft_substr(temp, j, i);
	free(temp);
}

int	minishell_start(t_shell *cmd)
{
	init_signals();
	init_shell(cmd);
	cmd->line = readline(READLINE_MSG);
	add_history(cmd->line);
	if (cmd->line == NULL)
	{
		free(cmd->line);
		ft_putstr_fd(EXIT_MSG, STDERR_FILENO);
		free_all(cmd, 4);
		g_xcode = 130;
		return (-1);
	}
	clear_line_space(cmd->line, cmd);
	if (!ft_strncmp(cmd->line, "echo $?", 7))
	{
		ft_putnbr_fd(g_xcode, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		g_xcode = 0;
	}
	else if (ft_strncmp(cmd->line, "", ft_strlen(cmd->line)))
	{
		g_xcode = 0;
		cmd->tok_lst = tokenization(cmd);
		expand_var(cmd);
		parser(cmd);
		if (g_xcode == 0)
			g_xcode = pre_executor(cmd);
		free_all(cmd, 4);
	}
	return (0);
}


int	main(int argc, char **argv, char **envp)
{
	t_shell	*cmd;
	int check;

	check = 42;
	argv = NULL;
	if (argc != 1)
		ft_putstr_fd("Error, program should not take any arguments\n", STDERR_FILENO);
	else
	{
		cmd = malloc(sizeof(t_shell));
		if (!cmd)
		{
			ft_putstr_fd("Malloc cmd allocation failed", STDERR_FILENO);
			exit(1);
		}
		cmd->env_lst = init_envp(envp, cmd);
		while (42)
		{
			check = minishell_start(cmd);
			if (check < 0)
				break ;
		}
		rl_clear_history();
		free_all(cmd, 5);
		free(cmd);
	}
	return (g_xcode);
}
