/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:45:56 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/05 22:49:49 by emiliedrouo      ###   ########.fr       */
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

/* is used to create a new node for 
single characters and 
add it to the end of the list */

void	new_token(t_token **tokens, char *command, int nb, enum e_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		ft_putstr_fd("Memory allocation failed for new token", STDERR_FILENO);
		exit (1);
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

/* is used to create a new node for quotes 
and then use the new_token*/

int	new_token_var_words(t_token **tokens, char *string, int i, int nb_token)
{
	int		start;
	char	*var;

	start = i;
	i++;
	while (special_char(string[i]) == 0 && string[i] != '\0')
		i++;
	var = ft_substr(string, start, i - start);
	if (ft_strncmp(var, "$", ft_strlen(var)) == 0)
		new_token(tokens, "$", nb_token, WORD);
	else if (string[start] == '$')
		new_token(tokens, var, nb_token, VARIABLE);
	else
	{
		new_token(tokens, var, nb_token, WORD);
		i = i - 1;
	}
	free(var);
	return (i);
}

/* is used to create a new node for quotes 
and then use the new_token with either single quote state 
or double quote state*/

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
	nb_token++;
	var = ft_substr(string, start, i +1 - start);
	if (c == 39)
		new_token(tokens, var, nb_token, S_QUOTE);
	else
		new_token(tokens, var, nb_token, D_QUOTE);
	free(var);
	return (i + 1);
}

/* Order every type into a list of token (see enum e_type) */

t_token	*tokenization_bis(t_shell *cmd, int *i, t_token *tok_lst, int nb_token)
{
	if (cmd->line[*i] == '|')
	{
		new_token(&tok_lst, "|", nb_token, PIPE);
		cmd->nb_of_pipes++;
	}
	else if (cmd->line[*i] == '>' && cmd->line[*i + 1] != '>')
		new_token(&tok_lst, ">", nb_token, REDIRECT_OUTPUT);
	else if (cmd->line[*i] == '<' && cmd->line[*i + 1] != '<')
		new_token(&tok_lst, "<", nb_token, REDIRECT_INPUT);
	else if (cmd->line[*i] == '>' && cmd->line[*i + 1] == '>')
	{
		new_token(&tok_lst, ">>", nb_token, APPEND);
		*i = *i + 1;
	}
	else if (cmd->line[*i] == '<' && cmd->line[*i + 1] == '<')
	{
		new_token(&tok_lst, "<<", nb_token, HEREDOC);
		cmd->nb_of_heredocs++;
		*i = *i + 1;
	}
	else if (cmd->line[*i] == ' ' || cmd->line[*i] == 9)
		new_token(&tok_lst, " ", nb_token, SPA);
	return (tok_lst);
}

t_token	*tokenization_simple_char(t_shell *cmd, int i, 
	t_token *tok_lst, int nb_token)
{
	if (cmd->line[i + 1] == '\0')
		new_token(&tok_lst, &cmd->line[i], nb_token, WORD);
	else if (cmd->line[i + 2] == '\0')
		new_token(&tok_lst, ft_substr(cmd->line, 0, 2), nb_token, WORD);
	return (tok_lst);
}

/*else if (cmd->line[*i] == '~' && (cmd->line[*i + 1] == ' '
		|| cmd->line[*i + 1] == '\0'))
{
	new_token(&tok_lst, "$HOME", nb_token, VARIABLE);
	i++;
}*/

t_token	*tokenization_special_char(t_shell *cmd, int *i, 
	t_token *tok_lst, int nb_token)
{
	if (cmd->line[*i] == 39 || cmd->line[*i] == 34)
		*i = new_token_quote(&tok_lst, cmd->line,
				*i, nb_token) - 1;
	else if (cmd->line[*i] == '$' && cmd->line[*i + 1] == '0')
	{
		new_token(&tok_lst, "minishell", nb_token, WORD);
		*i = *i + 1;
	}
	else if (cmd->line[*i] == '$')
		*i = new_token_var_words(&tok_lst, cmd->line, 
				*i, nb_token) - 1;
	return (tok_lst);
}

t_token	*tokenization(t_shell *cmd)
{
	int		i;
	int		nb_token;
	t_token	*tok_lst;

	i = 0;
	nb_token = 0;
	tok_lst = NULL;
	while (cmd->line[i] != '\0')
	{
		if (i == 0 && (cmd->line[i + 1] == '\0' || ((cmd->line[i] == cmd->line[i + 1] 
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
		i++;
		nb_token++;
	}
	free(cmd->line);
	return (tok_lst);
}
