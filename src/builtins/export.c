/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:29:20 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/03 15:40:27 by edrouot          ###   ########.fr       */
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
	char    **str;
	t_shell **tmp;
	int i;

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
			if (check_param(command[i]) == 0 &&
					var_exists((*tmp)->env_lst, str[0]) == 0)
				new_node_env(&(*tmp)->env_lst, str, command[i]);
			free_arr(str);
		}
		i++;
	}
	update_envp_copy(cmd);
	return (EXIT_SUCCESS);
}

void print_chararr(char **envp)
{
	int i;
	
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	update_envp_copy(t_shell *cmd)
{
	t_env *temp;
	int i;

	free_arr(cmd->envp_copy);
	cmd->envp_copy = (char **)malloc(sizeof(char *) * (ft_lstsize_test(cmd->env_lst) + 1));
	temp = cmd->env_lst;
	i = 0;
	while(temp)
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
	return(EXIT_FAILURE);
}
// can we replace it by check valid id test ? 
int check_valid_id(char c)
{
	if (c >= 32 && c <= 47)
		return (1);
	else if (c >= 58 && c <= 64)
		return (1);
	else if (c >= 91 && c <= 96)
		return (1);
	else if (c >= 123 && c <= 126)
		return (1);
	else
		return (0);
}

int var_exists(t_env *env, char *str)
{
	t_env *head;

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
	int i;

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
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void print_sorted_env(t_env **env_lst)
{
	t_env	*tmp;

	tmp = *env_lst;
	int i;
	i = ft_lstsize_test(*env_lst);
	while (i > 0)
	{
		while (tmp != NULL)
		{
			if (tmp->index == i)
			{
				printf("declare -x %s\n", tmp->full_string);
				break;
			}
			tmp = tmp->next;
		}
		tmp = *env_lst;
		i--;
	}
}

void	sort_env(t_env **env_lst)
{
	t_env	*tmp;

	tmp = *env_lst;
	int i;
	i = 1;
	char *string;
	
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

	tmp = *env_lst;
	int length;
	while (tmp != NULL)
	{
		if (ft_strlen(string) > ft_strlen(tmp->name))
			length = ft_strlen(string);
		else
			length = ft_strlen(tmp->name);

		if (ft_strncmp(string, tmp->name, length) == 0)
		{
			tmp->index = i;
			return;
		}
		tmp = tmp->next;

	}
	return ;
}


char *find_biggest(t_env **env_lst)
{
	t_env	*tmp;

	tmp = *env_lst;
	char *string;
	string = NULL;

	while (tmp != NULL)
	{
		if (string == NULL && tmp->index == 0)
			string = ft_strdup(tmp->name);
		else if (ft_strncmp(string, tmp->name, ft_strlen(string)) < 0 && tmp->index == 0)
		{
			free(string);
			string = ft_strdup(tmp->name);
		}
		if (tmp != NULL)
			tmp = tmp->next;
		// printf("HERE %s\n", string);
	}
	return (string);
}