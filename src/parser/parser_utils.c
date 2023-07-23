#include "../../minishell.h"

void	deleteNode(t_token **head, t_token *nodeToDelete)
{
	t_token *prevNode;

	prevNode = NULL;
	if (*head == NULL || nodeToDelete == NULL)
		return ;
	if (*head == nodeToDelete)
		*head = nodeToDelete->next;
	else
	{
		prevNode = *head;
		while (prevNode->next != NULL && prevNode->next != nodeToDelete)
			prevNode = prevNode->next;
		if (prevNode->next == nodeToDelete)
			prevNode->next = nodeToDelete->next;
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
		temp = &((*temp)->next);
		i++;
	}
	cmd->number_token = i;
}
