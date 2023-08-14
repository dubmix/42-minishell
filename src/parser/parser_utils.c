/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:24:27 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/14 10:14:05 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	delete_node_tok(t_token **head, t_token *node_to_delete)
{
	t_token	*prev_node;

	prev_node = NULL;
	if (*head == NULL || node_to_delete == NULL)
		return ;
	if (*head == node_to_delete)
		*head = node_to_delete->next;
	else
	{
		prev_node = *head;
		while (prev_node->next != NULL && prev_node->next != node_to_delete)
			prev_node = prev_node->next;
		if (prev_node->next == node_to_delete)
			prev_node->next = node_to_delete->next;
		else
			return ;
	}
	free(node_to_delete->command);
	free(node_to_delete);
	return ;
}

void	adjust_number(t_shell *cmd)
{
	t_token	**temp;
	int		i;

	temp = &(cmd->tok_lst);
	i = 0;
	while (*temp != NULL)
	{
		(*temp)->index = i;
		if (ft_strncmp((*temp)->command, " ", 
				ft_strlen((*temp)->command)) == 0 && i == 0)
			i = -1;
		i++;
		if (ft_strncmp((*temp)->command, "|", ft_strlen((*temp)->command)) == 0)
			i = 0;
		temp = &((*temp)->next);
	}
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
