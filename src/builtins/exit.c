/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:14:26 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/17 13:23:59 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
