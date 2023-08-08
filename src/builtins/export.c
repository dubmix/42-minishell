/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:29:20 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/08 13:08:23 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **var_arr(t_shell *cmd, char *command);

int	export(t_shell *cmd, char **command)
{
	char	**str;
	t_shell	**tmp;
	int		i;

	i = 0;
	tmp = &cmd;
	print_list_commands(cmd->cmd_lst, cmd);
	if (!command[i+1])
	{
		sort_env(&cmd->env_lst);
		print_sorted_env(&cmd->env_lst);
		return (EXIT_SUCCESS);
	}
	while (command[i++] != NULL)
	{
		if (ft_strncmp(command[i], " ", 1) != 0)
		{
			str = var_arr(cmd, command[i]);
			// str = ft_split(command[i], '=');
			if (check_param(command[i]) == 0
				&& var_exists((*tmp)->env_lst, str[0]) == 0)
				new_node_env(cmd, &(*tmp)->env_lst, str, command[i]);
			free_arr(str);
		}
	}
	update_envp_copy(cmd);
	return (EXIT_SUCCESS);
}

char **var_arr(t_shell *cmd, char *command)
{
	char **str_arr;
	int i;
	int j;

	i = 0;
	j = 0;
	str_arr = ft_split(command, '=');
	while (str_arr[i] != 0)
	{
		str_arr[i] = double_quote_env_heredoc(cmd, str_arr[i]);
		i++;
	}
	return (str_arr);
}

void	update_envp_copy(t_shell *cmd)
{
	t_env	*temp;
	int		env;
	int		i;

	free_arr(cmd->envp_copy);
	env = ft_lstsize_env(cmd->env_lst);
	cmd->envp_copy = (char **)malloc(sizeof(char *) * (env + 1));
	temp = cmd->env_lst;
	i = 0;
	while (temp)
	{
		cmd->envp_copy[i] = ft_strdup(temp->full_string);
		i++;
		temp = temp->next;
	}
	cmd->envp_copy[i] = 0;
}

int	var_exists(t_env *env, char *str)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (ft_strncmp(head->name, str, ft_strlen(str)) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

int	check_param(char *str)
{
	int	i;

	i = 0;
	if (ft_findchar(str, '=') == 0)
		return (EXIT_FAILURE);
	if (str[i] == '=')
		return (export_error(str));
	if (ft_isdigit(str[i]))
		return (export_error(str));
	while (str[i] != '=')
	{
		if (check_valid_id(str[i]) == 1)
			return (export_error(str));
		i++;
	}
	return (0);
}

int	ft_findchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
