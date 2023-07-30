/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:32:47 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/30 12:34:45 by edrouot          ###   ########.fr       */
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
			// printf("FINAL LINE IS %s", final_line);
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


// int	create_heredoc(char **heredoc, char *file_name)
// {
// 	int fd;
// 	char *line;
// 	int i;

// 	fd = open(file_name, O_CREAT);
// 	line = readline(">");
// 	while(line && ft_strncmp(heredoc[i], line, ft_strlen(heredoc[i])) != 0) // tant que EOF n'est pas detecte
// 	{
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 		line = readline(">");
// 	}
// 	free(line);
// 	close(fd);
// 	return (EXIT_SUCCESS);
// }

// char *create_heredoc_filename(void)
// {
// 	int i;

// 	i = 0;
// 	char *file_name;
	
// 	file_name = ft_strjoin("build/.tmp_heredoc_file_", "");
// 	return (file_name);
// }

// int ft_heredoc(t_shell *shell)
// {
// 	char *file_name;
// 	int ret;

// 	file_name = create_heredoc_filename();
// 	shell->nb_of_heredocs = 1; //flag for in heredoc
// 	ret = create_heredoc(file_name);
// 	shell->nb_of_heredocs = 0;
// 	return (ret);
// }

// create_heredoc


// int	exec_heredoc(t_shell *shell)
// {
// 	int ret;

// 	ret = EXIT_SUCCESS;
// 	//cmd->redirections?
// 	ret = ft_heredoc(shell, shell->tok_lst->redirections);
// 	return (EXIT_SUCCESS);
// }
