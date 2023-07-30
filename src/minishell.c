/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:16:23 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/30 14:37:51 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* alloc shell struc
initialize the environnement (envp)
 readline(real function) store in shell->line_command
 store in cmd->tok_lst all the tokens
 */

void	init_shell(t_shell *cmd)
{
	cmd->nb_of_heredocs = 0;
	cmd->nb_of_pipes = 0;
	cmd->exit_flag = 0;
}

int	minishell_start(char **envp)
{
	t_shell	*cmd;

	cmd = malloc(sizeof(t_shell));
	init_shell(cmd);
	(void)envp;
	if (!cmd)
		return (0);
	cmd->env_lst = init_envp(envp, cmd);
	while (1)
	{
		// printf("1 %d\n", ft_lstsize_test((cmd->env_lst)));
		cmd->line = readline("Minishell >");
		cmd->tok_lst = tokenization(cmd);
		add_history(cmd->line);
		expand_var(cmd);
		parser(cmd);
		pre_executor(cmd);
		// if (cmd->exit_flag == 1)
        // 	exit(exit_code); // pq ca marche pas ca??
	}
}


/* launch minishell */
int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		printf("Error, this program should not take any arguments");
	else
		minishell_start(envp);
	return (0);
}
