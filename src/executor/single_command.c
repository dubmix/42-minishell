/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:46:21 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/13 14:02:42 by pdelanno         ###   ########.fr       */
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
	while (*envp != (void *) '\0')
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	length = ft_strlen(envp[i]);
	path = malloc(sizeof(char *) * length + 1);
	if (!path)
		return (NULL);
	ft_strlcpy(path, envp[i], length + 1);
	path_arr = ft_split(path, ':');
	free(path);
	return (path_arr);
}

char	*check_access(char **envp, char **command)
{
	char	*path_cmd;
	char	**path_arr;
	char	*tmp;

	path_cmd = NULL;
	tmp = NULL;
	if (access(command[0], F_OK) == 0 && access(command[0], X_OK) == 0)
		return (command[0]);
	else if (access(command[0], F_OK) == 0 && access(command[0], X_OK) != 0)
	{
		g_xcode = 126;
		return (NULL);
	}
	path_arr = get_path(envp);
	if (!path_arr)
		return (NULL);
	path_cmd = check_access_sub(path_arr, command, path_cmd, tmp);
	return (path_cmd);
}

char *check_access_sub(char **path_arr, char **command, char *path_cmd, char *tmp)
{
	int	i;

	i = 0;
	while (path_arr[i] != (void *) '\0')
	{
		tmp = ft_strjoin(path_arr[i], "/");
		path_cmd = ft_strjoin(tmp, command[0]);
		free(tmp);
		if (access(path_cmd, F_OK | X_OK) != 0)
			free(path_cmd);
		else
			break ;
		i++;
	}
	if (path_arr[i] == (void *) '\0')
	{
		free_arr(path_arr);
		return (NULL);
	}
	free_arr(path_arr);
	return (path_cmd);
}
