/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:45:11 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/25 10:45:35 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int pre_executor(t_shell *cmd)
{
    //sigquit handle
    if (cmd->nb_of_pipes == 0)
        exec_single_command(cmd);
    // else
    // {
    //     cmd->pid = ft_calloc(sizeof(int *) * cmd->nb_of_pipes);
    //     if(!cmd->pid)
    //         return(0); //error_handling
    //     executor(cmd);
    // }
    return (EXIT_SUCCESS);
}

void exec_single_command(t_shell *cmd)
{
    int pid;
    int status;

    //exec_heredoc(cmd);
    pid = fork();
    if (pid < 0)
        return ; // error handling
    if (pid == 0)
        exit_code = single_command(cmd);
    waitpid(pid, &status, 0);
}

// int exec_command(t_shell *cmd)
// {
//     int exit_code;

//     exit_code = 0;
//     if (redirections)
//     {
//         // mimi's code with builtins and execve
//     }
//     return (exit_code); // a stocker dans la struct?
// }

// int executor(t_shell *cmd)
// {
//     int fd;
//     int pipefd[2];

//     fd = STDIN_FILENO;
//     while (1)
//     {
//         if (cmd->cmd_lst->next)
//             pipe(pipefd);
//         //exec_heredoc(cmd);
//         ft_fork(cmd, pipefd, fd);
//         if (cmd->cmd_lst->index != 0) // if there is a previous command
//             close(pipefd[1]);
//         fd = check_heredoc(cmd, pipefd);
//         if (cmd->cmd_lst->next)
//             cmd->cmd_lst = cmd->cmd_lst->next;
//         else
//             break;
//     }
//     pipe_wait(cmd->pid, cmd->nb_of_pipes); // could be replaced by pid = -1 
//     //so the parents waits for all child processes to terminate?
//     //cmd->cmd_lst->command; //iterate through list to set back to first command
//     return (0);
// }

// int ft_fork(t_shell *cmd, int pipefd[2], int fd)
// {
//     int i; // maybe needs to be reset, Maia has global

//     i = 0;
//     cmd->pid[i] = fork();
//     if (cmd->pid[i] < 0)
//         //error
//     if (cmd->pid[i] == 0)
//         dup_cmd(cmd, pipefd, fd);
//     i++;
//     return (EXIT_SUCCESS);
// }

// void dup_cmd(t_shell *cmd, int pipefd[2], int fd)
// {
//     int dup;

//     dup = dup2(fd, STDIN_FILENO);
//     if (dup < 0)
//         //error;
//     close(pipefd[0]);
//     dup = dup2(pipefd[1], STDOUT_FILENO);
//     if (dup < 0)
//         //error;
//     close(pipefd[1]);
//     if(cmd->cmd_lst->index != 0)
//         close(fd);
//     exec_command(cmd);
// }

// int check_heredoc(t_shell *cmd, int pipefd[2])
// {
//     int fd;

//     if (cmd->nb_of_heredocs != 0)
//     {
//         close(pipefd[0]);
//         fd = open(cmd->heredoc_arr, O_RDONLY);
//     }
//     else
//         fd = pipefd[0];
//     return (fd);
// }

// int pipe_wait(int *pid, int nb_of_pipes)
// {
//     int i;
//     int status;

//     i = 0;
//     while (i < nb_of_pipes)
//     {
//         waitpid(pid[i], &status, 0);
//         i++;
//     }
//     waitpid(pid[i], &status, 0);
//     return (EXIT_SUCCESS);
// }
