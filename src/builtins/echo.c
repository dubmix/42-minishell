/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:55:39 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/07 13:38:06 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo(char **commands, t_shell *cmd)
{
	int	newline;
	int	i;
	int	k;
	int	check;

	k = 0;
	newline = 1;
	i = 1;
	if (commands != NULL)
	{
		if (ft_strncmp(commands[i], " ", ft_strlen(commands[i])) == 0)
			i++;
		else if (commands[i][0] == '-')
		{
			k = i;
			i = find_new_line(commands, i);
			if (k != i)
				newline = 0;
		}
		check = echo_sub(commands, i);
	}
	if ((newline == 1 && check == 1) || cmd->nb_of_heredocs != 0)
		printf("\n");
}

int	echo_sub(char **cmd, int i)
{
	int	check;

	check = 0;
	while (cmd[i] != NULL)
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		check = 1;
		i++;
	}
	return (check);
}

int	find_new_line(char **cmd, int i)
{
	int	k;

	k = 0;
	while (cmd[i] != NULL)
	{
		if (cmd[i][k] == '-')
		{
			k++;
			while (cmd[i][k] == 'n')
				k++;
			if (cmd[i][k] != '\0')
				return (i);
			i++;
			k = 0;
		}
		else if (cmd[i][k] == ' ')
			i++;
		if (cmd[i][k] != '-' && cmd[i][k] != ' ')
			return (i);
	}
	return (i);
}
