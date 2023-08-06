/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:21:08 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/06 10:24:10 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cd(t_shell *cmd)
{
	int		ret;
	//char	*oldpwd;
	t_shell	**tmp;

	tmp = &cmd;
	//cd_sub(cmd);
	while ((*tmp)->env_lst)
	{
		if (ft_strncmp((*tmp)->env_lst->name, "PWD", 3))
		{
			//oldpwd = malloc(sizeof(char *) * ft_strlen(((*tmp)->env_lst->value)));
			//oldpwd = (*tmp)->env_lst->value;
			free((*tmp)->oldpwd);
			(*tmp)->oldpwd = ft_strdup((*tmp)->env_lst->value);
			break ;
		}
		(*tmp)->env_lst = (*tmp)->env_lst->next;
	}
	if (!(*tmp)->cmd_lst->command)
		ret = go_to_path(cmd, "HOME");
	else if (ft_strncmp((*tmp)->cmd_lst->command[0], "-", 1) == 0)
		ret = go_to_path(cmd, "OLDPWD");
	else
	{
		ret = chdir((*tmp)->cmd_lst->command[1]);
		if (ret != 0)
			printf("minishell: %s\n", (*tmp)->cmd_lst->command[0]);
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	add_path_to_env(cmd);
	return (EXIT_SUCCESS);
}

// void	cd_sub(t_shell *cmd)
// {
// 	t_shell	**tmp;
// 	int		value;
// 	char	*oldpwd;

// 	tmp = &cmd;
// 	while ((*tmp)->env_lst)
// 	{
// 		if (ft_strncmp((*tmp)->env_lst->name, "PWD", 3))
// 		{
// 			value = ft_strlen((*tmp)->env_lst->value);
// 			oldpwd = malloc(sizeof(char *) * value);
// 			oldpwd = (*tmp)->env_lst->value;
// 			(*tmp)->oldpwd = oldpwd;
// 			break ;
// 		}
// 		(*tmp)->env_lst = (*tmp)->env_lst->next;
// 	}
// }

void	add_path_to_env(t_shell *cmd)
{
	t_env	*tmp;
	char	cwd[PATH_MAX];

	tmp = cmd->env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == 0)
		{
			tmp->value = getcwd(cwd, sizeof(cwd));
		}
		else if (ft_strncmp(tmp->name, "OLDPWD", 6) == 0)
		{
			tmp->value = cmd->oldpwd;
			free(cmd->oldpwd);
		}
		tmp = tmp->next;
	}
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
	if (ret != 0)
	{
		/* error handling */
	}
	return (ret);
}
