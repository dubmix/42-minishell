/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:16:23 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/19 11:22:50 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int minishell_start(char **envp)
{
    (void)envp;
    t_shell *cmd;
    cmd = malloc(sizeof(t_shell));
    if (!cmd)
        return (0);
    cmd->env_lst = init_envp(envp, cmd);
    while (1)
    {
        cmd->line_command = readline(">");
        cmd->tok_lst = tokenization(cmd);
        expand_var(cmd);        
        parser(cmd);

    }
}

int main(int argc, char  **argv, char **envp)
{
    printf("%s",argv[0]);
    if (argc != 1)
        printf("Error, this program should not take any arguments");
    else
        minishell_start(envp);
    return (0);
}
