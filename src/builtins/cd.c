/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:21:08 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/06 16:46:50 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cd(t_shell *cmd)
{
	int		ret;
	//char	*oldpwd;
	t_shell	**tmp;

	tmp = &cmd;
	printf("OLD TRUC %s", cmd->oldpwd);
	while ((*tmp)->env_lst)
	{
		if (ft_strncmp((*tmp)->env_lst->name, "PWD", 3))
		{
			free(cmd->oldpwd);			
			cmd->oldpwd = ft_strdup((*tmp)->env_lst->value);
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

void	copy_pwd(t_env *tmp, t_shell *cmd)
{
	char	cwd[PATH_MAX];
	char **string;
	char *full_string;
	t_env *node_to_delete;

	full_string = NULL;
	string = (char **)malloc(sizeof(char *) * 3 );
	string[0] = ft_strdup(tmp->name);
	string[1] = getcwd(cwd, sizeof(cwd));
	string[2] = 0;
	if (!string[1])
		perror("Error retrieving the pwd");
	full_string = ft_strjoin(string[0], "=");
	full_string = ft_strjoin(full_string, string[1]);
	node_to_delete = tmp;
	delete_node_env(&(cmd->env_lst), node_to_delete);
	new_node_env(cmd, &cmd->env_lst, string, full_string);
}

void	copy_oldpwd(t_env *tmp, t_shell *cmd)
{
	char **string;
	char *full_string;
	t_env *node_to_delete;

	full_string = NULL;
	string = (char **)malloc(sizeof(char *) * 3 );
	string[0] = ft_strdup(tmp->name);
	string[1] = ft_strdup(cmd->oldpwd);
	string[2] = 0;
	if (!string[1])
		perror("Error retrieving the pwd");
	full_string = ft_strjoin(string[0], "=");
	full_string = ft_strjoin(full_string, string[1]);
	node_to_delete = tmp;
	delete_node_env(&(cmd->env_lst), node_to_delete);
	new_node_env(cmd, &cmd->env_lst, string, full_string);
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

	tmp = cmd->env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == 0)
			copy_pwd(tmp, cmd);
		if (ft_strncmp(tmp->name, "OLDPWD", 6) == 0)
			copy_oldpwd(tmp, cmd);
		tmp = tmp->next;
		}
	return (tmp);
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
