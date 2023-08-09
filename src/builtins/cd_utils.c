/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:10:21 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/08 17:28:04 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_path_to_env(t_shell *cmd)
{
	t_env	*tmp;
	int		check;
	char	cwd[PATH_MAX];
	char	*full_string_pwd;
	char	*full_string_oldpwd;

	full_string_oldpwd = NULL;
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
			check = add_path_to_env_sub(cmd, tmp, full_string_oldpwd, check);
		tmp = tmp->next;
	}
	free(full_string_pwd);
	free(full_string_oldpwd);
}

int	add_path_to_env_sub(t_shell *cmd, t_env *tmp, char *full_str, int check)
{
	tmp->value = ft_strdup(cmd->oldpwd);
	full_str = ft_strjoin(tmp->name, "=");
	full_str = ft_strjoin(full_str, tmp->value);
	tmp->full_string = ft_strdup(full_str);
	check++;
	return (check);
}
