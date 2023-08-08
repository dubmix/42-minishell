/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:21:08 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/08 17:27:04 by pdelanno         ###   ########.fr       */
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
			cmd->oldpwd = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

int	cd(t_shell *cmd)
{
	int		ret;
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
			return (cd_error((*tmp)->cmd_lst->command[1]));
	}
	if (ret != 0)
		return (cd_error((*tmp)->cmd_lst->command[1]));
	add_path_to_env(cmd);
	return (EXIT_SUCCESS);
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
