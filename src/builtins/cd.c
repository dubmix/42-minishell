/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:21:08 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/07 12:14:33 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	find_old_pwd(t_shell *cmd)
{
	t_env	*tmp;

	tmp = cmd->env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", 3))
		{
			free(cmd->oldpwd);			
			cmd->oldpwd = ft_strdup(tmp->full_string);
			break ;
		}
		tmp = tmp->next;
	}
}

int	cd(t_shell *cmd)
{
	int		ret;
	//char	*oldpwd;
	t_shell	**tmp;

	find_old_pwd(cmd);
	tmp = &cmd;
	if (!(*tmp)->cmd_lst->command)
		ret = go_to_path(cmd, "HOME");
	else if (ft_strncmp((*tmp)->cmd_lst->command[1], "-", 1) == 0)
		ret = go_to_path(cmd, "OLDPWD");
	else
	{
		ret = chdir((*tmp)->cmd_lst->command[1]);
		if (ret != 0)
		{
			printf("minishell: %s No such file or directory \n", (*tmp)->cmd_lst->command[0]);
			return (EXIT_FAILURE);
		}			
	}
	if (ret != 0)
	{
		printf("minishell: %s No such file or directory \n", (*tmp)->cmd_lst->command[0]);
		return (EXIT_FAILURE);
	}
	add_path_to_env(cmd);
	return (EXIT_SUCCESS);
}

void	add_path_to_env(t_shell *cmd)
{
	t_env	*tmp;
	int check;
	char	cwd[PATH_MAX];
	char *full_string_pwd;
	char *full_string_oldpwd;

	check = 0;
	tmp = cmd->env_lst;
	while (tmp && check != 2)
	{
		if (!ft_strncmp(tmp->name, "PWD", 3))
		{
			tmp->value = getcwd(cwd, sizeof(cwd));
			full_string_pwd = ft_strjoin(tmp->name, "=");
			full_string_pwd = ft_strjoin(full_string_pwd, tmp->value);
			tmp->full_string = ft_strdup(full_string_pwd);
			check++;
		}
		if (!ft_strncmp(tmp->name, "OLDPWD", 6))
		{	
			tmp->value = ft_strdup(cmd->oldpwd);
			full_string_oldpwd = ft_strjoin(tmp->name, "=");
			full_string_oldpwd = ft_strjoin(full_string_oldpwd, tmp->value);
			tmp->full_string = ft_strdup(full_string_oldpwd);
			check++;
		}
		tmp = tmp->next;
	}
	free(full_string_pwd);
	free(full_string_oldpwd);
}

char	*get_path_cd(t_shell *cmd, char *str)
{
	t_env	*tmp;
	char	*path;

	tmp = cmd->env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, str, ft_strlen(str)) == 0)
		{
			path = ft_strdup(tmp->value);
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	go_to_path(t_shell *cmd, char *str)
{
	char	*tmp;
	int		ret;

	tmp = get_path_cd(cmd, str);
	ret = chdir(tmp);
	free(tmp);
	return (ret);
}
