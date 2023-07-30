/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:04:33 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/30 13:27:15 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_single_cmd	*triage_cmd_redir(t_shell *cmd)
{
	t_token			**temp;
	t_single_cmd	*cmd_lst;
	int				index_node;

	index_node = 0;
	cmd_lst = NULL;
	temp = &(cmd->tok_lst);
	while ((*temp) != NULL && index_node != cmd->nb_of_pipes + 1)
	{
		(*temp) = new_node_cmd(&cmd_lst, index_node, *temp, cmd);
		index_node++;
		if ((*temp) != NULL)
			(*temp) = (*temp)->next;
	}
	free(cmd->words_per_pipe);
	return (cmd_lst);
}

void	init_node_cmd(t_single_cmd **new, t_shell *cmd, int index)
{
	(*new) = (t_single_cmd *)malloc(sizeof(t_single_cmd));
	(*new)->command = (char **)malloc(sizeof(char *) * 
			(cmd->words_per_pipe[index] + 1));
	if (!(*new) || !(*new)->command)
		return;// error handling
	(*new)->append_str = NULL;
	(*new)->redir_in_str = NULL;
	(*new)->redir_out_str = NULL;
}

t_token	*new_node_cmd(t_single_cmd **cmd_lst, int index, 
	t_token *tok_lst, t_shell *cmd)
{
	t_single_cmd	*new;
	t_token			*temp;
	int				i;

	i = 0;
	temp = tok_lst;
	new = NULL;
	init_node_cmd(&new, cmd, index);
	while (temp != NULL && temp->type != PIPE)
	{
		if ((temp->type == WORD) && i < cmd->words_per_pipe[index])
		{
			new->command[i] = ft_strdup(temp->command);
			i++;
		}
		else if (temp->type == REDIRECT_INPUT || temp->type == REDIRECT_OUTPUT || temp->type == APPEND)
		{
			handle_redir_in_out(new, temp->next);
			temp = temp->next;
		}
		else if (temp->type == HEREDOC)
			temp = temp->next->next;
		if (temp != NULL)
			temp = temp->next;
	}
	new->next = NULL;
	new->command[i] = NULL;
	new->index = index;
	add_stack_back_cmd(cmd_lst, new);
	return (temp);
}

void	add_stack_back_cmd(t_single_cmd **cmd_lst, t_single_cmd *new)
{
	t_single_cmd	*tail;

	if (!new)
		return ;
	if (!(*cmd_lst))
	{
		*cmd_lst = new;
		return ;
	}
	tail = *cmd_lst;
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	tail->next = new;
}
