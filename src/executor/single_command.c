/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:46:21 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/02 09:51:34 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_path(char **envp)
{
	int		i;
	int		length;
	char	*path;
	char	**path_arr;

	length = 0;
	i = 0;
	while (*envp != (void *)'\0')
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	length = ft_strlen(envp[i]);
	path = malloc(sizeof(char *) * length + 1);
	if (!path)
		return (NULL);
	ft_strlcpy(path, envp[i], length + 1);
	path_arr = ft_split(path, ':');
	free(path);
	return (path_arr);
}

char	*check_access(char **envp, char **cmd) //, int *fds)
{
	char	*path_cmd;
	int		i;
	char	**path_arr;
	char	*tmp;

	if (access(cmd[0], F_OK) == 0)
		return (cmd[0]);
	path_arr = get_path(envp);
	i = 0;
	while (path_arr[i] != (void *)'\0')
	{
		tmp = ft_strjoin(path_arr[i], "/");
		path_cmd = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path_cmd, F_OK | X_OK) != 0)
			free(path_cmd);
		else
			break ;
		i++;
	}
	// if (path_arr[i] == (void *) '\0')
	// 	free_all(path_arr, cmd) //, fds);
	free_arr(path_arr);
	return (path_cmd);
}

int	single_command(t_shell *cmd)
{
	char	*path;
	t_single_cmd *temp;

	temp = cmd->cmd_lst;
	path = check_access(cmd->envp_copy, temp->command);
	if (ft_strncmp(cmd->cmd_lst->command[0], "echo", 4) == 0)
		echo(cmd->cmd_lst->command);
	else if (ft_strncmp(cmd->cmd_lst->command[0], "env", 3) == 0)
		env(cmd);
	else if (ft_strncmp(cmd->cmd_lst->command[0], "pwd", 3) == 0)
		pwd();
	else
	{
		if (execve(path, cmd->cmd_lst->command, cmd->envp_copy) == -1)
			printf("oupsi");
	}
	free(path);
	return(EXIT_SUCCESS);
}
