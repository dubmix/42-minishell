#include "../../minishell.h"

void	parser(t_shell *cmd)
{
	triage_quotes(cmd);
	adjust_number(cmd);
	triage_space(cmd);
	adjust_number(cmd);
	number_words_per_pipe(cmd);
	cmd->cmd_lst = triage_cmd_redir(cmd);
	if (cmd->nb_of_heredocs != 0)
		grab_heredoc(cmd);
}

void	number_words_per_pipe(t_shell *cmd)
{
	t_token	*temp;
	
	temp = cmd->tok_lst;
	cmd->words_per_pipe = (int *)malloc(sizeof(int) * (cmd->nb_of_pipes + 1)); // +1 ?
	if (cmd->nb_of_heredocs != 0)
	{
		cmd->heredoc_arr = (char **)malloc(sizeof(char *) * (cmd->nb_of_heredocs + 1));
		if (!cmd->heredoc_arr)
			return ;
	}
	if (!cmd->words_per_pipe)
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
	if (cmd->nb_of_heredocs != 0)
		cmd->heredoc_arr[k] = 0;
}


