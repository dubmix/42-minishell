/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:45:38 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/29 14:02:01 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	look_into_envir(t_shell *cmd, t_token *var);
char	**string_variables(t_shell *cmd, t_token *var);
void	double_quote_env(t_shell *cmd, t_token *var);
char	*look_into_envir_quote(t_shell *cmd, char *string);
/*first function : look for two things : either a type variable ($) or double quote (state)*/
void	expand_var(t_shell *cmde)
{
	t_token	*tmp;

	tmp = cmde->tok_lst;
	while (tmp != NULL)
	{
		if (tmp->type == 4)
		{
			look_into_envir(cmde, tmp);
			tmp->type = 0;
		}
		else if (tmp->state == 1)
		{
			double_quote_env(cmde, tmp);
			tmp->type = 0;
		}
		tmp = tmp->next;
	}
}

char	**string_variables(t_shell *cmd, t_token *var)
{
	char	**arr_string;
	char	*temp;
	int		i;
	int		j;
	int		start;

	temp = var->command;
	i = 0;
	j = 0;
	start = 0;
	cmd->size_arr_var = countsubstr(var->command, '$');
	arr_string = (char **)malloc(sizeof(char *) * (cmd->size_arr_var + 1));
	if (!arr_string)
		return (NULL);
	while (temp[i] != '\0')
	{
		if (temp[i] == '$')
		{
			start = i + 1; 
			while (temp[i] != ' ' && temp[i] != 34)
				i++;
			arr_string[j] = look_into_envir_quote(cmd, ft_substr(var->command,
					start, i - start));
			j++;
		}
		i++;
	}
	arr_string[j] = 0;
	return (arr_string);
}
/*  create via string_variables an array with the correct values of the variable 
then rewrite the command line with str_join, replacing each var $XXX with the correct value*/
void	double_quote_env(t_shell *cmd, t_token *var)
{
	int		i;
	char	**arr_var;
	int		j;
	char	*new_string;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	arr_var = string_variables(cmd, var); 
	new_string = (char *)malloc(sizeof(char) * (length_arr_var(arr_var, cmd)
			+ length_string_without_var(var->command)) + 1);
	if (!new_string)
		return ;
	while (var->command[i] != '\0')
	{
		if (var->command[i] == '$')
		{
			while (var->command[i] != ' ' && var->command[i] != 34)
				i++;
			new_string = ft_strjoin(new_string, arr_var[k]);
			j = ft_strlen(new_string);
			k++;
		}
		new_string[j] = var->command[i];
		i++;
		j++;
	}
	new_string[j] = '\0';
	free_arr(arr_var);
	free(var->command);
	var->command = ft_strdup(new_string);
	free(new_string);
	// free_arr(arr_var);  // cause issue, to be checked later
}

 /*  we need only what is after the $ ($USER -> USER) and compare with USER with env_lst 
 and replace the correct value in the tok_lst*/
void	look_into_envir(t_shell *cmd, t_token *var)
{
	t_env	*tmp;
	char	**string;
	int		j;

	tmp = cmd->env_lst;
	j = 0;
	string = ft_split(var->command, '$');
	while (tmp != NULL)
	{
		if (ft_strncmp(string[0], tmp->name, ft_strlen(var->command)) == 0)
		{
			free(var->command);
			var->command = ft_strdup(tmp->value);
			var->type = 0;
			break ;
		}
		tmp = tmp->next;
	}
	while (string[j] != NULL)
	{
		free(string[j]);
		j++;
	}
	if (tmp == NULL)
	{
		free(var->command);
		var->command = ft_strdup("");
	}
	return ;
}

char	*look_into_envir_quote(t_shell *cmd, char *string)
{
	t_env	*tmp;

	tmp = cmd->env_lst;
	while (tmp != NULL)
	{
		if (ft_strncmp(string, tmp->name, ft_strlen(string)) == 0)
		{
			free(string);
			string = ft_strdup(tmp->value);
			return (string);
		}
		tmp = tmp->next;
	}
	return ("");
}
