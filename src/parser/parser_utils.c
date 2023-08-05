/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:24:27 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/06 00:07:34 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	delete_node_tok(t_token **head, t_token *nodeToDelete)
{
	t_token	*prev_node;

	prev_node = NULL;
	if (*head == NULL || nodeToDelete == NULL)
		return ;
	if (*head == nodeToDelete)
		*head = nodeToDelete->next;
	else
	{
		prev_node = *head;
		while (prev_node->next != NULL && prev_node->next != nodeToDelete)
			prev_node = prev_node->next;
		if (prev_node->next == nodeToDelete)
			prev_node->next = nodeToDelete->next;
		else
			return ;
	}
	free(nodeToDelete->command);
	free(nodeToDelete);
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

void	print_list_commands(t_single_cmd *cmd, t_shell *shell)
{
	t_single_cmd	*tmp;
	int				i;
	int				j;

	i = 0;
	j = 0;
	tmp = cmd;
	printf("printing commands %d\n", shell->nb_of_pipes);
	while (tmp)
	{
		printf("node is %d : \n", tmp->index);
		printf("redir_in is %d : %s\n", tmp->redir_in, tmp->redir_in_str);
		printf("redir_out is %d : %s\n", tmp->redir_out, tmp->redir_out_str);
		printf("append is %d : %s,\n", tmp->append, tmp->append_str);
		printf("Command are %s \n", tmp->command[i]);

		while (tmp->command[i] != NULL)
		{
			printf("Command are %s \n", tmp->command[i]);
			i++;
		}
		j++;
		i = 0;
		tmp = tmp->next;
	}
}
