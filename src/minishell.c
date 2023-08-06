/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:16:23 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/06 17:34:02 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signals = 0;

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
			printf("exit\n");
			exit(0);
		}
		if (ft_strncmp(cmd->line, "", ft_strlen(cmd->line)) != 0)
		{
			add_history(cmd->line);
			clear_line_space(cmd->line, cmd);
			cmd->tok_lst = tokenization(cmd);
			expand_var(cmd);
			parser(cmd);
			if (g_signals != 0)
				cmd->exit_code = g_signals;
			else
				pre_executor(cmd);
			free_all(cmd, 4);
		}
	}
	return (0);
}

	// rl_clear_history();
	// free_all(cmd, 5);
	// free(cmd);

int	main(int argc, char **argv, char **envp)
{
	t_shell	*cmd;

	argv = NULL;
	if (argc != 1)
		printf("Error, program should not take any arguments\n");
	else
	{
		cmd = malloc(sizeof(t_shell));
		if (!cmd)
		{
			ft_putstr_fd("Malloc cmd allocation failed", STDERR_FILENO);
			exit(1);
		}
		cmd->exit_code = 0;
		init_signals();
		cmd->oldpwd = (char *)malloc(sizeof(char *));
		cmd->oldpwd = ft_strdup("");
		cmd->env_lst = init_envp(envp, cmd);
		minishell_start(cmd);
	}
	return (0);
}
