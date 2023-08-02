/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:45:11 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/02 09:53:51 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int pre_executor(t_shell *cmd)
{
    //signal(SIGQUIT, sigquit_handler);
    if (cmd->nb_of_pipes == 0)
    {
        exec_single_command(cmd);
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

    if(ft_strncmp(cmd->cmd_lst->command[0], "exit", 4) == 0)
        exxit(cmd);    // check corner case exit | ech
    else if (ft_strncmp(cmd->cmd_lst->command[0], "export", 6) == 0)
    {
		export(cmd, cmd->cmd_lst->command);
        return ;
    }
    else if (ft_strncmp(cmd->cmd_lst->command[0], "unset", 5) == 0)
	{
        unset(cmd, cmd->cmd_lst->command);
        return ;
    }
    else if (ft_strncmp(cmd->cmd_lst->command[0], "cd", 2) == 0)
	{	
        cd(cmd);
        return ;
    }
    pid = fork();
    if (pid < 0)
        return ; // error handling
    if (pid == 0)
        g_exit_code = exec_command(cmd);
    else
        waitpid(pid, &status, 0);
}

int exec_piped_command(t_shell *cmd)
{
    int fd;
    int pipefd[2];
    int i;
    t_single_cmd *head;

    head = cmd->cmd_lst;
    i = 0;
    fd = STDIN_FILENO;
    while (1)
    {
        if (cmd->cmd_lst->next)
            pipe(pipefd);
        i = ft_fork(cmd, pipefd, fd, i);
        if (cmd->cmd_lst->index != 0)
            close(pipefd[1]);
        fd = pipefd[0];
        if (cmd->cmd_lst->next)
            cmd->cmd_lst = cmd->cmd_lst->next;
        else
            break;
    }
    pipe_wait(cmd->pid, cmd->nb_of_pipes);
    cmd->cmd_lst = head;
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

    if (cmd->cmd_lst->index != 0)
    {
        dup = dup2(fd, STDIN_FILENO);
        if (dup < 0 && cmd->cmd_lst->index != 0)
            return ; //error handling
    }
    close(pipefd[0]);
    if (cmd->cmd_lst->next)
    {
        dup = dup2(pipefd[1], STDOUT_FILENO);
        if (dup < 0 && cmd->cmd_lst->next)
            return ; //error handling
    }
    close(pipefd[1]);
    if(cmd->cmd_lst->index != 0)
        close(fd);
    exec_command(cmd);
}

int exec_command(t_shell *cmd)
{
    if (cmd->cmd_lst->append == 1 || cmd->cmd_lst->redir_in == 1
            || cmd->cmd_lst->redir_out == 1 || cmd->nb_of_heredocs != 0) //if there are 
        check_redirections(cmd);
    if (cmd->nb_of_pipes != 0 && cmd->cmd_lst->command != NULL) // nb_of_pipes needs to be reinit
    {
        g_exit_code = single_command(cmd);
        exit(g_exit_code); //si ca beug possibilite de lancer export etc dans le parent
    }
    else if (cmd->cmd_lst->command != NULL)
    {
        g_exit_code = single_command(cmd);
        // printf("2 %d\n", ft_lstsize_test((cmd->env_lst)));
        exit(g_exit_code); //return (exit_code); // si exit l'env s'efface quand le loop recommence
    }
    return (g_exit_code);
}

int check_redirections(t_shell *cmd)
{
    t_single_cmd *head;

    head = cmd->cmd_lst;
    while (cmd->cmd_lst)
    {
        if (cmd->nb_of_heredocs != 0)
            exec_heredoc(cmd);
        else if (cmd->cmd_lst->redir_in == 1)
            exec_infile(cmd->cmd_lst->redir_in_str);
        if (cmd->cmd_lst->append == 1)
            exec_outfile(cmd);
        else if (cmd->cmd_lst->redir_out == 1)
            exec_outfile(cmd);
    cmd->cmd_lst = cmd->cmd_lst->next;
    }
    cmd->cmd_lst = head;
    return (EXIT_SUCCESS);
}

int exec_heredoc(t_shell *cmd)
{
    int fd;
    int dup;
    
    fd = open("heredoc.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0)
    {
        printf("minishell: heredoc creation error");
        return (EXIT_FAILURE); // error handling;
    }
    write(fd, cmd->heredoc_string, ft_strlen(cmd->heredoc_string));
    close(fd);
    fd = open("heredoc.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("minishell: heredoc opening error\n");
        return (EXIT_FAILURE); // error handling;
    }
    dup = dup2(fd, STDIN_FILENO);
    if (dup < 0)
    {
        printf("minishell: dup heredoc error\n");
        return (EXIT_FAILURE); //error handling;
    }
    close(fd);
    unlink("heredoc.txt");
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
        fd = open(cmd->cmd_lst->redir_out_str,
                O_CREAT | O_RDWR | O_TRUNC, 0644);
    }
    if (fd < 0)
    {
        printf("minishell: outfile: Error\n");
        return (EXIT_FAILURE); // error handling;
    }
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