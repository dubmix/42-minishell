/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:29:20 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/10 10:16:07 by pdelanno         ###   ########.fr       */
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
			command[i] = ft_strjoin(ft_strjoin(str[0], "="), str[1]);
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
			 if (ft_strncmp(command[i], " ", 1) != 0 
				&& ft_strncmp(command[i], "", ft_strlen(command[i]) != 0))
			{
				str = var_arr(cmd, command[i]);
				free(command[i]);
				command[i] = ft_strjoin(ft_strjoin(str[0], "="), str[1]); //ici segfault avec lol = lol
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

char **var_arr(t_shell *cmd, char *command)
{
	char	**str_arr;
	int		i;

	i = 0;
	str_arr = ft_split(command, '=');
	while (str_arr[i] != 0)
	{
		if (str_arr[i][0] == '$')
			str_arr[i] = look_into_envir_export(cmd, 
					ft_substr(str_arr[i], 1, ft_strlen(str_arr[i])));
		i++;
	}
	return (str_arr);
}