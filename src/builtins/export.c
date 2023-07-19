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

int	export_error(char *str)
{
	printf("minishell: export: '%s': not a valid identifier", str);
	return(EXIT_FAILURE);
}

int check_valid_id(char c)
{
	if (c >= 32 && c <= 47)
		return (FALSE);
	else if (c >= 58 && c <= 64)
		return (FALSE);
	else if (c >= 91 && c <= 96)
		return (FALSE);
	else if (c >= 123 && c <= 126)
		return (FALSE);
	else
		return (TRUE);
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
		if (check_valid_id(str[i]) == FALSE)
			return (export_error(str));
		i++;
	}
	return (EXIT_SUCCESS);
}

int var_ex(t_env *env, char *str)
{
	t_env *head;

	head = env;
	while (head)
	{
		if (ft_strcmp(head->name, str) == 1)
			return (1);
		head = head->next;
	}
	return (0);
}

int	export(t_shell *cmd)
{
	char    **str;
	t_shell **tmp;

	tmp = &cmd;
	while ((*tmp)->tokens != NULL)
	{
		while ((*tmp)->env_lst != NULL)
		{
			str = ft_split(((*tmp)->tok_lst->command), "=");
			if (check_param((*tmp)->tok_lst->command) == 0 
					&& var_ex((*tmp)->env_lst, str[0]) == 0)
			{
				new_node_env((*tmp)->envir, str);
				free_array(str);
				break ;
			}
			(*tmp)->env_lst = (*tmp)->env_lst->next;
			free_array(str);
		}
	}
	return (EXIT_SUCCESS);
}
