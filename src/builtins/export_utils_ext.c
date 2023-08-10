/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_ext.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:17:41 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/10 11:19:48 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*look_into_envir_export(t_shell *cmd, char *string)
{
	t_env	*tmp;

	tmp = cmd->env_lst;
	while (tmp != NULL)
	{
		if (ft_strncmp(string, "$", ft_strlen(string)) == 0)
		{
			string = ft_strdup("Process ID ");
			break ;
		}
		else if (ft_strncmp(string, "?", 1) == 0)
		{
			string = ft_strdup(ft_itoa(g_xcode));
			break ;
		}
		else if (ft_strncmp(string, tmp->name, ft_strlen(string)) == 0)
		{
			string = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	return (string);
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
		if (ft_strncmp(head->name, str, ft_strlen(head->name)) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

int	check_param(char *str)
{
	int	i;

	i = 0;
	// if (ft_findchar(str, '=') == 0)
	// 	return (EXIT_FAILURE);
	// if (str[i] == '=')
	// 	return (export_error(str));
	if (ft_isdigit(str[i]))
		return (export_error(str));
	while (str[i] != '=' && str[i] != '\0')
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
