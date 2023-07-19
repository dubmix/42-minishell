/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:46:03 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/19 11:46:03 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
}

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
