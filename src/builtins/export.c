/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:29:20 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/12 14:49:54 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**var_arr(t_shell *cmd, char *command);
char	*look_into_envir_export(t_shell *cmd, char *string);
void	unset_if_export(t_shell *cmd, char *command);
char	**new_line(char *line);

int	export_variable(t_shell *cmd)
{
	char	**str;
	t_shell	**tmp;
	int		i;
	char	**command;
	char *temp;

	i = 0;
	tmp = &cmd;
	command = new_line(cmd->line);
	if (!command[i + 1])
	{
		sort_env(&cmd->env_lst);
		print_sorted_env(&cmd->env_lst);
		return (EXIT_SUCCESS);
	}
	i++;
	while (command[i] != NULL)
	{
		if (ft_strncmp(command[i], " ", 1) != 0)
		{
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
		i++;
	}
	free_arr(command);
	update_envp_copy(cmd);
	return (EXIT_SUCCESS);
}

int	export(t_shell *cmd, char **command)
{
	char	**str;
	t_shell	**tmp;
	int		i;

	i = 0;
	tmp = &cmd;
	if (ft_strchr(cmd->line, '$'))
		return (export_variable(cmd));
	else
	{
		if (!command[i + 1])
		{
			sort_env(&cmd->env_lst);
			print_sorted_env(&cmd->env_lst);
			return (EXIT_SUCCESS);
		}
		i++;
		while (command[i] != NULL)
		{
			if (!ft_strncmp(command[i], "=", ft_strlen(command[i])))
				export_error(command[i]);
			else if (ft_strncmp(command[i], " ", 1) != 0 && ft_strncmp(command[i], "", ft_strlen(command[i]) != 0))
			{
				if (ft_strchr(command[i], '=') != NULL)
					str = ft_split(command[i], '=');
				else
					str = ft_split(command[i], ' ');
				if (check_param(command[i]) == 0 && var_exists((*tmp)->env_lst, str[0]) == 0)
					new_node_env(cmd, &(*tmp)->env_lst, str, command[i]);
				else if (var_exists((*tmp)->env_lst, str[0]) == 1)
				{
					unset_if_export(cmd, str[0]);
					new_node_env(cmd, &(*tmp)->env_lst, str, command[i]);
				}
				free_arr(str);
			}
			i++;
		}
		update_envp_copy(cmd);
	}
	return (EXIT_SUCCESS);
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

char	**var_arr(t_shell *cmd, char *command)
{
	char	**str_arr;
	int		i;
	char *str;
	i = 0;
	str_arr = ft_split(command, '=');
	while (str_arr[i] != 0)
	{
		if (str_arr[i][0] == '$')
		{
			str = ft_substr(str_arr[i], 1, ft_strlen(str_arr[i]));
			free(str_arr[i]);
			str_arr[i] = look_into_envir_export(cmd, str);
			if (str_arr[i] == NULL)
				str_arr[i] = ft_strdup("");
			free(str);			
		}
		i++;
	}
	return (str_arr);
}
