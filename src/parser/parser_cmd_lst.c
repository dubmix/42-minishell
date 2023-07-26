#include "../../minishell.h"

t_single_cmd	*triage_cmd_redir(t_shell *cmd)
{
	t_token	**temp;
	t_single_cmd *cmd_lst;
	cmd_lst = NULL;

	temp = &(cmd->tok_lst);
	int index_node = 0;
	while ((*temp) != NULL && index_node != cmd->pipe_number + 1)
	{
		(*temp) = new_node_cmd(&cmd_lst, index_node, *temp, cmd);
		index_node++;
		if ((*temp) != NULL)
			(*temp) = (*temp)->next;
	}
	return (cmd_lst);
}

void init_node_cmd(t_single_cmd **new, t_shell *cmd, int index)
{
	(*new) = (t_single_cmd *)malloc(sizeof(t_single_cmd));
	(*new)->command = (char **)malloc(sizeof(char *) * cmd->words_per_pipe[index] + 1);
	if (!(*new) || !(*new)->command)
		return ; // error handling
	(*new)->append_str = NULL;
	(*new)->redir_in_str = NULL;
	(*new)->redir_out_str = NULL;
}

t_token	*new_node_cmd(t_single_cmd **cmd_lst, int index, t_token *tok_lst, t_shell *cmd)
{
	t_single_cmd	*new;
	t_token *temp;
	int i;

	i = 0;
	temp = tok_lst;
	new = NULL;
	init_node_cmd(&new, cmd, index);
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type == WORD)
		{
			new->command[i] = ft_strdup(temp->command);
			i++;
		}
		if (temp->type == REDIRECT_INPUT)
		{
			handle_redir_in(new, temp->next);
			new->redir_in = 1;
			temp = temp->next;
		}
		else if (temp->type == REDIRECT_OUTPUT)
		{
			handle_redir_out(new, temp->next, 1);
			new->redir_out = 1;
			temp = temp->next;
		}
		else if (temp->type == HEREDOC)
			temp = temp->next->next;
		else if (temp->type == APPEND)
		{
			handle_redir_out(new, temp->next, 2);
			new->append = 1;
			temp = temp->next;
		}
		if (temp != NULL)
			temp = temp->next;
	}
	new->next = NULL;
	new->command[i] = 0;
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

