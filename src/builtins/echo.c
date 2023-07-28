/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:55:39 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/28 09:02:21 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    echo(char **cmd)
{
    int newline;
    int i;

    newline = 1;
    i = 1;
    if (cmd != NULL)
    {   
        if (ft_strncmp(cmd[1], " ", 1) == 0)
            i++;
        if (ft_strncmp(cmd[i], "-n", 2) == 0)
        {
            newline = 0;
            i++;
        }
        while(cmd[i] != NULL)
        {
            ft_putstr_fd(args[i], STDOUT_FILENO);
            if (args[i + 1] != NULL) // apparently is printing the space when should not 
                printf(" ");
            i++;
        }
    }
    if (newline == 1)
        printf("\n");
}