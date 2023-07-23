#include "../../minishell.h"

void	print_list_commands(t_single_cmd *cmd, t_shell *shell);

void	parser(t_shell *cmd)
{
	triage_quotes(cmd);
	triage_space(cmd);
	adjust_number(cmd);
	number_words_per_pipe(cmd);
	triage_cmd_redir(cmd);
	print_list_commands(cmd->cmd_lst, cmd);
	// if (cmd->pipe_number != 0)
	// 	printf("IL Y A DES PIPES, ON FERA CA PLUS TARD");
	// else
	// 	single_command(cmd);
	// printf("\nPRINTING TOKENS \n");
	// print_list_tok(cmd->tok_lst);
	// printf("\nEND TOKENS \n");
	// if (cmd->redir_in != 0)
	//     printf("IN : NB REDIR %d\n ARR 1 %s\n ARR 2 %s \n", cmd->redir_in, cmd->redir_in_arr[0], cmd->redir_in_arr[1]);
	// if (cmd->redir_out != 0)
	//     printf("OUT : NB REDIR %d\n ARR 1 %s\n ARR 2 %s \n", cmd->redir_out,cmd->redir_out_arr[0], cmd->redir_out_arr[1]);
	// if (cmd->heredoc != 0)
	//     printf("NB HEREDOC %d\n ARR 1 %s\n ARR 2 %s \n", cmd->heredoc,cmd->heredoc_arr[0], cmd->heredoc_arr[1]);
	// if (cmd->append != 0)
	//     printf("NB APPEND %d\n ARR 1 %s\n ARR 2 %s \n", cmd->append,cmd->append_arr[0], cmd->append_arr[1]);
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
		printf("node is %d : \n, redir_in is %d : %s\n, redir_out is %d : %s\n, heredoc is %d : %s, append is %d : %s,\n", tmp->index, tmp->redir_in, tmp->redir_in_str,  tmp->redir_out, tmp->redir_out_str,  tmp->heredoc, tmp->heredoc_str,  tmp->append, tmp->append_str);
		while (i < shell->words_per_pipe[j])
		{
			printf("%s \n", tmp->command[i]);
			i++;
		}
		j++;
		tmp = tmp->next;
	}
}
// typedef struct s_single_cmd
// {
//     char **command;
//     int redir_in;
//     char *redir_in_str;
//     int redir_out;
//     char *redir_out_str;
//     int heredoc;
//     char *heredoc_str;
//     int append;
//     char *append_str;
//     int index; // is the index of the pipe basically
// } t_single_cmd;


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

void init_node_cmd(t_single_cmd *new, t_shell *cmd, int index)
{
	new = (t_single_cmd *)malloc(sizeof(t_single_cmd));
	new->command = (char **)malloc(sizeof(char *) * cmd->words_per_pipe[index] + 1);
	if (!new || !new->command)
		return ; // error handling
	new->append_str = ft_strdup("");
	new->heredoc_str = ft_strdup("");
	new->redir_in_str = ft_strdup("");
	new->redir_out_str = ft_strdup("");
	write(1, "init", 4);
}

void	handle_redir_in(t_single_cmd *new, t_token *temp)
{
	int fd;
	free(new->redir_in_str);
	fd = open(temp->next->command, O_RDONLY);
	if (fd < 0)
		return ; // error handling
	new->redir_in_str = ft_strdup(temp->next->command);
	new->redir_in = 1;
	close(fd);
}

void	handle_redir_out(t_single_cmd *new, t_token *temp, int type)
{
	int fd;
	if (type == 1)
	{
		free(new->redir_out_str);
		fd = open(temp->next->command, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
				return ; // error handling
		new->redir_out_str = ft_strdup(temp->next->command);
		new->redir_out = 1;
	}
	else
	{
		free(new->append_str);
		fd = open(temp->next->command, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
				return ; // error handling
		new->append_str = ft_strdup(temp->next->command);
		new->append = 1;

	}
	close(fd);
}

t_token	**new_node_cmd(t_single_cmd **cmd_lst, int index, t_token **temp, t_shell *cmd)
{
	t_single_cmd	*new;
	int i = 0;
	write(1, "new node\n", 9);

	new = NULL;
	init_node_cmd(new, cmd, index);
	while ((*temp) != NULL && (*temp)->type != PIPE)
	{
		if ((*temp)->type == WORD)
		{
			new->command[i] = ft_strdup((*temp)->command);
			write(1, "new node end\n", 13);
			i++;
		}
		if ((*temp)->type == REDIRECT_IN)
		{
			handle_redir_in(new, (*temp)->next);
			new->redir_in = 1;
		}
		else if ((*temp)->type == REDIRECT_OUT)
		{
			handle_redir_out(new, (*temp)->next, 1);
			new->redir_out = 1;
		}
		else if ((*temp)->type == REDIR_IN_DOUBLE)
		{
			printf("handle_heredoc((*temp)->next)");
			new->heredoc = 1;
		}
		else if ((*temp)->type == REDIR_OUT_DOUBLE)
		{
			handle_redir_out(new, (*temp)->next, 2);
			new->append = 1;
		}
		(*temp) = (*temp)->next;
	}
	new->next = NULL;

	add_stack_back_cmd(cmd_lst, new);
	return (temp);
}

void	number_words_per_pipe(t_shell *cmd)
{
	t_token	*temp;
	
	temp = cmd->tok_lst;
	// if (cmd->pipe_number == 0)
	// {
	// 	cmd->words_per_pipe = (int *)malloc(sizeof(int) * 1);
	// 	cmd->words_per_pipe[0] = 1;
	// 	return ;
	// }
	cmd->words_per_pipe = (int *)malloc(sizeof(int) * (cmd->pipe_number + 1));
	if (!cmd->words_per_pipe)
		return ; // error handling
	int i = 0;
	int j = 0;
	while (temp != NULL)
	{
		while (temp != NULL && temp->type != PIPE)
		{
			if (temp->type == REDIR_IN_DOUBLE || temp->type == REDIR_OUT_DOUBLE || temp->type == REDIRECT_IN || temp->type == REDIRECT_OUT)
				temp = temp->next->next;
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

void	triage_cmd_redir(t_shell *cmd)
{
	t_token	**temp;
	t_single_cmd *cmd_lst;

	temp = &(cmd->tok_lst);
	// printf("here %s", (*temp)->command);
	int index_node = 0;
	write(1, "RT\n", 3);
	while ((*temp) != NULL)
	{
		write(2, "NNN", 3);
		temp = new_node_cmd(&cmd_lst, index_node, temp, cmd);
		index_node++;
		if (temp != NULL)
			(*temp) = (*temp)->next;
		else 
			break;
	}


}


