#include "../../minishell.h"

void	delete_node_tok(t_token **head, t_token *nodeToDelete)
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
		if (ft_strncmp((*temp)->command, " ", ft_strlen((*temp)->command)) == 0 && i == 0)
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

	tmp = cmd;
	int i = 0;
	int j = 0;
	printf(" NOT IMPORTANT.%d\n", shell->nb_of_pipes);
	while (tmp)
	{
		printf("node is %d : \n, redir_in is %d : %s\n, redir_out is %d : %s\n, append is %d : %s,\n", tmp->index, tmp->redir_in, tmp->redir_in_str,  tmp->redir_out, tmp->redir_out_str, tmp->append, tmp->append_str);
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