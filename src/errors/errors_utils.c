/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:22:42 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/08 17:45:44 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_cmd_lst(t_single_cmd **cmd_lst)
{
	t_single_cmd	*current;
	t_single_cmd	*next;

	current = *cmd_lst;
	while (current != NULL)
	{
		next = current->next;
		delete_node_cmd(cmd_lst, current);
		current = next;
	}
	*cmd_lst = NULL;
}

void free_env_lst(t_env **env_lst)
{
    t_env *temp;
    while (*env_lst != NULL) 
	{
        temp = *env_lst;
        *env_lst = (*env_lst)->next;
        free(temp->full_string);
        free(temp->name);
        free(temp->value);
        free(temp);
    }
}

// void	free_env_lst(t_env **env_lst)
// {
// 	t_env	*current;
// 	t_env	*next;

// 	current = *env_lst;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		delete_node_env(env_lst, current);
// 		current = next;
// 	}
// 	*env_lst = NULL;
// }

void	delete_node_cmd(t_single_cmd **head, t_single_cmd *node_to_delete)
{
	t_single_cmd	*prev_node;

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
	free_arr(node_to_delete->command);
	if (node_to_delete->redir_in != 0)
		free(node_to_delete->redir_in_str);
	if (node_to_delete->redir_out != 0)
		free(node_to_delete->redir_out_str);
	if (node_to_delete->append != 0)
		free(node_to_delete->append_str);
	free(node_to_delete);
}

int	cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
