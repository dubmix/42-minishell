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

void	delete_node_env(t_env **head, t_env *nodeToDelete)
{
	t_env *prevNode;

	prevNode = NULL;
	if (*head == NULL || nodeToDelete == NULL)
		return ;
	if (*head == nodeToDelete)
		*head = nodeToDelete->next;
	else
	{
		prevNode = *head;
		while (prevNode->next != NULL && prevNode->next != nodeToDelete)
			prevNode = prevNode->next;
		if (prevNode->next == nodeToDelete)
			prevNode->next = nodeToDelete->next;
		else
			return ;
	}
	free(nodeToDelete->name);
    free(nodeToDelete->value);
	free(nodeToDelete);
	return ;
}