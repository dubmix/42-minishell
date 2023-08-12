/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:35:46 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/12 09:47:40 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env(t_shell *cmd)
{
	t_env	*tmp;

	if (cmd->cmd_lst->command[1] != NULL)
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(cmd->cmd_lst->command[1], STDERR_FILENO);
		ft_error(cmd, " No such file or directory\n", 127);
		return (EXIT_FAILURE);
	}
	else
	{
		tmp = cmd->env_lst;
		while (tmp != NULL)
		{
			if (ft_strchr(tmp->full_string, '=') != NULL)
				printf("%s\n", tmp->full_string);
			tmp = tmp->next;
		}
	}
	return (EXIT_SUCCESS);
}
