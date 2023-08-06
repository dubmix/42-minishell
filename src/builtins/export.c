/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:29:20 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/05 22:00:49 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize_test(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	export(t_shell *cmd, char **command)
{
	char	**str;
	t_shell	**tmp;
	int		i;

	i = 1;
	tmp = &cmd;
	if (!command[i])
	{
		sort_env(&cmd->env_lst);
		print_sorted_env(&cmd->env_lst);
		return (EXIT_SUCCESS);
	}
	while (command[i] != NULL)
	{
		if (ft_strncmp(command[i], " ", 1) != 0)
		{
			str = ft_split((command[i]), '=');
			if (check_param(command[i]) == 0 && var_exists((*tmp)->env_lst,
					str[0]) == 0)
				new_node_env(cmd, &(*tmp)->env_lst, str, command[i]);
			free_arr(str);
		}
		i++;
	}
	update_envp_copy(cmd);
	return (EXIT_SUCCESS);
}

void	print_chararr(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	update_envp_copy(t_shell *cmd)
{
	t_env	*temp;
	int		i;

	free_arr(cmd->envp_copy);
	cmd->envp_copy = (char **)malloc(sizeof(char *)
		* (ft_lstsize_test(cmd->env_lst) + 1));
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

int	export_error(char *str)
{
	printf("minishell: export: '%s': not a valid identifier\n", str);
	return (EXIT_FAILURE);
}

// can we replace it by check valid id test ?
int	check_valid_id(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || (c == '_'))
		return (0);
	else
		return (1);
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
	if (str[i] == '=')
		return (EXIT_FAILURE);
	if (ft_isdigit(str[i]))
		return (export_error(str));
	if (ft_findchar(str, '=') == 0)
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

void	print_sorted_env(t_env **env_lst)
{
	t_env	*tmp;
	int		i;

	tmp = *env_lst;
	i = ft_lstsize_test(*env_lst);
	while (i > 0)
	{
		while (tmp != NULL)
		{
			if (tmp->index == i)
			{
				printf("declare -x %s\n", tmp->full_string);
				break ;
			}
			tmp = tmp->next;
		}
		tmp = *env_lst;
		i--;
	}
}

void	sort_env(t_env **env_lst)
{
	char	*string;
	int		i;

	// t_env	*tmp; // au final I dont use it
	// tmp = *env_lst;
	i = 1;
	while (i < ft_lstsize_test(*env_lst))
	{
		string = find_biggest(env_lst);
		assign_index(env_lst, string, i);
		free(string);
		i++;
	}
}

void	assign_index(t_env **env_lst, char *string, int i)
{
	t_env	*tmp;
	int		length;

	tmp = *env_lst;
	while (tmp != NULL)
	{
		if (ft_strlen(string) > ft_strlen(tmp->name))
			length = ft_strlen(string);
		else
			length = ft_strlen(tmp->name);
		if (ft_strncmp(string, tmp->name, length) == 0)
		{
			tmp->index = i;
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

char	*find_biggest(t_env **env_lst)
{
	t_env *tmp;

	tmp = *env_lst;
	char *string;
	string = NULL;

	while (tmp != NULL)
	{
		if (string == NULL && tmp->index == 0)
			string = ft_strdup(tmp->name);
		else if (ft_strncmp(string, tmp->name, ft_strlen(string)) < 0
			&& tmp->index == 0)
		{
			free(string);
			string = ft_strdup(tmp->name);
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
	return (string);
}