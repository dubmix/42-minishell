/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:46:03 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/05 15:00:58 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	print_list(t_env *env)
// {
// 	t_env	*tmp;

// 	tmp = env;
// 	while (tmp != NULL)
// 	{
// 		printf("%s\n", tmp->full_string);
// 		tmp = tmp->next;
// 	}
// }

// void	print_list_tok(t_token *tok)
// {
// 	t_token	*tmp;

// 	tmp = tok;
// 	while (tmp)
// 	{
// 		printf("node is %s, nb is %d, state is %d, type is %d\n", tmp->command, tmp->index, tmp->state, tmp->type);
// 		tmp = tmp->next;
// 	}
// }

int	special_char(int c)
{
	if (c == '|' || c == 34 || c == ' ' || c == '<' || c == '>' || c == 39
		|| c == 9 || c == '$')
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
	int		length;

	i = 0;
	length = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '$')
		{
			while (string[i] != '\0' && 
				!check_valid_id(string[i]) && string[i] != '$') 
				i++;
		}
		else
			length++;
		i++;
	}
	return (length);
}
