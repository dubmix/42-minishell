#include "../../minishell.h"

void	parser(t_shell *cmd)
{
	triage_quotes(cmd);
	adjust_number(cmd);
	triage_space(cmd);
	adjust_number(cmd);
	number_words_per_pipe(cmd);
	// empty the array of int and free the tok_lst
	cmd->cmd_lst = triage_cmd_redir(cmd);
	print_list_commands(cmd->cmd_lst, cmd);
	if (cmd->nb_of_heredocs != 0)
		grab_heredoc(cmd); 
	
	// pre_executor(cmd);
	//single_command(cmd);
	/*
	part 1 : check if there is a pipe
	part 2 : form the command in a new list --> list2array
	part 3 : put all the redirections in a separate struct --> done
	part 4 : handle two cases : pipes or single command --> single command handled
	part 5 : differentiate if the command are builtin or not
	*/
}

void	number_words_per_pipe(t_shell *cmd)
{
	t_token	*temp;
	
	temp = cmd->tok_lst;
	cmd->words_per_pipe = (int *)malloc(sizeof(int) * (cmd->nb_of_pipes + 1));
	cmd->heredoc_arr = (char **)malloc(sizeof(char *) * (cmd->nb_of_heredocs + 1));
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
				temp = temp->next;
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
	cmd->heredoc_arr[k] = 0;
}


