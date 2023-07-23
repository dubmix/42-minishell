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
	cmd->env_lst = init_envp(envp, cmd);
	while (1)
	{
		cmd->line_command = readline("Minishell >");
		cmd->tok_lst = tokenization(cmd);
		expand_var(cmd);
		parser(cmd);
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
