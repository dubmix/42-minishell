/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:04:33 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/14 10:13:24 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_single_cmd	*triage_cmd_redir(t_shell *cmd)
{
	t_token			*temp;
	t_single_cmd	*cmd_lst;
	int				index_node;
	t_token			*next_start;

	index_node = 0;
	cmd_lst = NULL;
	temp = (cmd->tok_lst);
	while (temp != NULL && index_node != cmd->nb_of_pipes + 1)
	{
		next_start = new_node_cmd(&cmd_lst, index_node, temp, cmd);
		while (temp != next_start && temp != NULL)
			temp = temp->next;
		if (temp != NULL)
			temp = temp->next;
		index_node++;
	}
	cmd->cmd_alloc = 1;
	return (cmd_lst);
}

int	init_node_cmd(t_single_cmd **new, t_shell *cmd, int index, int i)
{
	(*new) = (t_single_cmd *)malloc(sizeof(t_single_cmd));
	(*new)->command = (char **)malloc(sizeof(char *) * 
			(cmd->words_per_pipe[index] + 1));
	if (!(*new) || !(*new)->command)
		ft_error(cmd, "New node creation failure", 1);
	(*new)->append_str = NULL;
	(*new)->redir_in_str = NULL;
	(*new)->redir_out_str = NULL;
	(*new)->append = 0;
	(*new)->redir_in = 0;
	(*new)->redir_out = 0;
	i = 0;
	return (i);
}

t_token	*new_node_cmd(t_single_cmd **cmd_lst, int index, 
	t_token *tok_lst, t_shell *cmd)
{
	t_single_cmd	*new;
	t_token			*temp;
	int				i;

	temp = tok_lst;
	i = init_node_cmd(&new, cmd, index, i);
	while (temp != NULL && temp->type != PIPE)
	{
		if ((temp->type == WORD) && i < cmd->words_per_pipe[index])
			i = new_node_word(temp, new, i);
		else if (temp->type == 7 || temp->type == 6 
			|| temp->type == 8 || (temp->type == 9 && temp->next != NULL))
		{
			if (temp->type == 7 || temp->type == 6 || temp->type == 8)
				handle_redir_in_out(new, temp);
			temp = temp->next;
			if (temp->next != NULL && !ft_strncmp(temp->next->command, " ", 
					ft_strlen(temp->next->command)))
				temp = temp->next;
		}
		if (temp != NULL)
			temp = temp->next;
	}
	new_node_cmd_sub(new, i, index, cmd_lst);
	return (temp);
}

int	new_node_word(t_token *temp, t_single_cmd *new, int i)
{
	if (ft_strncmp(temp->command, "", ft_strlen(temp->command)))
		new->command[i] = ft_strdup(temp->command);
	else
		new->command[i] = ft_strdup("");
	i++;
	return (i);
}

void	new_node_cmd_sub(t_single_cmd *new, int i, int index, 
	t_single_cmd **cmd_lst)
{
	new->next = NULL;
	new->command[i] = 0;
	new->index = index;
	add_stack_back_cmd(cmd_lst, new);
}
