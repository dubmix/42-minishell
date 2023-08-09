/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:21:47 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/09 13:08:48 by edrouot          ###   ########.fr       */
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
	free(arr);
}

void	free_all(t_shell *cmd, int type)
{
	if (type == 0)
		free_tok_lst(cmd->tok_lst);
	else if (type == 1)
		free_cmd_lst(&cmd->cmd_lst);
	else if (type == 2)
	{
		free_tok_lst(cmd->tok_lst);
		free_cmd_lst(&cmd->cmd_lst);
	}
	else if (type == 3)
		free_env_lst(&cmd->env_lst);
	else if (type == 4)
		free_shell(cmd);
	else if (type == 5)
	{
		free_env_lst(&cmd->env_lst);
		free_arr(cmd->envp_copy);
		free(cmd->oldpwd);
	}
}

void	ft_error(t_shell *cmd, char *string, int type, int exit_code)
{
	ft_putstr_fd(string, STDERR_FILENO);
	if (type == 0)
		free_all(cmd, 0);
	else if (type == 1)
		free_all(cmd, 1);
	else if (type == 2)
		free_all(cmd, 2);
	else if (type == 3)
		free_all(cmd, 3);
	else if (type == 4)
		free_all(cmd, 4);
	else if (type == 5)
	{
		free_all(cmd, 1);
		free_all(cmd, 3);
	}
	else if (type == 6)
	{
		free_all(cmd, 1);
		free_all(cmd, 2);
		free_all(cmd, 3);
	}
	g_xcode = exit_code;
	exit(g_xcode);
}

void	free_shell(t_shell *cmd)
{
	free_tok_lst(cmd->tok_lst);
	free_cmd_lst(&cmd->cmd_lst);
	cmd->size_arr_var = 0;
	if (cmd->nb_of_heredocs != 0)
	{
		free_arr(cmd->heredoc_arr);
		if (cmd->heredoc_string != NULL)
			free(cmd->heredoc_string);
	}
	cmd->nb_of_heredocs = 0;
	cmd->nb_of_pipes = 0;
	cmd->nb_of_tokens = 0;
	cmd->nb_of_heredocs = 0;
	free(cmd->line);
	// free(cmd->tok_lst);
	free(cmd->cmd_lst);
}

void free_tok_lst(t_token *tok_lst)
{
    while (tok_lst != NULL) 
	{
        t_token *temp = tok_lst;
        tok_lst = tok_lst->next;
        free(temp->command); // Free the command string
        free(temp);
    }
}


// void	free_tok_lst(t_token **tok_lst)
// {
// 	t_token	*current;
// 	t_token	*next;
// 	printf("IS FREEING BEG \n");

// 	current = *tok_lst;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		delete_node_tok(tok_lst, current);
// 		current = next;
// 	}
// 	free(current);
// 	*tok_lst = NULL;
// 	printf("IS FREEING END\n");
// }
// void	free_tok_lst(t_token **tok_lst)
// {
// 	t_token	*temp;

// 	printf("IS FREEING \n");
// 	if (!*tok_lst || !tok_lst)
// 		return ;
// 	printf("IS FREEING BEG \n");
// 	while (*tok_lst)
// 	{
// 		temp = (*tok_lst)->next;
// 		if ((*tok_lst)->command)
// 			free((*tok_lst)->command);
// 		free(*tok_lst);
// 		*tok_lst = temp;
// 	}
// // print_list_tok(*tok_lst);
// // 		printf("IS FREEING END\n");
// 	*tok_lst = NULL;

// }
