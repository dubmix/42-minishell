#include "../../minishell.h"

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

void	triage_quotes(t_shell *cmd)
{
	t_token	**temp;
	char	**cmd_splitted;

	temp = &(cmd->tok_lst);
	while (*temp != NULL)
	{
		if ((*temp)->state == 1)
		{
			cmd_splitted = ft_split((*temp)->command, '\"');
			free((*temp)->command);
			(*temp)->command = ft_strdup(cmd_splitted[0]);
			free_arr(cmd_splitted);
		}
		else if ((*temp)->state == 2)
		{
			cmd_splitted = ft_split((*temp)->command, '\'');
			free((*temp)->command);
			(*temp)->command = ft_strdup(cmd_splitted[0]);
			free_arr(cmd_splitted);
		}
		temp = &((*temp)->next);
	}
}

void	parser(t_shell *cmd)
{
	triage_quotes(cmd);
	triage_space(cmd);
	adjust_number(cmd);
	number_words_per_pipe(cmd);
	// triage_cmd_redir(cmd);
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

void	triage_space(t_shell *cmd)
{
	t_token	**temp;
	t_token	*nodeToDelete;
	int		state;

	temp = &(cmd->tok_lst);
	nodeToDelete = NULL;
	state = 0;
	while (*temp != NULL)
	{
		if ((*temp)->type == 0)
		{
			state = 0;
			temp = &((*temp)->next);
		}
		else if ((*temp)->type == 3 && (state == 1 || state == 2))
		{
			nodeToDelete = *temp;
			deleteNode(&(cmd->tok_lst), nodeToDelete);
			state = 2;
		}
		else
		{
			state = 1;
			temp = &((*temp)->next);
		}
	}
}

char	*copy_redir(t_shell *cmd, int nb_node)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = cmd->tok_lst;
	while (temp != NULL)
	{
		while (i < nb_node)
		{
			temp = temp->next;
			i++;
		}
		if (temp->type == 0)
			break ;
		temp = temp->next;
	}
	return (temp->command);
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
}

void	handle_redir_in(t_single_cmd *new, t_token *temp)
{
	int fd;
	free(new->redir_in_str);
	fd = open(temp->next->command, O_RDONLY);
	if (fd < 0)
		return ; // error handling
	new->redir_in_str = ft_strdup(temp->next->command);
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
	}
	else
	{
		free(new->append_str);
		fd = open(temp->next->command, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
				return ; // error handling
		new->append_str = ft_strdup(temp->next->command);
	}
	close(fd);
}
temp	**new_node_cmd(t_single_cmd **cmd_lst, int index, t_token **temp, t_shell *cmd)
{
	t_single_cmd	*new;
	t_token	**temp;
	
	temp = &(cmd->tok_lst);
	init_node_cmd(new, cmd, index);
	int i = 0;
	while ((*temp) != NULL && (*temp)->type != PIPE)
	{
		if ((*temp)->type == WORD && (*temp)->index == 0)
		{
			new->command[i] = ft_strdup((*temp)->command);
			i++;
		}
		if ((*temp)->type == REDIRECT_IN)
		{
			free(new->redir_in_str);
			handle_redir_in((*temp)->next);
			new->redir_in_str = ft_strdup((*temp)->next->command);
			new->redir_in = 1;
		}
		else if (*temp)->type == REDIRECT_OUT)
		{
			handle_redir_out((*temp)->next, 1);
			new->redir_out = 1;
		}
		else if (temp->type == REDIR_IN_DOUBLE)
		{
			printf("handle_heredoc((*temp)->next)");
			new->heredoc = 1;
		}
		else if (temp->type == REDIR_OUT_DOUBLE)
		{
			handle_redir_out((*temp)->next, 2);
			new->append = 1;
		}



		temp = temp->next;
	}

		
	// new->name = ft_strdup(string[0]);
	// new->value = ft_strdup(string[1]);
	// if (!new->name || !new->value)
	// 	return ; // error handling
	new->next = NULL;
	add_stack_back_env(cmd_lst, new);
	return (temp);
}

void	number_words_per_pipe(t_shell *cmd)
{
	t_token	**temp;
	
	temp = &(cmd->tok_lst);
	
	if (cmd->pipe_number == 0)
		return ;

	cmd->words_per_pipe = (int *)malloc(sizeof(int) * (cmd->pipe_number + 1));
	if (!cmd->words_per_pipe)
		return ; // error handling
	int i = 0;
	int j = 0;
	while ((*temp) != NULL)
	{
		while ((*temp) != NULL && (*temp)->type != PIPE)
		{
			if ((*temp)->type == REDIR_IN_DOUBLE || (*temp)->type == REDIR_OUT_DOUBLE || (*temp)->type == REDIRECT_IN || (*temp)->type == REDIRECT_OUT)
				(*temp) = (*temp)->next->next;
			if ((*temp)->type == WORD)
				j++;
			(*temp) = (*temp)->next;
		}
		cmd->words_per_pipe[i] = j;
		j = 0;
		i++;
		if ((*temp) != NULL)
			(*temp) = (*temp)->next;
	}
}

void	triage_cmd_redir(t_shell *cmd)
{
	t_token	*temp;
	t_single_cmd *cmd_lst;

	temp = cmd->tok_lst;
	int index_node = 0;
	
	while (temp != NULL)
	{
		//chaque pipe doit créer un new node
		// toutes les redirections doivent etre ouvertes puis fermees
		// la derniere de chaque type est stockée dans le noeud
		temp = new_node_cmd(&cmd_lst, index_node, (*temp))
		index_node++; 





		
// 		if (temp->type == WORD && temp->index == 0)
// 		{
// 			cmd-


// 		}
// 		if (temp->type == REDIRECT_IN)
// 		{
// 			cmd->redir_in_arr[redir_in] = ft_strdup(copy_redir(cmd,
// 					temp->index));
// 			redir_in++;
// 		}
// 		else if (temp->type == REDIRECT_OUT)
// 		{
// 			cmd->redir_out_arr[redir_out] = ft_strdup(copy_redir(cmd,
// 					temp->index));
// 			redir_out++;
// 		}
// 		else if (temp->type == REDIR_IN_DOUBLE)
// 		{
// 			cmd->heredoc_arr[heredoc] = ft_strdup(copy_redir(cmd, temp->index));
// 			heredoc++;
// 		}
// 		else if (temp->type == REDIR_OUT_DOUBLE)
// 		{
// 			cmd->append_arr[append] = ft_strdup(copy_redir(cmd, temp->index));
// 			append++;
// 		}

		temp = temp->next;
	}


}


// // void	triage_cmd_redir(t_shell *cmd)
// // {
// // 	t_token	*temp;
// // 	int		redir_in;
// // 	int		redir_out;
// // 	int		heredoc;
// // 	int		append;

// // 	temp = cmd->tok_lst;
// // 	redir_in = 0;
// // 	redir_out = 0;
// // 	heredoc = 0;
// // 	append = 0;
// // 	// should I malloc only in the number are different from 0 ? then different function for it,could put the end with 0 also in it with a different status kinda
// // 	cmd->redir_in_arr = (char **)malloc(sizeof(char *) * cmd->redir_in + 1);
// // 	cmd->redir_out_arr = (char **)malloc(sizeof(char *) * cmd->redir_out + 1);
// // 	cmd->heredoc_arr = (char **)malloc(sizeof(char *) * cmd->heredoc + 1);
// // 	cmd->append_arr = (char **)malloc(sizeof(char *) * cmd->append + 1);
// // 	if (!cmd->redir_in_arr || !cmd->redir_out_arr || !cmd->heredoc_arr || !cmd->append_arr)
// // 		return ;
// // 	while (temp != NULL)
// // 	{
// // 		if (temp->type == REDIRECT_IN)
// // 		{
// // 			cmd->redir_in_arr[redir_in] = ft_strdup(copy_redir(cmd,
// // 					temp->index));
// // 			redir_in++;
// // 		}
// // 		else if (temp->type == REDIRECT_OUT)
// // 		{
// // 			cmd->redir_out_arr[redir_out] = ft_strdup(copy_redir(cmd,
// // 					temp->index));
// // 			redir_out++;
// // 		}
// // 		else if (temp->type == REDIR_IN_DOUBLE)
// // 		{
// // 			cmd->heredoc_arr[heredoc] = ft_strdup(copy_redir(cmd, temp->index));
// // 			heredoc++;
// // 		}
// // 		else if (temp->type == REDIR_OUT_DOUBLE)
// // 		{
// // 			cmd->append_arr[append] = ft_strdup(copy_redir(cmd, temp->index));
// // 			append++;
// // 		}
// // 		temp = temp->next;
// // 	}
// // 	cmd->redir_in_arr[redir_in] = 0;
// // 	cmd->redir_out_arr[redir_out] = 0;
// // 	cmd->heredoc_arr[heredoc] = 0;
// // 	cmd->append_arr[append] = 0;
// // }

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