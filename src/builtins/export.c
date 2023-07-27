/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:29:20 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/19 11:13:15 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export(t_shell *cmd)
{
	char    **str;
	t_shell **tmp;

	tmp = &cmd;
	while ((*tmp)->cmd_lst)
	{
		while ((*tmp)->env_lst)
		{
			str = ft_split(((*tmp)->cmd_lst->command[1]), '=');
			if (check_param((*tmp)->cmd_lst->command[1]) == 0 
					&& var_exists((*tmp)->env_lst, str[0]) == 0)
			{
				new_node_env(&(*tmp)->env_lst, str);
				//free_array(str);
				write(1, "k", 1);
				break ;
			}
			(*tmp)->env_lst = (*tmp)->env_lst->next;
			//free_array(str);
		}
		(*tmp)->cmd_lst = (*tmp)->cmd_lst->next;
	}
	return (EXIT_SUCCESS);
}

int	export_error(char *str)
{
	printf("minishell: export: '%s': not a valid identifier", str);
	return(EXIT_FAILURE);
}

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

int	check_param(char *str)
{
	int i;

	i = 0;
	if (str[i] == '=')
		return (EXIT_FAILURE);
	 if (ft_isdigit(str[i]))
	 	return (export_error(str));
	// if (ft_findchar(str, '=') == 0)
	// 	return (export_error(str));
	// while (str[i] != '=')
	// {
	// 	if (check_valid_id(str[i]) == 1)
	// 		return (export_error(str));
	// 	i++;
	// }
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

int var_exists(t_env *env, char *str)
{
	t_env *head;

	head = env;
	while (head)
	{
		if (ft_strncmp(head->name, str, ft_strlen(str)) == 1)
			return (1);
		head = head->next;
	}
	return (0);
}