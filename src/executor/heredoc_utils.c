/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:44:56 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/13 12:07:14 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*double_quote_env_heredoc(t_shell *cmd, char *string)
{
	char	**arr_var;
	char	*new_string;
	char 	*temp;
	int i;

	i = 0;
	arr_var = string_variables_heredoc(cmd, string);
	new_string = (char *)malloc(sizeof(char) * (length_arr_var(arr_var, cmd)
				+ length_string_without_var(string)) + 1);
	if (!new_string)
		ft_error(cmd, "Memory allocation failed for expander", 1);
	new_string = double_quote_env_bis(string, new_string, arr_var, i);
	free_arr(arr_var);
	temp = ft_strjoin(new_string, "\n");
	free(new_string);
	if (ft_strncmp(temp, "\n", 1) == 0)
		return (NULL);
	return (temp);
}