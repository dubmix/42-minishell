/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:53:28 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/13 14:42:10 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_sorted_env(t_env **env_lst)
{
	t_env	*tmp;
	int		i;

	tmp = *env_lst;

	i = ft_lstsize_env(*env_lst);
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

	i = 1;
	assign_back_to_zero(env_lst);
	while (i < ft_lstsize_env(*env_lst))
	{
		string = find_biggest(env_lst);
		assign_index(env_lst, string, i);
		free(string);
		i++;
	}
}

void	assign_back_to_zero(t_env **env_lst)
{
	t_env	*tmp;

	tmp = *env_lst;
	while (tmp != NULL)
	{
		tmp->index = 0;
		tmp = tmp->next;
	}
	return ;
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
	t_env	*tmp;
	char	*string;

	tmp = *env_lst;
	string = NULL;
	while (tmp != NULL)
	{
		if (string == NULL && tmp->index == 0)
			string = ft_strdup(tmp->name);
		else if (ft_strncmp(string, tmp->name,
				ft_strlen(string)) < 0 && tmp->index == 0)
		{
			free(string);
			string = ft_strdup(tmp->name);
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
	return (string);
}
