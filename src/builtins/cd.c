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

// char *get_dir_name()
// {
// 	int i;

// 	i = 0;
// 	while()
// 	{
// 		if (ft_strncmp)
// 	}
// }

// int change_directory(t_shell *cmd)
// {
// 	char *tmp;
// 	int		ret;

// 	tmp = get_dir_name()
// 	ret = chdir(tmp); //returns 0 if success, -1 if error
// 	free(tmp);

// 	return (ret);
// }

void add_path_to_env(t_shell *cmd)
{
	t_env *tmp;
	char *str;
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

char *get_path(t_shell *cmd, char *str)
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

	tmp = get_path(cmd, str);
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		/* error handling */
	}
	return (ret);
}

int cd(t_shell *cmd)
{
	int ret;
	t_shell **tmp;

	tmp = &cmd;
	if ((*tmp)->tok_lst->command == '\0')
		ret = go_to_path(cmd, "HOME");
	else if(ft_strncmp((*tmp)->tok_lst->command, "-", 1) == 0)
		ret = go_to_path(cmd, "OLDPWD");
	else
	{
		ret = chdir((*tmp)->tok_lst->command);
		if (ret != 0)
			printf("minishell: %s\n", (*tmp)->tok_lst->command);
	}
	if (ret != 0)
		return (EXIT_FAILURE); // exit_failure value = 8;
	add_path_to_env(cmd);
	return (EXIT_SUCCESS);
}
