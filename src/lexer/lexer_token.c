/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:45:56 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/19 12:10:35 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->command = ft_strdup(command);
	new->index = nb;
	new->type = type;
	new->next = NULL;
	if (new->type == 2)
		new->state = 1;
	else if (new->type == 1)
		new->state = 2;
	else
		new->state = 0;
	add_stack_back_tok(tokens, new);
	return ;
}

int	new_token_var_words(t_token **tokens, char *string, int i, int nb_token)
{
	int		start;
	char	*var;

	start = i;
	while (special_char(string[i]) == 0 && string[i] != '\0')
		i++;
	var = ft_substr(string, start, i - start);
	if (string[start] == '$')
		new_token(tokens, var, nb_token, VARIABLE);
	else
		new_token(tokens, var, nb_token, WORD);
	return (i);
}

int	new_token_quote(t_token **tokens, char *string, int i, int nb_token)
{
	int		start;
	char	*var;
	char	c;

	c = string[i];
	start = i;
	i++;
	while (string[i] != '\0')
	{
		if (string[i] == c)
			break ;
		i++;
	}
	var = ft_substr(string, start, i + 1 - start);
	if (string[i] == '\0' && string[i] != c)
		return (printf("error")); // inifinite loop - to be changed, saying that there is an incorrect number of quotes
	else if (c == 39)
		new_token(tokens, var, nb_token, S_QUOTE);
	else
		new_token(tokens, var, nb_token, D_QUOTE);
	return (i + 1);
}

t_token	*tokenization(t_shell *shell)
{
	int		i;
	int		nb_token;
	t_token	*tok_lst;

	// int start;
	i = 0;
	// start = 0;
	nb_token = 0;
	tok_lst = NULL;
	shell->redir_in = 0;
	shell->redir_out = 0;
	shell->heredoc = 0;
	shell->append = 0;
	shell->pipe_number = 0;
	while (shell->line_command[i] != '\0')
	{
		if (shell->line_command[i] == '|')
		{
			new_token(&tok_lst, "|", nb_token, PIPE);
			shell->pipe_number++;
		}
		else if (shell->line_command[i] == 39) // single quotes
			i = new_token_quote(&tok_lst, shell->line_command, i, nb_token) - 1;
		else if (shell->line_command[i] == 34) // double quotes
			i = new_token_quote(&tok_lst, shell->line_command, i, nb_token) - 1;
		else if (shell->line_command[i] == '>' && shell->line_command[i
			+ 1] != '>')
		{
			new_token(&tok_lst, ">", nb_token, REDIRECT_IN);
			shell->redir_in++;
		}
		else if (shell->line_command[i] == '<' && shell->line_command[i
			+ 1] != '<')
		{
			new_token(&tok_lst, "<", nb_token, REDIRECT_OUT);
			shell->redir_out++;
		}
		else if (shell->line_command[i] == '>' && shell->line_command[i
			+ 1] == '>')
		{
			new_token(&tok_lst, ">>", nb_token, REDIR_IN_DOUBLE);
			shell->heredoc++;
			i++;
		}
		else if (shell->line_command[i] == '<' && shell->line_command[i
			+ 1] == '<')
		{
			new_token(&tok_lst, "<<", nb_token, REDIR_OUT_DOUBLE);
			shell->append++;
			i++;
		}
		else if (shell->line_command[i] == ' ' || shell->line_command[i] == 9)
			// space and tab
			new_token(&tok_lst, " ", nb_token, SPA);
		else if (shell->line_command[i] == '$')
			i = new_token_var_words(&tok_lst, shell->line_command, i, nb_token)
				- 1;
		else
			i = new_token_var_words(&tok_lst, shell->line_command, i, nb_token)
				- 1;
		i++;
		nb_token++;
	}
	return (tok_lst);
}
