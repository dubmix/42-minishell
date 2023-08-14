/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:30:49 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/13 15:23:29 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redir_error(char *str)
{
	printf("%s\n", str);
	return (EXIT_FAILURE);
}

int	check_redirections(t_shell *cmd)
{
	if (cmd->nb_of_heredocs != 0)
		return (exec_heredoc(cmd));
	else if (cmd->cmd_lst->redir_in == 1)
		return (exec_infile(cmd->cmd_lst->redir_in_str));
	if (cmd->cmd_lst->append == 1)
		return (exec_outfile(cmd));
	else if (cmd->cmd_lst->redir_out == 1)
		return (exec_outfile(cmd));
	return (EXIT_SUCCESS);
}

int	exec_heredoc(t_shell *cmd)
{
	int	fd;
	int	dup;

	fd = open("heredoc.txt", O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (redir_error("minishell: heredoc creation error"));
	write(fd, cmd->heredoc_string, ft_strlen(cmd->heredoc_string));
	close(fd);
	fd = open("heredoc.txt", O_RDONLY);
	if (fd < 0)
		return (redir_error("minishell: heredoc opening error"));
	dup = dup2(fd, STDIN_FILENO);
	if (dup < 0)
		return (redir_error("minishell: dup heredoc error"));
	close(fd);
	unlink("heredoc.txt");
	return (EXIT_SUCCESS);
}

int	exec_outfile(t_shell *cmd)
{
	int	fd;
	int	dup;

	if (cmd->cmd_lst->append == 1)
		fd = open(cmd->cmd_lst->append_str, 
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(cmd->cmd_lst->redir_out_str,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	dup = dup2(fd, STDOUT_FILENO);
	if (fd > 0 && dup < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	exec_infile(char *file)
{
	int	fd;
	int	dup;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	dup = dup2(fd, STDIN_FILENO);
	if (fd > 0 && dup < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}
