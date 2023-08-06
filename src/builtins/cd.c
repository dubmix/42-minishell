/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:21:08 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/06 14:21:12 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cd(t_shell *cmd)
{
	int		ret;
	t_shell	**tmp;

	tmp = &cmd;
	while ((*tmp)->env_lst)
	{
		if (ft_strncmp((*tmp)->env_lst->name, "PWD", 3))
		{
			free(cmd->oldpwd);			
			cmd->oldpwd = ft_strdup((*tmp)->env_lst->value);
			// printf("PWD IS %s",(*tmp)->env_lst->value );
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
			printf("minishell: %s No such file or directory \n", (*tmp)->cmd_lst->command[0]); // what's this ?
	}
	if (ret != 0)
	{
		printf("minishell: %s No such file or directory \n", (*tmp)->cmd_lst->command[0]); // what's this ?

	}	
	cmd->env_lst = add_path_to_env(cmd);
	printf("--------------\n");
	print_list(cmd->env_lst);
	printf("--------------\n");
	return (EXIT_SUCCESS);
}

t_env	*add_path_to_env(t_shell *cmd)
{
	t_env	*tmp;
	t_env	**head;
	char	cwd[PATH_MAX];

	tmp = cmd->env_lst;
	head = &tmp;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == 0)
		{
			printf("OLD PWD IS %s", tmp->value);
			free(tmp->value);
			tmp->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
			printf("NEW PWD IS %s", tmp->value);
		}
		if (ft_strncmp(tmp->name, "OLDPWD", 6) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(cmd->oldpwd);
		}
		tmp = tmp->next;
	}
	tmp = *head;
	return (*head);
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
	char *tmp;
	int ret;

	tmp = get_path_cd(cmd, str);
	ret = chdir(tmp);
	free(tmp);
	return (ret);
}