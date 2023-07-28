/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:13:54 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/28 10:33:22 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_redir_in_out(t_single_cmd *new, t_token *temp)
{
	int	fd;

	fd = 0;
	if (temp->type == REDIRECT_OUTPUT)
	{
		free(new->redir_out_str);
		new->redir_out_str = ft_strdup(temp->command);
		fd = open(new->redir_out_str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		new->redir_out = 1;
	}
	else if (temp->type == APPEND)
	{
		free(new->append_str);
		new->append_str = ft_strdup(temp->command);
		fd = open(new->append_str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		new->append = 1;
	}
	else if (temp->type == REDIRECT_INPUT)
	{
		free(new->redir_in_str);
		new->redir_in_str = ft_strdup(temp->command);
		fd = open(new->redir_in_str, O_RDONLY | O_CREAT, 0644);
		new->redir_in = 1;
	}
	if (fd < 0)
		printf("REDIR OUT SIMPLE ERROR") ; // error handling
	close(fd);
}
