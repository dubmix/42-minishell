/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:44:34 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/11 15:34:31 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_error(char *str)
{

	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	ft_lstsize_env(t_env *lst)
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

void	print_chararr(char **arr)
{
	int	i;

	i = 0;
	if (arr == 0)
		return ;
	while (arr[i] != 0)
	{
		ft_putstr_fd(arr[i], STDERR_FILENO);
		printf("'%s'\n", arr[i]);
		i++;
	}
}

char	**new_line(char *line)
{
	char	**new_line;
	char	*new;
	int		i;

	i = ft_strlen(line);
	while (line[i] != '|' && i > 0)
		i--;
	new = ft_substr(line, 0, ft_strlen(line) - i);
	new_line = ft_split(new, ' ');
	return (new_line);
}
