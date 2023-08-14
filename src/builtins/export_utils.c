/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:44:34 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/14 09:44:35 by pdelanno         ###   ########.fr       */
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

// void	print_chararr(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	if (arr == 0)
// 		return ;
// 	while (arr[i] != 0)
// 	{
// 		ft_putstr_fd(arr[i], STDERR_FILENO);
// 		printf("'%s'\n", arr[i]);
// 		i++;
// 	}
// }

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
	free(new);
	return (new_line);
}

char	**var_arr(t_shell *cmd, char *command)
{
	char	**str_arr;
	int		i;
	char	*str;

	i = 0;
	str_arr = ft_split(command, '=');
	while (str_arr[i] != 0)
	{
		if (str_arr[i][0] == '$')
		{
			str = ft_substr(str_arr[i], 1, ft_strlen(str_arr[i]));
			free(str_arr[i]);
			str_arr[i] = look_into_envir_export(cmd, str);
			if (str_arr[i] == NULL)
				str_arr[i] = ft_strdup("");
			free(str);
		}
		i++;
	}
	return (str_arr);
}
