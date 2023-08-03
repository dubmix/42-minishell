/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:45:38 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/03 20:57:52 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	look_into_envir(t_shell *cmd, t_token *var);
char	**string_variables(t_shell *cmd, t_token *var);
void	double_quote_env(t_shell *cmd, t_token *var);
char	*look_into_envir_quote(t_shell *cmd, char *string);

/*first function : look for two things : either a type variable ($) or double quote (state)*/
void	expand_var(t_shell *cmd)
{
	t_token	*tmp;

	tmp = cmd->tok_lst;

	while (tmp != NULL)
	{
		if (tmp->type == 4)
		{
			look_into_envir(cmd, tmp);
			tmp->type = 0;
		}
		else if (tmp->state == 1)
		{
			double_quote_env(cmd, tmp);
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
			i++;
			start = i;
			while (var->command[i] != '\0' && !check_valid_id_test(var->command[i]) && var->command[i] != '$')
				i++;
			if (var->command[i] == '$')
				i = i - 1;
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
	int n = 0;
	arr_var = string_variables(cmd, var);
	new_string = (char *)malloc(sizeof(char) * (length_arr_var(arr_var, cmd) + length_string_without_var(var->command)) + 1);
	if (!new_string)
		return ;
	while (var->command[i] != '\0')
	{
		if (var->command[i] == '$')
		{
			i++;
			while (var->command[i] != '\0' && !check_valid_id_test(var->command[i]) && var->command[i] != '$')
   				i++;
			while (arr_var[k][n] != '\0')
			{
				new_string[j] = arr_var[k][n];
				j++;
				n++;
			}
			n = 0;
			k++;
		}
		else
		{
			new_string[j] = var->command[i];
			i++;
			j++;				
		}
	}
	new_string[j] = '\0';
	free_arr(arr_var);
	free(var->command);
	var->command = ft_strdup(new_string);
	free(new_string);
}

int check_valid_id_test(char c) 
{
    if ((c >= 'a' && c <= 'z') ||       // Lowercase letters
        (c >= 'A' && c <= 'Z') ||       // Uppercase letters
        (c >= '0' && c <= '9') ||       // Digits
        (c == '_')) {                   // Underscore
        return 0; // Valid character for an identifier
    } else 
	{
        return 1; // Invalid character for an identifier
    }
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
		if (ft_strncmp(string[0], "?", 1) == 0)
		{
			free(var->command);
			var->command = ft_strdup(ft_itoa(cmd->exit_code));
			break;
		}
		else if (ft_strncmp(string[0], tmp->name, ft_strlen(var->command)) == 0)
		{
			free(var->command);
			var->command = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	free_arr(string);
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
		if (ft_strncmp(string, "?", 1) == 0)
		{
			free(string);
			string = ft_strdup(ft_itoa(cmd->exit_code));
			return (string);
		}
		else if (ft_strncmp(string, tmp->name, ft_strlen(string)) == 0)
		{
			free(string);
			string = ft_strdup(tmp->value);
			return (string);
		}
		tmp = tmp->next;
	}
	return ("");
}
