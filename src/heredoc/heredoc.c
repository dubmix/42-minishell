/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:32:47 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/19 11:21:42 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	create_heredoc(char *file_name)
{
	int fd;
	char *line;

	fd = open(file_name, O_CREAT);
	line = readline(HEREDOC_MSG);
	while(line)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_MSG)
	}
	free(line);
	//stop heredoc
	close(fd);
	return (EXIT_SUCCESS);
}

char *create_heredoc_filename(void)
{
}

int ft_heredoc()
{
create_heredoc
}

int	heredoc()
{
	int es;

	es = EXIT_SUCCESS;
	//cmd->redirections
	//cmd-><file_name> create_heredoc_filename
	es = ft_heredoc;
	return (EXIT_SUCCESS);
}
