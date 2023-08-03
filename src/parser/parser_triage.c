#include "../../minishell.h"

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
			delete_node_tok(&(cmd->tok_lst), nodeToDelete);
			state = 2;
		}
		else
		{
			state = 1;
			if ((*temp)->type == SPA && (*temp)->index != 1)
				(*temp)->type = WORD;
			temp = &((*temp)->next);
		}
	}
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
			if (cmd_splitted[0])
				(*temp)->command = ft_strdup(cmd_splitted[0]);
			else
				(*temp)->command = ft_strdup("\"\"");
			free_arr(cmd_splitted);
		}
		else if ((*temp)->state == 2)
		{
			cmd_splitted = ft_split((*temp)->command, '\'');
			free((*temp)->command);
			if (cmd_splitted[0])
				(*temp)->command = ft_strdup(cmd_splitted[0]);
			else
				(*temp)->command = ft_strdup("\'\'");
			(*temp)->type = 0;
			free_arr(cmd_splitted);
		}
		temp = &((*temp)->next);
	}
}