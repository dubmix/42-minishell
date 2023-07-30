/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:35:10 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/29 11:30:44 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int unset_error(char **str)
{
    int i;

    i = 0;
    if (str[1] == (void *)0)
    {
        printf("minishell: unset: not enough arguments");
        return (1);
    }
    while (str[1][i])
    {
        if (str[1][i] == '/')
        {    
            printf("minishell: unset: %s: not a valid identifier", str[1]);
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}

int unset(t_shell *cmd)
{
    t_shell **tmp;
    char       **str;
    str = NULL;
    tmp = &cmd;
    if (ft_findchar((*tmp)->tok_lst->command, '=' == 0))
    {
        printf("minishell: unset: not a valid identifier");
        return (EXIT_FAILURE);
    }
    if (unset_error(str) == 1)  // str is supposed to be what ???
        return (EXIT_FAILURE);
    while ((*tmp)->env_lst)
    {
        if (ft_strncmp((*tmp)->env_lst->name,(*tmp)->tok_lst->command, ft_strlen((*tmp)->env_lst->name) == 0))
        {
            delete_node_env(&(cmd->env_lst), (*tmp)->env_lst);
            break ;
        }
        (*tmp)->env_lst = (*tmp)->env_lst->next;
    }
    return (EXIT_SUCCESS);
}

void	delete_node_env(t_env **head, t_env *node_to_delete)
{
	t_env *prev_node;

	prev_node = NULL;
	if (*head == NULL || node_to_delete == NULL)
		return ;
	if (*head == node_to_delete)
		*head = node_to_delete->next;
	else
	{
		prev_node = *head;
		while (prev_node->next != NULL && prev_node->next != node_to_delete)
			prev_node = prev_node->next;
		if (prev_node->next == node_to_delete)
			prev_node->next = node_to_delete->next;
		else
			return ;
	}
	free(node_to_delete->name);
    free(node_to_delete->value);
	free(node_to_delete);
	return ;
}