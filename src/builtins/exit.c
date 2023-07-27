/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:14:26 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/19 11:13:14 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exxit(t_shell *cmd)
{
	//char **str;

	printf("exit");
	cmd->exit_flag = 1;
	if (cmd->cmd_lst->command[1] && cmd->cmd_lst->command[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	//str = ft_arrdup(single_cmd->);
	//free_env(env);
	get_exit_code();
	return (EXIT_SUCCESS);
}

void get_exit_code(void)
{
	int exit_code;

	// if (str[1] == '\0')
	// 	exit_code = 0;
	// if (is_only_digits(str[1]) != 0)
	// 	exit_code = ft_atoi(str[1]);
	// else
	// {
	// 	printf("minishell: exit: %s: numeric argument required\n");
	exit_code = 0;
	// }		
	//free_arr(str);

	exit(0); //child process??
}

// int is_only_digits(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] < 48 || str[i] > 57)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// void	free_all()
// {

// }