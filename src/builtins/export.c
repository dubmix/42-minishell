/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:29:20 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/08 22:12:47 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **var_arr(t_shell *cmd, char *command);
char *look_into_envir_export(t_shell *cmd, char *string);
void unset_if_export(t_shell *cmd, char *command);

char **new_line(char *line)
{
	char **new_line;
	char *new;
	int i;

	i = ft_strlen(line);
	while (line[i] != '|' && i > 0)
		i--;
	new = ft_substr(line, 0, ft_strlen(line) - i);
	new_line = ft_split(new, ' ');
	return (new_line);
}

int	export(t_shell *cmd, char **command)
{
	char	**str;
	t_shell	**tmp;
	int		i;

	i = 0;
	tmp = &cmd;
	if (ft_strchr(cmd->line, '$'))
	{
		free_arr(command);
		command = new_line(cmd->line);
	}
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
			free(command[i]);
			command[i] = ft_strjoin(ft_strjoin(str[0], "="), str[1]);
			if (check_param(command[i]) == 0 && var_exists((*tmp)->env_lst, str[0]) == 0)
				new_node_env(cmd, &(*tmp)->env_lst, str, command[i]);
			else if (var_exists((*tmp)->env_lst, str[0]) == 1)
			{
				unset_if_export(cmd, str[0]);
				new_node_env(cmd, &(*tmp)->env_lst, str, command[i]);
			}
			free_arr(str);
		}
	}
	update_envp_copy(cmd);
	return (EXIT_SUCCESS);
}

void unset_if_export(t_shell *cmd, char *command)
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
	char **str_arr;
	int i;

	i = 0;
	str_arr = ft_split(command, '=');
	while (str_arr[i] != 0)
	{
		if (str_arr[i][0] == '$')
			str_arr[i] = look_into_envir_export(cmd, ft_substr(str_arr[i], 1, ft_strlen(str_arr[i])));
		i++;
	}
	return (str_arr);
}

char *look_into_envir_export(t_shell *cmd, char *string)
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
	env = ft_lstsize_test(cmd->env_lst);
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
