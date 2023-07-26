#include "../../minishell.h"

void	print_list_commands(t_single_cmd *cmd, t_shell *shell);

void	parser(t_shell *cmd)
{
	triage_quotes(cmd);
	triage_space(cmd);
	adjust_number(cmd);
	number_words_per_pipe(cmd);
	cmd->cmd_lst = triage_cmd_redir(cmd);
	single_command(cmd);
	/*
	part 1 : check if there is a pipe
	part 2 : form the command in a new list --> list2array
	part 3 : put all the redirections in a separate struct --> done
	part 4 : handle two cases : pipes or single command --> single command handled
	part 5 : differentiate if the command are builtin or not
	*/
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

void	handle_redir_in(t_single_cmd *new, t_token *temp)
{
	int fd;
	if (new->redir_in_str == NULL)
		free(new->redir_in_str);
	new->redir_in_str = ft_strdup(temp->command);
	fd = open(new->redir_in_str, O_RDONLY | O_CREAT, 0644);
	if (fd < 0)
		printf("REDIR IN ERROR") ; // error handling
	new->redir_in = 1;
	close(fd);
}

void	handle_redir_out(t_single_cmd *new, t_token *temp, int type)
{
	int fd;
	if (type == 1)
	{
		free(new->redir_out_str);
		new->redir_out_str = ft_strdup(temp->command);
		fd = open(new->redir_out_str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			printf("REDIR OUT SIMPLE ERROR") ; // error handling
		new->redir_out = 1;
	}
	else
	{
		free(new->append_str);
		new->append_str = ft_strdup(temp->command);
		fd = open(new->append_str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			printf("APPEND ERROR") ; // error handling
		new->append = 1;
	}
	close(fd);
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

void	number_words_per_pipe(t_shell *cmd)
{
	t_token	*temp;
	
	temp = cmd->tok_lst;
	cmd->words_per_pipe = (int *)malloc(sizeof(int) * (cmd->pipe_number + 1));
	cmd->heredoc_arr = (char **)malloc(sizeof(char *) * cmd->heredoc + 1);
	if (!cmd->words_per_pipe || !cmd->heredoc_arr)
		return ; // error handling
	int i = 0;
	int j = 0;
	int k = 0;
	while (temp != NULL)
	{
		while (temp != NULL && temp->type != PIPE)
		{
			if (temp->type == APPEND || temp->type == REDIRECT_OUTPUT || temp->type == REDIRECT_INPUT)
				temp = temp->next->next;
			else if (temp->type == HEREDOC)
			{
				cmd->heredoc_arr[k] = ft_strdup(temp->next->command);
				k++;
				temp = temp->next->next;
			}
			else if (temp->type == WORD)
				j++;
			if (temp != NULL)
				temp = temp->next;
			else
				break;
		}
		cmd->words_per_pipe[i] = j;
		j = 0;
		i++;
		if (temp != NULL)
			temp = temp->next;
		else
			break;
	}
}

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


