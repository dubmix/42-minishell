/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:14:26 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/02 09:46:00 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exxit(t_shell *cmd)
{
	printf("exit\n");
	if (cmd->cmd_lst->command[1] && cmd->cmd_lst->command[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	get_exit_code(cmd->cmd_lst->command);
	return (EXIT_SUCCESS);
}

void get_exit_code(char **command)
{

	// if (str[1] == '\0')
	// 	exit_code = 0;
	// if (is_only_digits(str[1]) != 0)
	// 	exit_code = ft_atoi(str[1]);
	// else
	// {
	// 	printf("minishell: exit: %s: numeric argument required\n");
	g_exit_code = 0;
	// }		
	//free_arr(str);

	exit(0); //child process??
	if (!command[1])
		exit_code = 0;
	else if (is_only_digits(command[1]) == 0)
		exit_code = ft_atoi(command[1]);
	else
	{
		printf("minishell: exit: %s: numeric argument required\n", command[1]);
		exit_code = 255;
	}		
	//free_all(command);
	write(1, "k", 1);
	exit(exit_code);
}

int is_only_digits(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
	}
	return (0);
}