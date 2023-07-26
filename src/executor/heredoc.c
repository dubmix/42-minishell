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

int	create_heredoc(char **heredoc, char *file_name)
{
	int fd;
	char *line;
	int i;

	fd = open(file_name, O_CREAT);
	line = readline(">");
	while(line && ft_strncmp(heredoc[i], line, ft_strlen(heredoc[i])) != 0) // tant que EOF n'est pas detecte
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(">");
	}
	free(line);
	close(fd);
	return (EXIT_SUCCESS);
}

char *create_heredoc_filename(void)
{
	int i;

	i = 0;
	char *file_name;
	
	file_name = ft_strjoin("build/.tmp_heredoc_file_", "");
	return (file_name);
}

int ft_heredoc(t_shell *shell)
{
	char *file_name;
	int ret;

	file_name = create_heredoc_filename();
	shell->heredoc = 1; //flag for in heredoc
	ret = create_heredoc(file_name);
	shell->heredoc = 0;
	return (ret);
}

create_heredoc


int	exec_heredoc(t_shell *shell)
{
	int ret;

	ret = EXIT_SUCCESS;
	//cmd->redirections?
	ret = ft_heredoc(shell, shell->tok_lst->redirections);
	return (EXIT_SUCCESS);
}
