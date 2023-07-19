/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:35:46 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/19 11:13:12 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int env(t_shell *cmd)
{
    t_shell **tmp;

    tmp = &cmd;
    while((*tmp)->env_lst)
    {
        printf("%s=%s\n", (*tmp)->env_lst->name, (*tmp)->env_lst->value);
        (*tmp) = (*tmp)->env_lst->next;
    }
    return (EXIT_SUCCESS);
}