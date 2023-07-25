/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:45:56 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/25 16:54:45 by edrouot          ###   ########.fr       */
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
/* is used to create a new node for single characters and add it to the end of the list */
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
	if (new->type == D_QUOTE)
		new->state = 1;
	else if (new->type == S_QUOTE)
		new->state = 2;
	else
		new->state = 0;
	add_stack_back_tok(tokens, new);
	return ;
}

/* is used to create a new node for quotes and then use the new_token*/
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


/* is used to create a new node for quotes and then use the new_token with either single quote state or double quote state*/
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
/* Order every type into a list of token (see enum e_type) */
t_token	*tokenization(t_shell *shell)
{
	int		i;
	int		nb_token;
	t_token	*tok_lst;

	i = 0;
	nb_token = 0;
	tok_lst = NULL;
	shell->heredoc = 0;
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
		else if (shell->line_command[i] == '>' && shell->line_command[i+ 1] != '>')
			new_token(&tok_lst, ">", nb_token, REDIRECT_OUTPUT);
		else if (shell->line_command[i] == '<' && shell->line_command[i+ 1] != '<')
			new_token(&tok_lst, "<", nb_token, REDIRECT_INPUT);
		else if (shell->line_command[i] == '>' && shell->line_command[i+ 1] == '>')
		{
			new_token(&tok_lst, ">>", nb_token, APPEND);
			i++;
		}
		else if (shell->line_command[i] == '<' && shell->line_command[i+ 1] == '<')
		{
			new_token(&tok_lst, "<<", nb_token, HEREDOC);
			shell->heredoc++;
			i++;
		}
		else if (shell->line_command[i] == ' ' || shell->line_command[i] == 9)
			new_token(&tok_lst, " ", nb_token, SPA);
		else if (shell->line_command[i] == '$')
			i = new_token_var_words(&tok_lst, shell->line_command, i, nb_token)- 1;
		else
			i = new_token_var_words(&tok_lst, shell->line_command, i, nb_token)- 1;
		i++;
		nb_token++;
	}
	return (tok_lst);
}
