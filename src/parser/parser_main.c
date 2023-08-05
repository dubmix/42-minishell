/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:01:11 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/05 14:30:07 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	number_heredocs(t_shell *cmd);

void	parser(t_shell *cmd)
{
	triage_quotes(cmd);
	adjust_number(cmd);
	triage_space(cmd);
	triage_space_redir(cmd);
	adjust_number(cmd);
	number_words_per_pipe(cmd);
	if (cmd->nb_of_heredocs != 0)
	{
		number_heredocs(cmd);
		grab_heredoc(cmd);
	}
	cmd->cmd_lst = triage_cmd_redir(cmd);
}

void	number_heredocs(t_shell *cmd)
{
	t_token	*temp;
	int		k;

	k = 0;
	temp = cmd->tok_lst;
	cmd->heredoc_arr = (char **)malloc(sizeof(char *) * 
			(cmd->nb_of_heredocs + 1));
	if (!cmd->heredoc_arr)
		ft_error(cmd, "Heredoc memory allocation failure");
	while (temp != NULL)
	{
		if (temp->type == HEREDOC)
		{
			cmd->heredoc_arr[k] = ft_strdup(temp->next->command);
			k++;
		}
		temp = temp->next;
	}
	if (cmd->nb_of_heredocs != 0)
		cmd->heredoc_arr[k] = 0;
}

void	number_words_per_pipe(t_shell *cmd)
{
	t_token	*temp;
	int		i;
	int		j;

	temp = cmd->tok_lst;
	cmd->words_per_pipe = (int *)malloc(sizeof(int) * (cmd->nb_of_pipes + 1));
	if (!cmd->words_per_pipe)
		ft_error(cmd, "Int array memory allocation failure");
	i = 0;
	while (temp != NULL)
	{
		j = 0;
		while (temp != NULL && temp->type != PIPE)
		{
			if (temp->type == APPEND || temp->type == REDIRECT_OUTPUT
				|| temp->type == REDIRECT_INPUT || temp->type == HEREDOC)
				temp = temp->next;
			else if (temp->type == WORD)
				j++;
			temp = temp->next;
		}
		cmd->words_per_pipe[i++] = j;
		if (temp != NULL)
			temp = temp->next;
	}
}
