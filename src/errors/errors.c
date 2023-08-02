#include "../../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
// void	free_arr_int(int *arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		free((void*)arr[i]);
// 		i++;
// 	}
// 	free((void)arr);
// }

void	free_all(t_shell *cmd, int type)
{
	//type = 0 -> free tok_lst
	//type = 1 -> free cmd->lst
	//type = 2 -> free tok_lst + cmd_lst
	// type = 3 -> free env_lst

	//to free : tok_lst        cmd_lst       env_lst 

	if (type == 0)
		free_tok_lst(&cmd->tok_lst);
	else if (type == 1)
		free_cmd_lst(&cmd->cmd_lst);
	else if (type == 2)
	{
		free_tok_lst(&cmd->tok_lst);
		free_cmd_lst(&cmd->cmd_lst);
	}
	else if (type == 3)
	{
		free_env_lst(&cmd->env_lst);
		free_arr(cmd->envp_copy);
		free(cmd->oldpwd);
	}
	else if (type == 4)
		free_shell(cmd);
}

void free_shell(t_shell *cmd)
{
	free_tok_lst(&cmd->tok_lst);
	free_cmd_lst(&cmd->cmd_lst);
	cmd->size_arr_var = 0;
	if (cmd->nb_of_heredocs != 0)
	{
		free_arr(cmd->heredoc_arr);
		free(cmd->heredoc_string);
	}
	cmd->nb_of_heredocs = 0;
	cmd->nb_of_pipes = 0;
	cmd->nb_of_tokens = 0;
	cmd->nb_of_heredocs = 0;
	//cmd->exit_flag = 0;
}

void delete_all_nodes(t_token **head) 
{
    t_token *current = *head;
    t_token *next;

    while (current != NULL) {
        next = current->next;
        delete_node_tok(head, current);
        current = next;
    }
}

void	free_tok_lst(t_token **tok_lst)
{
	t_token *current = *tok_lst;
	t_token	*next;
	
	while (current != NULL)
	{
			next = current->next;
			delete_node_tok(tok_lst, current);
			current = next;
	}
}

void	free_cmd_lst(t_single_cmd **cmd_lst)
{
	t_single_cmd	*nodeToDelete;
	
	nodeToDelete = NULL;
	while (*cmd_lst != NULL)
	{
			nodeToDelete = *cmd_lst;
			delete_node_cmd(cmd_lst, nodeToDelete);
	}
}

void	free_env_lst(t_env **env_lst)
{
	// t_token	**temp;
	t_env	*nodeToDelete;
	
	nodeToDelete = NULL;
	while (*env_lst != NULL)
	{
			nodeToDelete = *env_lst;
			delete_node_env(env_lst, nodeToDelete);
	}
}

void	delete_node_cmd(t_single_cmd **head, t_single_cmd *nodeToDelete)
{
	t_single_cmd *prevNode;

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
