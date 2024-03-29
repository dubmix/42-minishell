/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:32:47 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/14 10:15:58 by edrouot          ###   ########.fr       */
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
			i = grab_heredoc_tri(i, l_ipt);
		else if (i == (c->nb_of_heredocs - 1))
		{
			fir_l = double_quote_env_heredoc(c, l_ipt);
			temp = ft_strjoin(fin_l, fir_l);
			free(fin_l);
			fin_l = ft_strdup(temp);
			grab_hd_sub_sub(l_ipt, fir_l, temp);
		}
		if (g_xcode == 130)
			break ;
	}
	return (fin_l);
}

void	grab_hd_sub_sub(char *l_ipt, char *fir_l, char *temp)
{
	free(l_ipt);
	free(temp);
	free(fir_l);
}

int	grab_heredoc_tri(int i, char *l_ipt)
{
	i++;
	free(l_ipt);
	return (i);
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
