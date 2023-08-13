/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:29:20 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/13 15:05:19 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**var_arr(t_shell *cmd, char *command);
char	*look_into_envir_export(t_shell *cmd, char *string);
void	unset_if_export(t_shell *cmd, char *command);
char	**new_line(char *line);

int	export_variable(t_shell *cmd)
{
	t_shell	**tmp;
	int		i;
	char	**command;

	i = 0;
	tmp = &cmd;
	command = new_line(cmd->line);
	if (!command[i + 1])
		return (print_sorted_env(&cmd->env_lst));
	i++;
	while (command[i] != NULL)
	{
		if (ft_strncmp(command[i], " ", 1) != 0)
			export_variable_bis(cmd, command, i, tmp);
		i++;
	}
	free_arr(command);
	update_envp_copy(cmd);
	return (EXIT_SUCCESS);
}

void	export_variable_bis(t_shell *cmd, char **command, int i, t_shell **tmp)
{
	char	**str;
	char	*temp;

	str = var_arr(cmd, command[i]);
	free(command[i]);
	if (str[1] != NULL)
	{
		temp = ft_strjoin(str[0], "=");
		command[i] = ft_strjoin(temp, str[1]);
		free(temp);
	}
	else
		command[i] = ft_strdup(str[0]);
	if (check_param(command[i]) == 0 
		&& var_exists((*tmp)->env_lst, str[0]) == 0)
		new_node_env(cmd, &(*tmp)->env_lst, str, command[i]);
	else if (var_exists((*tmp)->env_lst, str[0]) == 1)
	{
		unset_if_export(cmd, str[0]);
		new_node_env(cmd, &(*tmp)->env_lst, str, command[i]);
	}
	free_arr(str);
}

int	export(t_shell *cmd, char **command)
{
	t_shell	**tmp;
	int		i;

	i = 0;
	tmp = &cmd;
	if (ft_strchr(cmd->line, '$'))
		return (export_variable(cmd));
	else
	{
		if (!command[i + 1])
			return (print_sorted_env(&cmd->env_lst));
		i++;
		while (command[i] != NULL)
		{
			if (!ft_strncmp(command[i], "=", ft_strlen(command[i])))
				export_error(command[i]);
			else if (ft_strncmp(command[i], " ", 1) != 0 
				&& ft_strncmp(command[i], "", ft_strlen(command[i]) != 0))
				export_bis(command, tmp, i, cmd);
			i++;
		}
		update_envp_copy(cmd);
	}
	return (EXIT_SUCCESS);
}

void	export_bis(char **command, t_shell **tmp, int i, t_shell *cmd)
{
	char	**str;

	if (ft_strchr(command[i], '=') != NULL)
		str = ft_split(command[i], '=');
	else
		str = ft_split(command[i], ' ');
	if (check_param(command[i]) == 0 
		&& var_exists((*tmp)->env_lst, str[0]) == 0)
		new_node_env(cmd, &(*tmp)->env_lst, str, command[i]);
	else if (var_exists((*tmp)->env_lst, str[0]) == 1)
	{
		unset_if_export(cmd, str[0]);
		new_node_env(cmd, &(*tmp)->env_lst, str, command[i]);
	}
	free_arr(str);
}

void	unset_if_export(t_shell *cmd, char *command)
{
	t_shell	**tmp;
	t_env	*tmp_env;

	tmp = &cmd;
	tmp_env = (*tmp)->env_lst;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->name, command, ft_strlen(tmp_env->name)) == 0)
		{
			delete_node_env(&(*tmp)->env_lst, tmp_env);
			break ;
		}
		tmp_env = tmp_env->next;
	}
}
