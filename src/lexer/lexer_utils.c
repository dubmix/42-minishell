/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:46:03 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/26 09:18:20 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_list(t_env *env) // print the envp
{
	t_env *tmp = env;
	while (tmp != NULL)
	{
		printf("node is %s and value is %s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	print_list_tok(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		printf("node is %s, number is %d, state is %d, type is %d\n",
			tmp->command, tmp->index, tmp->state, tmp->type);
		tmp = tmp->next;
	}
}

int	special_char(int c)
{
	if (c == '|' || c == 34 || c == ' ' || c == '<' || c == '>' || c == 39
		|| c == 9)
		return (1);
	else
		return (0);
}


int	length_arr_var(char **arr_var, t_shell *cmd)
{
	int	j;
	int	length;

	j = 0;
	length = 0;
	while (arr_var[j] != NULL && j < cmd->size_arr_var)
	{
		length += ft_strlen(arr_var[j]);
		j++;
	}
	return (length);
}

int	length_string_without_var(char *string)
{
	int		i;
	char	*temp;
	int		length;

	i = 0;
	temp = string;
	length = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] == '$')
		{
			while (temp[i] != ' ' && temp[i] != 34)
				i++;
		}
		else
			length++;
		i++;
	}
	return (length);
}
