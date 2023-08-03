/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:45:43 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/03 11:44:33 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	size_envp(char **envp);

/* Take the size of the environnement
alloc char **
while loop -> alloc each line and
create a new node with name and value of each line
free the split */

t_env	*init_envp(char **envp, t_shell *cmd)
{
	int		i;
	int		j;
	char	**string;
	t_env	*envir;
	int		size_env;

	size_env = size_envp(envp);
	cmd->envp_copy = (char **)malloc(sizeof(char *) * (size_env + 1));
	envir = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		cmd->envp_copy[i] = ft_strdup(envp[i]);
		string = ft_split(envp[i], '=');
		new_node_env(&envir, string, envp[i]);
		j = 0;
		free_arr(string);
		i++;
	}
	cmd->envp_copy[i] = 0;
	return (envir);
}

static int	size_envp(char **envp)
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

/*create a new node, copy in name and value and 
add it to the back of the list */

void	new_node_env(t_env **env_list, char **string, char *full_string)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	new->full_string = ft_strdup(full_string);
	new->name = ft_strdup(string[0]);
	new->index = 0;
	if (!string[1])
		new->value = ft_strdup("");
	else
		new->value = ft_strdup(string[1]);
	if (!new->name || !new->value)
		return ;// error handling
	new->next = NULL;
	add_stack_back_env(env_list, new);
}
