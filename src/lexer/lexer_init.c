/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:45:43 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/10 14:24:18 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*init_envp(char **envp, t_shell *cmd)
{
	int		i;
	char	**string;
	t_env	*env_lst;
	int		size_env;

	size_env = size_envp(envp);
	cmd->envp_copy = (char **)malloc(sizeof(char *) * (size_env + 1));
	if (!cmd->envp_copy)
		ft_error(cmd, "env_lst allocation failure", 1);
	env_lst = NULL;
	i = 0;
	while (envp[i] != (void *)0)
	{
		if (!ft_strncmp(envp[i], "OLDPWD", 6))
			cmd->oldpwd = ft_substr(envp[i], 7, ft_strlen(envp[i]) - 7);
		cmd->envp_copy[i] = ft_strdup(envp[i]);
		string = ft_split(envp[i], '=');
		new_node_env(cmd, &env_lst, string, envp[i]);
		free_arr(string);
		i++;
	}
	cmd->envp_copy[i] = 0;
	cmd->env_alloc = 1;
	return (env_lst);
}

int	size_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

void	add_stack_back_env(t_env **env_lst, t_env *new)
{
	t_env	*tail;

	if (!new)
		return ;
	if (!(*env_lst))
	{
		*env_lst = new;
		return ;
	}
	tail = *env_lst;
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	tail->next = new;
}

void	new_node_env(t_shell *cmd, t_env **env_list, 
	char **string, char *full_string)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		ft_error(cmd, "New node env_lst allocation failure", 1);
	new->full_string = ft_strdup(full_string);
	new->name = ft_strdup(string[0]);
	new->index = 0;
	if (!string[1])
		new->value = ft_strdup("");
	else
		new->value = ft_strdup(string[1]);
	if (!new->name || !new->value)
		ft_error(cmd, "New node env_lst allocation failure", 1);
	new->next = NULL;
	add_stack_back_env(env_list, new);
}
