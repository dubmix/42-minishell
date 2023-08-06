/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:16:23 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/06 11:20:13 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

/* alloc shell struc
initialize the environnement (envp)
 readline(real function) store in shell->line_command
 store in cmd->tok_lst all the tokens
 */
int	g_signals = 0;

void	init_shell(t_shell *cmd)
{
	cmd->nb_of_heredocs = 0;
	cmd->nb_of_pipes = 0;
	cmd->oldpwd = (char *)malloc(sizeof(char *));
	cmd->oldpwd = ft_strdup("");
}

void	clear_line_space(char *line, t_shell *cmd)
{
	int i;
	char *temp;

	temp = ft_strdup(line);
	i = ft_strlen(line) - 1;
	while (i > 0)
	{
		if (temp[i] != ' ')
			break ;
		i--;
	}
	i++;
	free(cmd->line);
	cmd->line = ft_substr(temp, 0, i);
	free(temp);
}

int	minishell_start(char **envp)
{
	t_shell	*cmd;

	cmd = malloc(sizeof(t_shell));
	if (!cmd)
	{
		ft_putstr_fd("Malloc cmd allocation failed", STDERR_FILENO);
		exit(1);
	}
	cmd->exit_code = 0;
	init_signals();
	cmd->env_lst = init_envp(envp, cmd);
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
	rl_clear_history();
	free_all(cmd, 5);
	free(cmd);
	return (0);
}

/* launch minishell */
int	main(int argc, char **argv, char **envp)
{
	argv = NULL;
	if (argc != 1)
		printf("Error, this program should not take any arguments, %s", argv[0]);
	else
		minishell_start(envp);
	return (0);
}
