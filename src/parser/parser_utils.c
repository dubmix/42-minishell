#include "../../minishell.h"

void	delete_node(t_token **head, t_token *nodeToDelete)
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
	cmd->nb_of_tokens = i;
}

void	print_list_commands(t_single_cmd *cmd, t_shell *shell)
{
	t_single_cmd	*tmp;

	tmp = cmd;
	int i = 0;
	int j = 0;
	while (tmp)
	{
		printf("node is %d : \n, redir_in is %d : %s\n, redir_out is %d : %s\n, append is %d : %s,\n", tmp->index, tmp->redir_in, tmp->redir_in_str,  tmp->redir_out, tmp->redir_out_str, tmp->append, tmp->append_str);
		while (i < shell->words_per_pipe[j])
		{
			printf("Command are %s \n", tmp->command[i]);
			i++;
		}
		j++;
		i = 0;
		tmp = tmp->next;
	}
}