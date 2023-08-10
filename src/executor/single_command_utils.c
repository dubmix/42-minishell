/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:52:45 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/10 17:12:11 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtins(char *string)
{
	if (!ft_strncmp(string, "echo", ft_strlen(string)))
		return (1);
	else if (!ft_strncmp(string, "pwd", ft_strlen(string)))
		return (1);
	else if (!ft_strncmp(string, "env", ft_strlen(string)))
		return (1);
	else
		return (0);
}

int	single_command(t_shell *cmd)
{
	char			*path;
	t_single_cmd	*temp;

	path = NULL;
	temp = cmd->cmd_lst;
	if (!is_builtins(temp->command[0]))
	{
		path = check_access(cmd->envp_copy, temp->command);
		single_command_sub(cmd, path, temp);
		// if (!path && g_xcode != 126)
		// {
		// 	g_xcode = 127;
		// 	ft_putstr_fd(temp->command[0], STDERR_FILENO);
		// 	ft_putstr_fd(": command not found\n", STDERR_FILENO);
		// 	exit(g_xcode);
		// }
		// else if (!path && g_xcode == 126)
		// {
		// 	ft_putstr_fd("minishell: ", STDERR_FILENO);
		// 	ft_putstr_fd(temp->command[0], STDERR_FILENO);
		// 	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		// 	exit(g_xcode);
		// }
		// else
		// {
		// 	if (execve(path, cmd->cmd_lst->command, cmd->envp_copy) == -1)
		// 	{
		// 		g_xcode = 127;
		// 		free(path);
		// 		exit(g_xcode);
		// 	}
		// }
	}
	else if (ft_strncmp(cmd->cmd_lst->command[0], "echo", 4) == 0)
		echo(cmd->cmd_lst->command, cmd);
	else if (ft_strncmp(cmd->cmd_lst->command[0], "env", 3) == 0)
		env(cmd);
	else if (ft_strncmp(cmd->cmd_lst->command[0], "pwd", 3) == 0)
		pwd();
	exit(EXIT_SUCCESS);
}

void	single_command_sub(t_shell *cmd, char *path, t_single_cmd *temp)
{
	if (!path && g_xcode != 126)
	{
		g_xcode = 127;
		ft_putstr_fd(temp->command[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(g_xcode);
	}
	else if (!path && g_xcode == 126)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(temp->command[0], STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		exit(g_xcode);
	}
	else if (execve(path, cmd->cmd_lst->command, cmd->envp_copy) == -1)
	{
		g_xcode = 127;
		free(path);
		exit(g_xcode);
	}
}
