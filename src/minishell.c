/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:16:23 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/08 23:17:39 by emiliedrouo      ###   ########.fr       */
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
	while (1)
	{
		init_shell(cmd);
		init_signals();
		cmd->line = readline("Minishell >");
		if (cmd->line == NULL)
		{
			free(cmd->line);
			ft_putstr_fd("exit\n", STDERR_FILENO);
			g_xcode = 130;
			return (-1);
		}
		add_history(cmd->line);
		if (!ft_strncmp(cmd->line, "echo $?", 7))
		{
			ft_putnbr_fd(g_xcode, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			g_xcode = 0;
		}
		else if (ft_strncmp(cmd->line, "", ft_strlen(cmd->line)))
		{
			g_xcode = 0;
			clear_line_space(cmd->line, cmd);
			cmd->tok_lst = tokenization(cmd);
			expand_var(cmd);
			parser(cmd);
			if (g_xcode == 0)
				g_xcode = pre_executor(cmd);
			free_all(cmd, 4);
		}
	}
	return (0);
}


int	main(int argc, char **argv, char **envp)
{
	t_shell	*cmd;
	int check;

	check = 42;
	(void)argv; // to put again argv = NULL;
	if (argc != 1)
		ft_putendl_fd("Error, program should not take any arguments\n", STDERR_FILENO);
	else
	{
		cmd = malloc(sizeof(t_shell));
		if (!cmd)
		{
			ft_putstr_fd("Malloc cmd allocation failed", STDERR_FILENO);
			exit(1);
		}
		cmd->env_lst = init_envp(envp, cmd);
		while (check > 0)
		{
			check = minishell_start(cmd);
		}
		clear_history();
		free_all(cmd, 5);
		free(cmd);
	}
	return (0);
}
