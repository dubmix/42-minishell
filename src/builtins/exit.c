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

void get_exit_code(char **str)
{
	int exit_code;

	exit_code = 255;
	free(str);
	exit(exit_code);
}

void	free_all()
{

}

int	exit()
{
	char **str;

	printf("exit");	
	free_all();
	get_exit_code(str);
	return (EXIT_SUCCESS);
}
