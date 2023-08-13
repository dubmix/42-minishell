/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:10:21 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/13 13:32:20 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_path_to_env(t_shell *cmd)
{
	t_env	*tmp;
	int		check;

	check = 0;
	tmp = cmd->env_lst;
	while (tmp && check != 2)
	{
		if (!ft_strncmp(tmp->name, "PWD", 3))
			check = add_path_to_env_sub(tmp, check);
		if (!ft_strncmp(tmp->name, "OLDPWD", 6))
			check = add_oldpath_to_env_sub(cmd, tmp, check);
		tmp = tmp->next;
	}
}

int	add_path_to_env_sub(t_env *tmp, int check)
{
	char	*temp;
	char	*full_string_pwd;
	char	cwd[PATH_MAX];

	free(tmp->value);
	free(tmp->full_string);
	tmp->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
	if (tmp->value == NULL)
		ft_putstr_fd("ERRROR\n", 2);
	temp = ft_strjoin(tmp->name, "=");
	full_string_pwd = ft_strjoin(temp, tmp->value);
	free(temp);
	tmp->full_string = ft_strdup(full_string_pwd);
	free(full_string_pwd);
	check++;
	return (check);
}

int	add_oldpath_to_env_sub(t_shell *cmd, t_env *tmp, int check)
{
	char	*full_string_oldpwd;
	char	*temp;

	free(tmp->value);
	free(tmp->full_string);
	tmp->value = ft_strdup(cmd->oldpwd);
	temp = ft_strjoin(tmp->name, "=");
	full_string_oldpwd = ft_strjoin(temp, tmp->value);
	free(temp);
	tmp->full_string = ft_strdup(full_string_oldpwd);
	free(full_string_oldpwd);
	check++;
	return (check);
}
