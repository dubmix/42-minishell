/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:45:43 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/23 11:57:36 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
int	size_envp(char **envp);
/* 
Take the size of the environnement
alloc char **
while loop -> alloc each line and create a new node with name and value of each line
free the split
*/
t_env	*init_envp(char **envp, t_shell *cmd)
{
	int		i;
	int		j;
	char	**string;
	t_env	*envir;
	int		size_env;

	size_env = size_envp(envp);
	cmd->envp_copy = (char **)malloc(sizeof(char *) * size_env + 1);
	envir = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		cmd->envp_copy[i] = ft_strdup(envp[i]);
		string = ft_split(envp[i], '=');
		new_node_env(&envir, string);
		j = 0;
		while (string[j] != NULL)
		{
			free(string[j]);
			j++;
		}
		i++;
	}
	return (envir);
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

/*create a new node, copy in name and value and add it to the back of the list */
void	new_node_env(t_env **env_list, char **string)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(string[0]);
	new->value = ft_strdup(string[1]);
	if (!new->name || !new->value)
		return ; // error handling
	new->next = NULL;
	add_stack_back_env(env_list, new);
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
	char	*temp;
	int		length;

	i = 0;
	temp = string;
	length = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] == '$')
		{
			while (temp[i] != ' ' && temp[i] != 34)
				i++;
		}
		else
			length++;
		i++;
	}
	return (length);
}