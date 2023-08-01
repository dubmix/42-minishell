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

int unset_error(char **command)
{
    int i;
    int j;

    i = 1;
    j = 0;
    if (!command[i])
    {
        printf("minishell: unset: not enough arguments\n");
        return (1);
    }
    while (command[i])
    {
        while (command[i][j])
        {
            if (command[i][j] == '/' || command[i][j] == '=')
            {    
                printf("minishell: unset: %s: invalid parameter name\n", command[i]);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int unset(t_shell *cmd, char **command)
{
    t_shell **tmp;
    t_env *tmp_env;
    int i;

    tmp = &cmd;
    i = 1;
    if (unset_error(command) == 1)
        return(EXIT_FAILURE);
    while (command[i])
    {
        if (ft_strncmp(command[i], " ", 1) != 0)
        {
            tmp_env = (*tmp)->env_lst;
            while(tmp_env)
            {
                if (ft_strncmp(tmp_env->name, command[i], 
                        ft_strlen(tmp_env->name)) == 0)
                {
                    delete_node_env(&(*tmp)->env_lst, tmp_env);
                    break ;
                }
                tmp_env = tmp_env->next;
            }
        }
        i++;
    }
    update_envp_copy(cmd);
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
    free(node_to_delete->full_string);
	free(node_to_delete);
	return ;
}