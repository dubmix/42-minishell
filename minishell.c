/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:16:23 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/04 13:12:45 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int minishell_start(char **envp)
{
    (void)envp;
    t_shell *cmd;
    cmd = malloc(sizeof(t_shell));
    cmd->envir = init_envp(envp);
//    print_list(cmd->envir);
    while (1)
    {
        cmd->line_command = readline(">");
        cmd->tokens=tokenization(cmd);
        printf("BEFORE %s %d\n", cmd->tokens->command, cmd->tokens->type);
        expand_var(cmd);
        print_list_tok(cmd->tokens);
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
