/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:35:10 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/19 11:13:05 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int unset_error(char **str, t_shell **tmp)
{
    int i;

    i = 0;
    if (str[1] == '\0')
    {
        printf("minishell: unset: not enough arguments");
        return (1);
    }
    while (str[1][i])
    {
        if (str[1][i] == '/')
        {    
            printf("minishell: unset: %s: not a valid identifier", str[1]);
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}

int unset(t_shell *cmd)
{
    t_shell **tmp;
    char       **str;

    tmp = &cmd;
    if (ft_findchar((*tmp)->tok_lst->command, '=' == 0))
    {
        printf("minishell: unset: not a valid identifier");
        return (EXIT_FAILURE);
    }
    if (unset_error(str) == 1)
        return (EXIT_FAILURE);
    while ((*tmp)->env_lst)
    {
        if ((*tmp)->env_lst->name == (*tmp)->tok_lst->command)
        {
            deleteNode(&(cmd->env_lst), (*tmp)->env_lst);
            break ;
        }
        (*tmp)->env_lst == (*tmp)->env_lst->next;
    }
    return (EXIT_SUCCESS);
}