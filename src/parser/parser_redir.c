/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:13:54 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/14 10:00:24 by edrouot          ###   ########.fr       */
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

void	handle_redir_in_out(t_single_cmd *new, t_token *temp)
{
	int	fd;

	if (temp->next != NULL && temp->next->type == WORD)
	{
		fd = 0;
		if (temp->type == REDIRECT_OUTPUT || temp->type == APPEND)
			fd = handle_redir_in_out_sub(new, temp, fd);
		else if (temp->type == REDIRECT_INPUT)
		{
			free(new->redir_in_str);
			new->redir_in_str = ft_strdup(temp->next->command);
			fd = open(new->redir_in_str, O_RDONLY, 0644);
			new->redir_in = 1;
		}
		if (fd < 0)
			g_xcode = 1;
		if (fd > 0)
			close(fd);
	}
	return ;
}

int	handle_redir_in_out_sub(t_single_cmd *new, t_token *temp, int fd)
{
	if (temp->type == REDIRECT_OUTPUT)
	{
		free(new->redir_out_str);
		new->redir_out_str = ft_strdup(temp->next->command);
		fd = open(new->redir_out_str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		new->redir_out = 1;
		if (new->append == 1)
			new->append = 2;
	}
	else if (temp->type == APPEND)
	{
		free(new->append_str);
		new->append_str = ft_strdup(temp->next->command);
		fd = open(new->append_str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		new->append = 1;
		if (new->redir_out == 1)
			new->redir_out = 2;
	}
	return (fd);
}
