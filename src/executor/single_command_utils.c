/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:52:45 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/13 14:05:13 by pdelanno         ###   ########.fr       */
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
	else if (!ft_strncmp(string, "cd", ft_strlen(string)))
		return (1);
	else if (!ft_strncmp(string, "exit", ft_strlen(string)))
		return (1);
	else if (!ft_strncmp(string, "export", ft_strlen(string)))
		return (1);
	else if (!ft_strncmp(string, "unset", ft_strlen(string)))
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
	if (!is_builtins(temp->command[0]) && g_xcode != 130)
	{
		path = check_access(cmd->envp_copy, temp->command);
		single_command_sub(cmd, path, temp);
	}
	else if (ft_strncmp(cmd->cmd_lst->command[0], "echo", 4) == 0)
		echo(cmd->cmd_lst->command, cmd);
	else if (ft_strncmp(cmd->cmd_lst->command[0], "env", 3) == 0)
		env(cmd);
	else if (ft_strncmp(cmd->cmd_lst->command[0], "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(cmd->cmd_lst->command[0], "cd", 2) == 0)
		cd(cmd);
	else if (ft_strncmp(cmd->cmd_lst->command[0], "exit", 4) == 0)
		exxit(cmd);
	else if (ft_strncmp(cmd->cmd_lst->command[0], "export", 6) == 0)
		export(cmd, cmd->cmd_lst->command);
	else if (ft_strncmp(cmd->cmd_lst->command[0], "unset", 5) == 0)
		unset(cmd, cmd->cmd_lst->command);
	exit(g_xcode);
}

void	single_command_sub(t_shell *cmd, char *path, t_single_cmd *temp)
{
	if (!path && g_xcode != 126)
	{
		g_xcode = 127;
		single_command_error(": command not found\n", temp);
	}
	else if (!path && g_xcode == 126)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		single_command_error(": Permission denied\n", temp);
	}
	else if (!ft_strncmp(path, "/", ft_strlen(path)))
	{
		g_xcode = 126;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		single_command_error(": is a directory\n", temp);
	}
	single_command_sub_sub(cmd, path, temp);
}

void	single_command_sub_sub(t_shell *cmd, char *path, t_single_cmd *temp)
{
	if (!ft_strncmp(path, ".", ft_strlen(path)))
	{
		g_xcode = 2;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		single_command_error(": filename argument required\n", temp);
	}
	else if (execve(path, cmd->cmd_lst->command, cmd->envp_copy) == -1)
	{
		g_xcode = 127;
		free(path);
		exit(g_xcode);
	}
}

void	single_command_error(char *str, t_single_cmd *temp)
{
	ft_putstr_fd(temp->command[0], STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	exit(g_xcode);
}
