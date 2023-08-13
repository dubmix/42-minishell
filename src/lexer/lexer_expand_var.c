/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:45:38 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/13 15:26:36 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**string_variables(t_shell *cmd, t_token *var)
{
	char	**arr_string;
	int		i;

	i = 0;
	cmd->size_arr_var = countsubstr(var->command, '$');
	arr_string = (char **)malloc(sizeof(char *) * (cmd->size_arr_var + 1));
	if (!arr_string)
		ft_error(cmd, "Memory allocation failed for expander", 1);
	arr_string = string_variables_bis(cmd, var->command, arr_string, i);
	return (arr_string);
}

char	**string_variables_bis(t_shell *cmd, char *command,
		char **arr_string, int i)
{
	int		j;
	int		start;
	char	*string;

	j = 0;
	start = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '$')
		{
			i++;
			start = i;
			while (command[i] != '\0' && !check_valid_id(command[i])
				&& command[i] != '$')
				i++;
			if (command[i] == '$' && command[i - 1] != '$')
				i = i - 1;
			string = ft_substr(command, start, i - start);
			arr_string[j] = look_into_envir_quote(cmd, string);
			if (arr_string[j] == NULL)
				arr_string[j] = ft_strdup("");
			free(string);
			j++;
		}
		i++;
	}
	arr_string[j] = 0;
	return (arr_string);
}

void	double_quote_env(t_shell *cmd, t_token *var)
{
	char	**arr_var;
	char	*new_string;
	int		i;

	i = 0;
	arr_var = string_variables(cmd, var);
	new_string = (char *)malloc(sizeof(char) * (length_arr_var(arr_var, cmd)
				+ length_string_without_var(var->command)) + 1);
	if (!new_string)
		ft_error(cmd, "Memory allocation failed for expander", 1);
	new_string = double_quote_env_bis(var->command, new_string, arr_var, i);
	free_arr(arr_var);
	free(var->command);
	var->command = ft_strdup(new_string);
	free(new_string);
}

char	*double_quote_env_bis(char *command, char *new_string, 
		char **arr_var, int i)
{
	int		j;
	int		k;
	int		n;

	j = 0;
	k = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '$')
		{
			i++;
			n = 0;
			while (command[i] != '\0' && !check_valid_id(command[i])
				&& command[i] != '$')
				i++;
			i = double_quote_env_bis_sub(command, i);
			// if ((command[i] == '?' && (command[i + 1] == ' ' 
			// 		|| command[i + 1] == '\0')) || (command[i] == '$'))
			// 	i++;
			while (arr_var[k][n] != '\0')
				new_string[j++] = arr_var[k][n++];
			k++;
		}
		else
			new_string[j++] = command[i++];
	}
	new_string[j] = '\0';
	return (new_string);
}

int	double_quote_env_bis_sub(char *command, int i)
{
	if ((command[i] == '?' && (command[i + 1] == ' ' 
				|| command[i + 1] == '\0')) || (command[i] == '$'))
		i++;
	return (i);
}
