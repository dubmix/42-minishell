/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:54:27 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/11 11:59:28 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_piped_command(t_shell *cmd)
{
	int				fd;
	int				pipefd[2];
	int				i;
	t_single_cmd	*head;

	head = cmd->cmd_lst;
	i = 0;
	fd = STDIN_FILENO;
	while (cmd->cmd_lst)
	{
		i = exec_piped_command_sub(cmd, pipefd, fd, i);
		if (cmd->cmd_lst->index != 0)
		{
			close(fd);
			close(pipefd[1]);
		}
		fd = pipefd[0];
		if (cmd->cmd_lst->next)
			cmd->cmd_lst = cmd->cmd_lst->next;
		else
			break ;
	}
	pipe_wait(cmd);
	cmd->cmd_lst = head;
	return (EXIT_SUCCESS);
}

int	exec_piped_command_sub(t_shell *cmd, int pipefd[], int fd, int i)
{
	if (cmd->cmd_lst->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("Pipe error\n");
			exit(EXIT_FAILURE);
		}
	}
	i = ft_fork(cmd, pipefd, fd, i);
	if (i == -1)
	{
		perror("Fork error\n");
		exit(EXIT_FAILURE);
	}
	return (i);
}

int	ft_fork(t_shell *cmd, int pipefd[2], int fd, int i)
{
	cmd->pid[i] = fork();
	if (cmd->pid[i] < 0)
		ft_error(cmd, "Fork error", 1);
	if (cmd->pid[i] == 0)
		dup_cmd(cmd, pipefd, fd);
	else
		close(pipefd[1]);
	i++;
	return (i);
}

void	dup_cmd(t_shell *cmd, int pipefd[2], int fd)
{
	if (cmd->cmd_lst->index != 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
			ft_error(cmd, "Dup failed IN", 1);
	}
	close(pipefd[0]);
	if (cmd->cmd_lst->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			ft_error(cmd, "Dup failed OUT", 1);
	}
	close(pipefd[1]);
	exec_command(cmd);
}

int	pipe_wait(t_shell *cmd)
{
	int		i;
	int		status;
	int		child_count;
	pid_t	result;

	child_count = cmd->nb_of_pipes + 1;
	while (child_count > 0)
	{
		i = child_count;
		while (i > 0)
		{
			result = waitpid(cmd->pid[i], &status, WNOHANG);
			if (result == -1 || result == 0)
			{
				i--;
				continue ;
			}
			else if (WIFEXITED(status))
				g_xcode = WEXITSTATUS(status);
			i--;
		}
		usleep(10000);
		child_count--;
	}
	return (EXIT_SUCCESS);
}
