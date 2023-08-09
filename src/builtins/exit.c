/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:14:26 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/08 22:01:31 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exxit(t_shell *cmd)
{
	printf(EXIT_MSG);
	if (cmd->cmd_lst->command[1] && cmd->cmd_lst->command[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
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
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(command[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
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
