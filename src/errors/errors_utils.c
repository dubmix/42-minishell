/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:22:42 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/14 11:37:34 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_cmd_lst(t_single_cmd **cmd_lst)
{
	t_single_cmd	*temp;

	if (!*cmd_lst || !cmd_lst)
		return ;
	while (*cmd_lst)
	{
		temp = (*cmd_lst)->next;
		if ((*cmd_lst)->redir_in != 0)
			free((*cmd_lst)->redir_in_str);
		if ((*cmd_lst)->redir_out != 0)
			free((*cmd_lst)->redir_out_str);
		if ((*cmd_lst)->append != 0)
			free((*cmd_lst)->append_str);
		if ((*cmd_lst)->command != NULL)
			free_arr((*cmd_lst)->command);
		free(*cmd_lst);
		*cmd_lst = temp;
	}
	*cmd_lst = NULL;
}

void	free_env_lst(t_env **env_lst)
{
	t_env	*temp;

	if (!*env_lst || !env_lst)
		return ;
	while (*env_lst)
	{
		temp = (*env_lst)->next;
		if ((*env_lst)->full_string)
			free((*env_lst)->full_string);
		if ((*env_lst)->name)
			free((*env_lst)->name);
		if ((*env_lst)->value)
			free((*env_lst)->value);
		free(*env_lst);
		*env_lst = temp;
	}
	*env_lst = NULL;
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
	g_xcode = 1;
	return (EXIT_FAILURE);
}
