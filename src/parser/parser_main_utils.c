/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:34:20 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/13 15:38:34 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	number_heredocs(t_shell *cmd)
{
	t_token	*temp;
	int		k;

	k = 0;
	temp = cmd->tok_lst;
	cmd->heredoc_arr = (char **)malloc(sizeof(char *) * 
			(cmd->nb_of_heredocs + 1));
	if (!cmd->heredoc_arr)
		ft_error(cmd, "Heredoc memory allocation failure", 1);
	while (temp != NULL)
	{
		if (temp->type == HEREDOC && temp->next != NULL)
		{
			cmd->heredoc_arr[k] = ft_strdup(temp->next->command);
			k++;
		}
		temp = temp->next;
	}
	if (k == 0)
	{
		cmd->nb_of_heredocs = 0;
		free_arr(cmd->heredoc_arr);
	}
	else if (cmd->nb_of_heredocs != 0)
		cmd->heredoc_arr[k] = 0;
}

void	init_words_per_pipe(t_shell *cmd)
{
	if (cmd->nb_of_pipes != 0)
	{
		cmd->words_per_pipe = (int *)malloc(sizeof(int) 
				* (cmd->nb_of_pipes + 1));
		if (!cmd->words_per_pipe)
			ft_error(cmd, "Int array memory allocation failure", 1);
	}
	else
	{
		cmd->words_per_pipe = (int *)malloc(sizeof(int) * 1);
		if (!cmd->words_per_pipe)
			ft_error(cmd, "Int array memory allocation failure", 1);
	}
	cmd->words_per_pipe_alloc = 1;
}

void	number_words_per_pipe(t_shell *cmd)
{
	t_token	*temp;
	int		i;
	int		j;

	init_words_per_pipe(cmd);
	temp = cmd->tok_lst;
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
			if (temp != NULL)
				temp = temp->next;
		}
		cmd->words_per_pipe[i] = j;
		if (temp != NULL)
			temp = temp->next;
		i++;
	}
}
