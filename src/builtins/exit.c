/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:14:26 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/07 16:31:14 by edrouot          ###   ########.fr       */
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

void	get_exit_code(char **command)
{
	g_xcode = 0;
	if (!command[1])
		g_xcode = 0;
	else if (is_only_digits(command[1]) == 0)
		g_xcode = ft_atoi(command[1]);
	else
	{
		printf("minishell: exit: %s: numeric argument required\n", command[1]);
		g_xcode = 255;
	}
	exit(g_xcode);
}

int	is_only_digits(char *str)
{
	int	i;

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
