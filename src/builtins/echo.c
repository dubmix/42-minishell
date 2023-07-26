/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:55:39 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/19 15:13:40 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int     args_nb(char **args)
{
    int nb;

    nb = 0;
    while (args[nb])
        nb++;
    return (nb);
}

void    echo(char **args)
{
    int newline;
    int i;

    newline = 1;
    i = 1;
    if (args_nb(args) > 1)
    {
        if (ft_strncmp(args[i], "-n", 2) == 0) // one n or multiple should be equal to -n 
        {
            newline = 0;
            i++;
        }
        while(args[i])
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