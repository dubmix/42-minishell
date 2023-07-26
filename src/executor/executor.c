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

#include "minishell.h"

launch_expander

int pre_executor(t_shell *shell)
{
    //sigquit handle
    if (shell->pipe_number == 0)
        execute_single_command(shell)
    else
    {
        shell->pid = ft_calloc; //?? or malloc enough
        //protect
        executor(shell);
    }
    return (EXIT_SUCCESS);
}

void execute_single_command(t_shell *shell)
{
    int pid;
    int status;

    shell->commands = launch_expander(shell);
    heredoc(shell);
    pid = fork();
    if (pid < 0)
        //error
    if (pid == 0)
        exit_code = single_command(shell);
    waitpid(pid, &status, 0);
}

int execute_command(t_shell *shell)
{
    int exit_code;

    exit_code = 0;
    if (redirections)
    {
        // mimi's code with builtins and execve
    }
    return (exit_code); // a stocker dans la struct?
}

int executor(t_shell *shell)
{
    int fd;
    int pipefd[2];

    fd = STDIN_FILENO;
    while (1)
    {
        shell->tok_lst->command = expander()
        if (shell->tok_lst->next)
        {
            flag = 1;
            pipe(pipefd);
        }
        heredoc(shell);
        ft_fork();
        if (flag == 1) // if there is a previous command
            close(end[1]);
        fd = check_heredoc(shell, pipefd);
        if (shell->tok_lst->next)
            shell->tok_lst = shell->tok_lst->next;
        else
            break;
    }
    pipe_wait(pid, shell->pipe_number); // could be replaced by pid = -1 
    //so the parents waits for all child processes to terminate?
    shell->cmd_lst->command; //iterate through list to set back to first command
    return (0);
}

int ft_fork(t_shell *shell, int pipefd[2], int fd)
{
    int i; // maybe needs to be reset

    i = 0;
    shell->pid[i] = fork();
    if (shell->pid[i] < 0)
        //error
    if (shell->pid[i] == 0)
        dup_cmd(shell, pipefd, fd);
    i++;
    return (EXIT_SUCCESS);
}

void dup_cmd(t_shell *shell, int pipefd[2], int fd)
{
    int dup;

    dup = dup2(fd, STDIN_FILENO);
    if (dup < 0)
        //error;
    close(pipefd[0]);
    dup = dup2(pipefd[1], STDOUT_FILENO);
    if (dup < 0)
        //error;
    close(pipefd[1]);
    if(previous command exists)
        close(fd_in);
    execute_command(shell);
}

int check_heredoc(t_shell *shell, int pipefd[2])
{
    int fd;

    if (shell->heredoc != 0)
    {
        close(pipefd[0]);
        fd = open(shell->heredocfilename, O_RDONLY);
    }
    else
        fd = pipefd[0];
    return (fd);
}

int pipe_wait(int *pid, int number_of_pipes)
{
    int i;
    int status;

    i = 0;
    while (i < amount)
    {
        waitpid(pid[i], &status, 0);
        i++;
    }
    waitpid(pid[i], &status, 0);
    return (EXIT_SUCCESS);
}
