/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:32:47 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/04 16:14:11 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	grab_heredoc(t_shell *cmd)
{
	int i;
	char *line_input;
	char *first_line;
	char *second_line;
	char *final_line;
	
	second_line = NULL;
	i = 0;
	signal(SIGINT, sigint_heredoc);
	while(i < cmd->nb_of_heredocs)
	{
		line_input = readline("heredoc >");
		if(!ft_strncmp(line_input, cmd->heredoc_arr[i], ft_strlen(line_input)))
			i++;
		else if (i == (cmd->nb_of_heredocs - 1))
		{
			
			first_line = double_quote_env_heredoc(cmd, line_input);
			free(line_input);
			if (second_line == NULL)
				second_line = ft_strdup(first_line);
			else
				second_line = ft_strjoin(second_line, first_line);
			free(first_line);
			final_line = ft_strjoin(second_line, "\n");
			free(second_line);
		}
	}
	cmd->heredoc_string = ft_strdup(final_line);
	free(final_line);
	free_arr(cmd->heredoc_arr);
	return;
}

char	**string_variables_heredoc(t_shell *cmd, char *string)
{
	char	**arr_string;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = 0;
	cmd->size_arr_var = countsubstr(string, '$');
	arr_string = (char **)malloc(sizeof(char *) * (cmd->size_arr_var + 1));
	if (!arr_string)
		return (NULL);
	while (string[i] != '\0')
	{
		if (string[i] == '$')
		{
			start = i + 1;
			while (string[i] != ' ' && string[i] != '\0') 
				i++;
			arr_string[j] = look_into_envir_quote(cmd, ft_substr(string,
					start, i - start));
			j++;
		}
		i++;
	}
	arr_string[j] = 0;
	return (arr_string);
}
/*  create via string_variables an array with the correct values of the variable 
then rewrite the command line with str_join, replacing each var $XXX with the correct value*/
char *double_quote_env_heredoc(t_shell *cmd, char *string)
{
	int		i;
	char	**arr_var;
	int		j;
	char	*new_string;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	arr_var = string_variables_heredoc(cmd, string); 
	new_string = (char *)malloc(sizeof(char) * (length_arr_var(arr_var, cmd)
			+ length_string_without_var(string)) + 1);
	if (!new_string)
		return (NULL);
	while (string[i] != '\0')
	{
		if (string[i] == '$')
		{
			while (string[i] != ' ' && string[i] != 34 && string[i] != '\0')
				i++;
			new_string = ft_strjoin(new_string, arr_var[k]);
			j = ft_strlen(new_string);
			k++;
		}
		new_string[j] = string[i];
		i++;
		j++;
	}
	new_string[j] = '\0';
	free(arr_var);
	return(new_string);
}