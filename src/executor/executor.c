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
    {
        exec_single_command(cmd);
        //write(1, "a", 1);
    }
    else
    {
        cmd->pid = ft_calloc(sizeof(int), cmd->nb_of_pipes);
        if(!cmd->pid)
            return(0); //error handling
        exec_piped_command(cmd);
    }
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
        exit_code = exec_command(cmd);
    waitpid(pid, &status, 0);
}

int exec_piped_command(t_shell *cmd)
{
    int fd;
    int pipefd[2];
    int i;

    i = 0;
    fd = STDIN_FILENO;
    while (1)
    {
        if (cmd->cmd_lst->next)
            pipe(pipefd);
        //exec_heredoc(cmd);
        i = ft_fork(cmd, pipefd, fd, i);
        if (cmd->cmd_lst->index != 0)
            close(pipefd[1]);
        fd = pipefd[0];
        //fd = check_heredoc(cmd, pipefd);
        if (cmd->cmd_lst->next)
            cmd->cmd_lst = cmd->cmd_lst->next;
        else
            break;
    }
    pipe_wait(cmd->pid, cmd->nb_of_pipes); // could be replaced by pid = -1 
    //so the parents waits for all child processes to terminate?
    //cmd->cmd_lst->command; //iterate through list to set back to first command
    return (0);
}

int ft_fork(t_shell *cmd, int pipefd[2], int fd, int i)
{
    cmd->pid[i] = fork();
    if (cmd->pid[i] < 0)
        return (0); //error handling
    if (cmd->pid[i] == 0)
        dup_cmd(cmd, pipefd, fd);
    i++;
    return (i);
}

void dup_cmd(t_shell *cmd, int pipefd[2], int fd)
{
    int dup;

    dup = dup2(fd, STDIN_FILENO);
    if (dup < 0)
        return ; //error handling
    close(pipefd[0]);
    dup = dup2(pipefd[1], STDOUT_FILENO);
    if (dup < 0)
        return ; //error handling
    close(pipefd[1]);
    if(cmd->cmd_lst->index != 0)
        close(fd);
    exec_command(cmd);
}

int exec_command(t_shell *cmd)
{
    if (cmd->cmd_lst->append == 1 || cmd->cmd_lst->redir_in == 1
            || cmd->cmd_lst->redir_out == 1) //if there are any redirections. and how do we declare the static exit_code
    {
        check_redirections(cmd);
        write(1, "c", 1);
            //exit(1);
    }
    write(1, "d", 1);
    if (cmd->cmd_lst->command != NULL)
    {
        exit_code = single_command(cmd);
        exit(exit_code);
    }
    return (exit_code);
}

int check_redirections(t_shell *cmd)
{
    t_single_cmd *head;

    head = cmd->cmd_lst;
    while (cmd->cmd_lst)
    {
        if (cmd->cmd_lst->redir_in == 1)
            exec_infile(cmd->cmd_lst->redir_in_str);
        else if (cmd->cmd_lst->append == 1)
            exec_outfile(cmd); //actually heredoc filename?
        else if (cmd->cmd_lst->redir_out == 1)
            exec_outfile(cmd);
    cmd->cmd_lst = cmd->cmd_lst->next;
    }
    write(1, "g", 1);
    cmd->cmd_lst = head; // a utiliser a la place des temp?
    return (EXIT_SUCCESS);
}

int exec_infile(char *file)
{
    int fd;
    int dup;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        printf("minishell: infile: No such file or directory\n");
        return (EXIT_FAILURE); // error handling;
    }
    dup = dup2(fd, STDIN_FILENO);
    if (fd > 0 && dup < 0)
    {
        printf("minishell: pipe error\n");
        return (EXIT_FAILURE); //error handling;
    }
    if (fd > 0)
        close(fd);
    return (EXIT_SUCCESS);
}

int exec_outfile(t_shell *cmd)
{
    int fd;
    int dup;

    if (cmd->cmd_lst->append == 1)
        fd = open(cmd->cmd_lst->append_str, 
                O_CREAT | O_RDWR | O_APPEND, 0644);
    else
    {
        write(1, "e", 1);
        fd = open(cmd->cmd_lst->redir_out_str,
                O_CREAT | O_RDWR | O_TRUNC, 0644);
    }
    if (fd < 0)
    {
        printf("minishell: outfile: Error\n");
        return (EXIT_FAILURE); // error handling;
    }
    write(1, "f", 1);
    dup = dup2(fd, STDOUT_FILENO);
    if (fd > 0 && dup < 0)
    {
        printf("minishell: pipe error\n");
        return (EXIT_FAILURE); //error handling;
    }
    if (fd > 0)
        close(fd);
    return (EXIT_SUCCESS);
}

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

int pipe_wait(int *pid, int nb_of_pipes)
{
    int i;
    int status;

    i = 0;
    while (i < nb_of_pipes)
    {
        waitpid(pid[i], &status, 0);
        i++;
    }
    waitpid(pid[i], &status, 0);
    return (EXIT_SUCCESS);
}