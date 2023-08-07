/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:44:56 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/07 17:35:12 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*double_quote_env_heredoc(t_shell *cmd, char *string)
{
	char	**arr_var;
	char	*new_string;

	arr_var = string_variables_heredoc(cmd, string);
	new_string = (char *)malloc(sizeof(char) * (length_arr_var(arr_var, cmd)
				+ length_string_without_var(string)) + 1);
	if (!new_string)
		return (NULL);
	new_string = double_quote_env_hd_sub(string, new_string, arr_var);
	new_string = ft_strjoin(new_string, "\n");
	free(arr_var);
	return (new_string);
}

char	*double_quote_env_hd_sub(char *string, char *n_str, char **arr_var)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '$')
		{
			while (string[i] != ' ' && string[i] != 34 && string[i] != '\0')
				i++;
			n_str = ft_strjoin(n_str, arr_var[k]);
			j = ft_strlen(n_str);
			k++;
		}
		n_str[j] = string[i];
		i++;
		j++;
	}
	n_str[j] = '\0';
	return (n_str);
}
