/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:59:28 by pdelanno          #+#    #+#             */
/*   Updated: 2023/06/08 12:01:15 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <signal.h>

typedef struct s_token 
{
    char    *str;
    int     type;
    struct s_token *next;
    struct s_token *prev;
} t_token;

typedef struct s_env
{
    char *value;
    struct s_env *next;
} t_env;

int	ft_strcmp(const char *str1, const char *str2);

#endif
