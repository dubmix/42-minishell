/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:21:47 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/13 13:49:23 by pdelanno         ###   ########.fr       */
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

void	free_all_inside_loop(t_shell *cmd)
{
	if (cmd->tok_alloc == 1)
		free_tok_lst(&cmd->tok_lst);
	if (cmd->cmd_alloc == 1)
		free_cmd_lst(&cmd->cmd_lst);
	if (cmd->line != NULL)
		free(cmd->line);
	if (cmd->heredoc_arr != NULL)
		free_arr(cmd->heredoc_arr);
	if (cmd->heredoc_string != NULL)
		free(cmd->heredoc_string);
	if (cmd->words_per_pipe_alloc == 1)
		free(cmd->words_per_pipe);
	if (cmd->pid_alloc == 1)
		free(cmd->pid);
}

void	free_all_exit(t_shell *cmd)
{
	if (cmd->env_alloc == 1)
		free_env_lst(&cmd->env_lst);
	if (cmd->envp_copy != NULL)
		free_arr(cmd->envp_copy);
	if (cmd->oldpwd != NULL)
		free(cmd->oldpwd);
}

void	ft_error(t_shell *cmd, char *string, int exit_code)
{
	ft_putstr_fd(string, STDERR_FILENO);
	free_all_inside_loop(cmd);
	g_xcode = exit_code;
	exit(g_xcode);
}

void	free_tok_lst(t_token **tok_lst)
{
	t_token	*temp;

	if (!*tok_lst || !tok_lst)
		return ;
	while (*tok_lst)
	{
		temp = (*tok_lst)->next;
		if ((*tok_lst)->command)
			free((*tok_lst)->command);
		free(*tok_lst);
		*tok_lst = temp;
	}
	*tok_lst = NULL;
}
