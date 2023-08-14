/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:07:17 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/14 09:58:02 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*tokenization(t_shell *cmd)
{
	int		i;
	int		nb_token;
	t_token	*tok_lst;

	i = 0;
	nb_token = 0;
	tok_lst = NULL;
	tok_lst = token_loop(cmd, i, nb_token, tok_lst);
	cmd->tok_alloc = 1;
	return (tok_lst);
}

t_token	*token_loop(t_shell *cmd, int i, int nb_token, t_token *tok_lst)
{
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == '~' && (cmd->line[i + 1] == '\0' 
				|| cmd->line[i + 1] == ' '))
		{
			new_token(&tok_lst, "$HOME", nb_token, VARIABLE);
			i++;
		}
		else if (i == 0 && (cmd->line[i + 1] == '\0' 
				|| ((cmd->line[i] == cmd->line[i + 1] 
						&& cmd->line[i + 2] == '\0'))))
			tok_lst = tokenization_simple_char(cmd, i, tok_lst, nb_token);
		else if (cmd->line[i] == 39 || cmd->line[i] == 34
			|| cmd->line[i] == '$')
			tok_lst = tokenization_special_char(cmd, &i, tok_lst, nb_token);
		else if (cmd->line[i] == '>' || cmd->line[i] == '<' || 
			cmd->line[i] == ' ' || cmd->line[i] == 9 || cmd->line[i] == '|')
			tok_lst = tokenization_bis(cmd, &i, tok_lst, nb_token);
		else
			i = new_token_var_words(&tok_lst, cmd->line, i, nb_token);
		if (cmd->line[i] != '\0')
			i++;
		nb_token++;
	}
	return (tok_lst);
}

int	tokenization_sub(t_shell *cmd, int i, t_token *tok_lst, int nb_token)
{
	if (i == 0 && (cmd->line[i + 1] == '\0'
			|| ((cmd->line[i] == cmd->line[i + 1] 
					&& cmd->line[i + 2] == '\0'))))
		tok_lst = tokenization_simple_char(cmd, i, tok_lst, nb_token);
	else if (cmd->line[i] == '~' && (cmd->line[i + 1] == ' '
			|| cmd->line[i + 1] == '\0'))
	{
		new_token(&tok_lst, "$HOME", nb_token, VARIABLE);
		i++;
	}
	return (i);
}

void	add_stack_back_tok(t_token **tok_lst, t_token *new)
{
	t_token	*tail;

	if (!new)
		return ;
	if (!(*tok_lst))
	{
		*tok_lst = new;
		return ;
	}
	tail = *tok_lst;
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	tail->next = new;
}

void	new_token(t_token **tokens, char *command, int nb, enum e_type type)
{
	t_token	*new;

	new = NULL;
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
	{
		ft_putstr_fd("Memory allocation failed for new token", STDERR_FILENO);
		return ;
	}
	new->command = ft_strdup(command);
	new->index = nb;
	new->type = type;
	new->next = NULL;
	if (new->type == D_QUOTE)
		new->state = 1;
	else if (new->type == S_QUOTE)
		new->state = 2;
	else
		new->state = 0;
	add_stack_back_tok(tokens, new);
	return ;
}
