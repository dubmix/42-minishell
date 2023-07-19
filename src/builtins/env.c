/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:35:46 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/19 12:15:41 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int env(t_shell *cmd)
{
    t_shell **tmp;
    // t_env **tmp
    // tmp = cmd->env_lst;
    tmp = &cmd;
    while((*tmp)->env_lst)
    {
        printf("%s=%s\n", (*tmp)->env_lst->name, (*tmp)->env_lst->value);
        (*tmp)->env_lst = (*tmp)->env_lst->next;
    }
    return (EXIT_SUCCESS);
}