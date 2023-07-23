/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:14:26 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/19 11:13:14 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit(t_env *env, t_single_cmd *single_cmd)
{
	char **str;

	printf("exit");
	if (single_cmd->str[1] && single_cmd->str[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	str =  ft_arrdup(single_cmd->str);
	free_env(env);
	get_exit_code(str);
	return (EXIT_SUCCESS);
}

void get_exit_code(char **str)
{
	int exit_code;

	if (str[1] == '\0')
		exit_code = 0;
	else if (is_only_digits(str[1]) != 0)
		exit_code = ft_atoi(str[1]);
	else
	{
		printf("minishell: exit: %s: numeric argument required\n");
		exit_code = 255;
	}		
	free_arr(str);
	exit(exit_code);
}

int is_only_digits(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

void	free_all()
{

}
