/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:32:47 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/13 15:03:15 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	grab_heredoc(t_shell *cmd)
{
	char	*line_input;
	char	*first_line;
	char	*final_line;

	final_line = ft_strdup("");
	first_line = NULL;
	line_input = NULL;
	signal(SIGINT, sigint_heredoc);
	final_line = grab_hd_sub(line_input, first_line, final_line, cmd);
	if (final_line != NULL)
	{
		cmd->heredoc_string = ft_strdup(final_line);
		free(final_line);
	}
	else
	{
		free(final_line);
		cmd->heredoc_string = ft_strdup("");
	}
	return ;
}

char	*grab_hd_sub(char *l_ipt, char *fir_l, char *fin_l, t_shell *c)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < c->nb_of_heredocs)
	{
		l_ipt = readline(HEREDOC_MSG);
		if (l_ipt == NULL)
			break ;
		else if (ft_strncmp(l_ipt, c->heredoc_arr[i],
				ft_strlen(l_ipt)) == 0 && l_ipt[0] != 0)
		{
			i++;
			free(l_ipt);
		}
		else if (i == (c->nb_of_heredocs - 1))
		{
			//grab_hd_sub_sub(l_ipt, fir_l, fin_l, c);
			fir_l = double_quote_env_heredoc(c, l_ipt);
			free(l_ipt);
			temp = ft_strjoin(fin_l, fir_l);
			free(fin_l);
			fin_l = ft_strdup(temp);
			free(temp);
			free(fir_l);
		}
		if (g_xcode == 130)
			break ;
	}
	return (fin_l);
}

char	*grab_hd_sub_sub(char *l_ipt, char *fir_l, char *fin_l, t_shell *c)
{
	char *temp;

	fir_l = double_quote_env_heredoc(c, l_ipt);
	free(l_ipt);
	temp = ft_strjoin(fin_l, fir_l);
	free(fin_l);
	fin_l = ft_strdup(temp);
	free(temp);
	free(fir_l);
	return (fin_l);
}

char	**string_variables_heredoc(t_shell *cmd, char *string)
{
	char	**arr_string;
	int		start;

	start = 0;
	cmd->size_arr_var = countsubstr(string, '$');
	arr_string = (char **)malloc(sizeof(char *) * (cmd->size_arr_var + 1));
	if (!arr_string)
		return (NULL);
	arr_string = string_var_hd_sub(cmd, string, arr_string, start);
	return (arr_string);
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
