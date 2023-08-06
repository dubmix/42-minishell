/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:16:23 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/05 15:09:25 by edrouot          ###   ########.fr       */
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
}

int	minishell_start(char **envp, char **argv)
{
	t_shell	*cmd;

	cmd = malloc(sizeof(t_shell));
	argv = NULL;
	(void)envp;
	if (!cmd)
		return (0);
	cmd->exit_code = 0;
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
			cmd->tok_lst = tokenization(cmd);
			expand_var(cmd);
			parser(cmd);
			pre_executor(cmd);
			if (g_signals != 0)
				cmd->exit_code = g_signals;
			free_all(cmd, 4);
		}
	}
	rl_clear_history();
	free_all(cmd, 3);
	free(cmd);
	return (0);
}


/* launch minishell */
int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		printf("Error, this program should not take any arguments");
	else
		minishell_start(envp, argv);
	return (0);
}
