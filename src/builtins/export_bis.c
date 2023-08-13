/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:06:02 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/13 15:21:30 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
