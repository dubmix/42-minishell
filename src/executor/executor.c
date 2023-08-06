/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:45:11 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/06 16:53:15 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pre_executor(t_shell *cmd)
{
	signal(SIGQUIT, sigquit_handler); 
	cmd->exit_code = 1;
	if (cmd->nb_of_pipes == 0)
		exec_single_command(cmd);
	else
	{
		cmd->pid = ft_calloc(sizeof(int), cmd->nb_of_pipes + 2);
		if (!cmd->pid)
			ft_error(cmd, "Pid error", 4, 1);
		exec_piped_command(cmd);
	}
	return (cmd->exit_code);
}

void	exec_single_command(t_shell *cmd)
{
	int	pid;
	int	status;

	if (exec_single_command_sub(cmd) == 1)
		return ;
	signal(SIGINT, sigint_child);
	pid = fork();
	if (pid < 0)
		ft_error(cmd, "Fork error", 4, 1);
	if (pid == 0)
	{
		cmd->exit_code = exec_command(cmd);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

int	exec_single_command_sub(t_shell *cmd)
{
	if (ft_strncmp(cmd->cmd_lst->command[0], "exit", 4) == 0)
		exxit(cmd);
	else if (ft_strncmp(cmd->cmd_lst->command[0], "export", 6) == 0)
	{
		export(cmd, cmd->cmd_lst->command);
		return (1);
	}
	else if (ft_strncmp(cmd->cmd_lst->command[0], "unset", 5) == 0)
	{
		unset(cmd, cmd->cmd_lst->command);
		return (1);
	}
	else if (ft_strncmp(cmd->cmd_lst->command[0], "cd", 2) == 0)
	{
		cd(cmd);
		return (1);
	}
	return (0);
}

int	exec_command(t_shell *cmd)
{
	if (cmd->cmd_lst->append == 1 || cmd->cmd_lst->redir_in == 1
		|| cmd->cmd_lst->redir_out == 1 || cmd->nb_of_heredocs != 0)
		check_redirections(cmd);
	if (cmd->cmd_lst->command != NULL)
	{
		cmd->exit_code = single_command(cmd);
		exit(cmd->exit_code); 
	}
	exit(cmd->exit_code);
}
