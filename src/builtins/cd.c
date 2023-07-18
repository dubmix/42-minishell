/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:21:08 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/17 12:57:12 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_dir_name()
{
	int i;

	i = 0;
	while()
	{
		if (ft_strncmp)
	}
}

int change_directory()
{
	char *tmp;
	int		ret;

	tmp = get_dir_name()
	ret = chdir(tmp); //returns 0 if success, -1 if error
	free(tmp);

	return (ret);
}

void add_path_to_env()
{
	
}

void change_path()
{
	char *tmp;

	getcwd
}
int cd
{
	
	ret = chdir(path)
	if (ret != 0)
		return (EXIT_FAILURE); // exit_failure value = 8;
	add_path_to_env();
	return (EXIT_SUCCESS);
}
