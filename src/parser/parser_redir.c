#include "../../minishell.h"

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
