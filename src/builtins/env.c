/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:35:46 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/08 22:00:12 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env(t_shell *cmd)
{
	t_env	*tmp;

	tmp = cmd->env_lst;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->full_string); // printf or stderr ?
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
