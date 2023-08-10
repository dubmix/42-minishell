/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:13:54 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/10 12:33:31 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_redir_in(int fd, t_single_cmd *new, t_token *temp)
{
	if (temp->type == REDIRECT_INPUT)
	{
		free(new->redir_in_str);
		new->redir_in_str = ft_strdup(temp->next->command);
		fd = open(new->redir_in_str, O_RDONLY | O_CREAT, 0644);
		new->redir_in = 1;
	}
	return (fd);
}

int	handle_redir_in_out(t_shell *cmd, t_single_cmd *new, t_token *temp, int i)
{
	int	fd;

	if (temp->next != NULL && temp->next->type == WORD)
	{
		fd = 0;
		if (temp->type == REDIRECT_OUTPUT)
			fd = handle_redir_in_out_sub(new, temp, fd);
		// {
		// 	free(new->redir_out_str);
		// 	new->redir_out_str = ft_strdup(temp->next->command);
		// 	fd = open(new->redir_out_str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// 	new->redir_out = 1;
		// }
		else if (temp->type == APPEND)
		{
			free(new->append_str);
			new->append_str = ft_strdup(temp->next->command);
			fd = open(new->append_str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			new->append = 1;
		}
		else if (temp->type == REDIRECT_INPUT)
			fd = handle_redir_in(fd, new, temp);
		if (fd < 0)
			ft_error(cmd, "File descriptor error", 1);
		close(fd);
	}
	else
		new->command[i] = ft_strdup(temp->command);
	return (i);
}

int	handle_redir_in_out_sub(t_single_cmd *new, t_token *temp, int fd)
{
	free(new->redir_out_str);
	new->redir_out_str = ft_strdup(temp->next->command);
	fd = open(new->redir_out_str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	new->redir_out = 1;
	return (fd);
}
