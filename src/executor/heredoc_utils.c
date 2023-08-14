/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:44:56 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/14 10:15:52 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*double_quote_env_heredoc(t_shell *cmd, char *string)
{
	char	**arr_var;
	char	*new_string;
	char	*temp;
	int		i;

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

char	**string_var_hd_sub(t_shell *cmd, char *str, char **arr_str, int start)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			start = i + 1;
			while (str[i] != '\0' && str[i] != ' ')
				i++;
			string = ft_substr(str, start, i - start);
			arr_str[j] = look_into_envir_quote(cmd, string);
			j++;
		}
		if (str[i] != '\0')
			i++;
	}
	arr_str[j] = 0;
	return (arr_str);
}
