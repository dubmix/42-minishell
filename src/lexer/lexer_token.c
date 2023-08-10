/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:45:56 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/10 09:06:26 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

t_token	*tokenization_special_char(t_shell *cmd, int *i, 
	t_token *tok_lst, int nb_token)
{
	if (cmd->line[*i] == 39 || cmd->line[*i] == 34)
		*i = new_token_quote(&tok_lst, cmd->line,
				*i, nb_token) - 1;
	else if (cmd->line[*i] == '$' && cmd->line[*i + 1] == '$')
	{
		new_token(&tok_lst, "$$", nb_token, VARIABLE);
		*i = *i + 1;
	}
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
