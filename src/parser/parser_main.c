/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:01:11 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/13 15:33:08 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	test_tok_lst(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->tok_lst;
	while (temp != NULL)
	{
		if (ft_strncmp(cmd->tok_lst->command, "",
				ft_strlen(cmd->tok_lst->command)))
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
		return (0);
	return (1);
}

int	test_cmd_lst(t_shell *cmd)
{
	t_single_cmd	*temp;

	temp = cmd->cmd_lst;
	while (temp != NULL)
	{
		if (ft_strncmp(cmd->cmd_lst->command[0], "",
				ft_strlen(*cmd->cmd_lst->command)))
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
		return (0);
	return (1);
}

int	parser(t_shell *cmd)
{
	if (!test_tok_lst(cmd))
		return (0);
	triage_quotes(cmd);
	adjust_number(cmd);
	triage_space(cmd);
	triage_space_redir_pipe(cmd);
	adjust_number(cmd);
	if (!error_syntax(cmd))
		return (0);
	number_words_per_pipe(cmd);
	if (cmd->nb_of_heredocs)
	{
		if (g_xcode == 130)
			g_xcode = 0;
		number_heredocs(cmd);
		if (cmd->nb_of_heredocs)
			grab_heredoc(cmd);
	}
	else
		g_xcode = 0;
	cmd->cmd_lst = triage_cmd_redir(cmd);
	if (!test_cmd_lst(cmd))
		return (0);
	return (1);
}

void	space_commands(t_shell *cmd)
{
	t_single_cmd	*temp;
	int				i;

	i = 0;
	temp = cmd->cmd_lst;
	while (temp != NULL)
	{
		while (temp->command[i] != 0)
		{
			if (!ft_strncmp(temp->command[i], " ",
					ft_strlen(temp->command[i])) && temp->command[i + 1] == 0)
			{
				free(temp->command[i]);
				temp->command[i] = ft_strdup("");
				break ;
			}
		}
		temp = temp->next;
	}
}

int	error_syntax(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->tok_lst;
	while (temp != NULL)
	{
		if ((temp->next == NULL || temp->next->type == PIPE) && 
			(temp->type == HEREDOC || temp->type == REDIRECT_INPUT || 
				temp->type == REDIRECT_OUTPUT || temp->type == APPEND))
		{
			ft_putstr_fd("minishell : syntax error", STDERR_FILENO);
			ft_putstr_fd(" near unexpected token\n", STDERR_FILENO);
			g_xcode = 2;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}
