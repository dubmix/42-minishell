/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:21:08 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/19 11:13:09 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int cd(t_shell *cmd)
{
	int ret;
	t_shell **tmp;

	tmp = &cmd;
	if (!(*tmp)->cmd_lst->command)
	{
		write(1, "a", 1);
		ret = go_to_path(cmd, "HOME");
	}
	else if(ft_strncmp((*tmp)->cmd_lst->command[0], "-", 1) == 0)
	{	
		write(1, "b", 1);
		ret = go_to_path(cmd, "OLDPWD");
	}
	else
	{
		write(1, "cd", 2);
		ret = chdir((*tmp)->cmd_lst->command[1]);
		if (ret != 0)
			printf("minishell: %s\n", (*tmp)->cmd_lst->command[0]);
	}
	if (ret != 0)
		return (EXIT_FAILURE); // exit_failure value = 8;
	add_path_to_env(cmd);
	return (EXIT_SUCCESS);
}

void add_path_to_env(t_shell *cmd)
{
	t_env *tmp;
	//char *str;
	char cwd[PATH_MAX];

	tmp = cmd->env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == 0)
			tmp->value = getcwd(cwd, sizeof(cwd));
		tmp = tmp->next;
	}
	//same with OLDPWD
}

char *get_path_cd(t_shell *cmd, char *str)
{
	t_env *tmp;
	char *path;

	tmp = cmd->env_lst;
	while(tmp)
	{
		if(ft_strncmp(tmp->name, str, ft_strlen(str)) == 0)
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
	char *tmp;
	int ret;

	tmp = get_path_cd(cmd, str);
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		/* error handling */
	}
	return (ret);
}