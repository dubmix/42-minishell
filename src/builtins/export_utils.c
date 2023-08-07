/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:44:34 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/07 16:55:57 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_error(char *str)
{
	printf("minishell: export: '%s': not a valid identifier\n", str);
	return (EXIT_FAILURE);
}

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

int	check_valid_id(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') 
		|| (c >= '0' && c <= '9') || (c == '_'))
		return (0);
	else
		return (1);
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
