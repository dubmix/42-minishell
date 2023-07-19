/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:55:39 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/19 10:50:45 by edrouot          ###   ########.fr       */
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

    newline = 0;
    i = 1;
    if (args_nb(args) > 1)
    {
        if (ft_strncmp(args[i], "-n", 2) == 0)
        {
            newline = 1;
            i++;
        }
        while(args[i])
        {
            printf("%s", args[i]);
            if (args[i + 1] != NULL)
                write(1, " ", 1);
            i++;
        }
    }
    if (newline == 1)
        write(1, "\n", 1);
}