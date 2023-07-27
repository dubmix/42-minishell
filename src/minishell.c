/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:16:23 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/23 10:29:41 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* alloc shell struc
initialize the environnement (envp)
 readline(real function) store in shell->line_command
 store in cmd->tok_lst all the tokens
 */

int	minishell_start(char **envp)
{
	t_shell	*cmd;

	(void)envp;
	cmd = malloc(sizeof(t_shell));
	if (!cmd)
		return (0);
	cmd->exit_flag = 0;
	cmd->env_lst = init_envp(envp, cmd);
	while (1)
	{
		//printf("1 %d\n", ft_lstsize_test((cmd->env_lst)));
		cmd->line_command = readline("Minishell >");
		cmd->tok_lst = tokenization(cmd);
		add_history(cmd->line_command);
		expand_var(cmd);
		parser(cmd);
		pre_executor(cmd);
		if (cmd->exit_flag == 1)
        	exit(exit_code); // pq ca marche pas ca??
		//printf("2 %d\n", ft_lstsize_test((cmd->env_lst)));
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
