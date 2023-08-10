/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_triage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 11:56:11 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/10 08:37:53 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	triage_quotes_bis(t_token **temp, char **cmd_splitted);

void	triage_space_bis(t_shell *cmd, t_token **temp, t_token *node_to_delete, 
	int state)
{
	while (*temp != NULL)
	{
		if ((*temp)->type == 0)
		{
			state = 0;
			temp = &((*temp)->next);
		}
		else if ((*temp)->type == 3 && (state == 1 || state == 2))
		{
			node_to_delete = *temp;
			delete_node_tok(&(cmd->tok_lst), node_to_delete);
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

void	triage_space(t_shell *cmd)
{
	t_token	**temp;
	t_token	*node_to_delete;
	int		state;

	temp = &(cmd->tok_lst);
	node_to_delete = NULL;
	state = 0;
	triage_space_bis(cmd, temp, node_to_delete, state);
}

void	triage_space_redir_pipe(t_shell *cmd)
{
	t_token	**temp;
	t_token	*node_to_delete;

	temp = &(cmd->tok_lst);
	node_to_delete = NULL;
	while (*temp != NULL)
	{
		if (((*temp)->next != NULL) && (ft_strncmp((*temp)->command, " ",
					ft_strlen((*temp)->command)) == 0) 
			&& ((*temp)->next->type == REDIRECT_INPUT
				|| (*temp)->next->type == REDIRECT_OUTPUT
				|| (*temp)->next->type == APPEND 
				|| (*temp)->next->type == PIPE))
		{
			node_to_delete = *temp;
			delete_node_tok(&(cmd->tok_lst), node_to_delete);
		}
		temp = &((*temp)->next);
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
			triage_quotes_bis(temp, cmd_splitted);
		else if ((*temp)->state == 2)
		{
			cmd_splitted = ft_split((*temp)->command, '\'');
			free((*temp)->command);
			if (cmd_splitted[0])
				(*temp)->command = ft_strdup(cmd_splitted[0]);
			else
				(*temp)->command = ft_strdup("");
			(*temp)->type = 0;
			free_arr(cmd_splitted);
		}
		temp = &((*temp)->next);
	}
}

void	triage_quotes_bis(t_token **temp, char **cmd_splitted)
{
	cmd_splitted = ft_split((*temp)->command, '\"');
	free((*temp)->command);
	if (cmd_splitted[0])
		(*temp)->command = ft_strdup(cmd_splitted[0]);
	else
		(*temp)->command = ft_strdup("");
	free_arr(cmd_splitted);
}
