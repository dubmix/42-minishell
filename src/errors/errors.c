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

void	free_all(t_shell *cmd, int type)
{
	//type = 0 -> free tok_lst
	//type = 1 -> free cmd->lst
	//type = 2 -> free tok_lst + cmd_lst
	// type = 3 -> free env_lst
	// type = 4 -> free shell (tok_lst, cmd_lst + all value of t_shell)
	// type = 5 -> free env_lst + all the values from shell who are to be freed outside of the while loop

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
		free_env_lst(&cmd->env_lst);
	else if (type == 4)
		free_shell(cmd);
	else if (type == 5)
	{
		free_env_lst(&cmd->env_lst);
		free_arr(cmd->envp_copy);
		free(cmd->oldpwd);
	}
}

void	ft_error(t_shell *cmd, char *string, int type, int exit_code)
{
	write(2, &string, ft_strlen(string));
	if (type == 0)
		free_all(cmd, 0);
	else if (type == 1)
		free_all(cmd, 1);
	else if (type == 2)
		free_all(cmd, 2);
	else if (type == 3)
		free_all(cmd, 3);
	else if (type == 4)
		free_all(cmd, 4);
	else if (type == 5)
	{
		free_all(cmd, 1);
		free_all(cmd, 3);
	}
	else if (type == 6)
	{
		free_all(cmd, 1);
		free_all(cmd, 2);
		free_all(cmd, 3);
	}
	cmd->exit_code = exit_code;
	exit(1);
}
void free_shell(t_shell *cmd)
{
	free_tok_lst(&cmd->tok_lst);
	free_cmd_lst(&cmd->cmd_lst);
	cmd->size_arr_var = 0;
	if (cmd->nb_of_heredocs != 0)
	{
		free(cmd->heredoc_string);
	}
	cmd->nb_of_heredocs = 0;
	cmd->nb_of_pipes = 0;
	cmd->nb_of_tokens = 0;
	cmd->nb_of_heredocs = 0;
	free(cmd->tok_lst);
	free(cmd->cmd_lst);
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
	*tok_lst = NULL;
}

void	free_cmd_lst(t_single_cmd **cmd_lst)
{
	t_single_cmd *current = *cmd_lst;
	t_single_cmd	*next;
	
	while (current != NULL)
	{
			next = current->next;
			delete_node_cmd(cmd_lst, current);
			current = next;
	}
	*cmd_lst = NULL;
}

void	free_env_lst(t_env **env_lst)
{
	t_env *current = *env_lst;
	t_env	*next;
	while (current != NULL)
	{
			next = current->next;
			delete_node_env(env_lst, current);
			current = next;
	}
	*env_lst = NULL;
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
	free_arr(nodeToDelete->command);
	if (nodeToDelete->redir_in != 0)
		free(nodeToDelete->redir_in_str);
	if (nodeToDelete->redir_out != 0)
		free(nodeToDelete->redir_out_str);
	if (nodeToDelete->append != 0)
	free(nodeToDelete->append_str);
	free(nodeToDelete);
	return ;
}
