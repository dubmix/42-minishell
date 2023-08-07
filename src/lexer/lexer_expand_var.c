/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:45:38 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/07 16:28:47 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	look_into_envir(t_shell *cmd, t_token *var);
char	**string_variables(t_shell *cmd, t_token *var);
void	double_quote_env(t_shell *cmd, t_token *var);
char	*look_into_envir_quote(t_shell *cmd, char *string);
char	**string_variables_bis(t_shell *cmd, char *command,
			char **arr_string, int i);
char	*double_quote_env_bis(char *command, char *new_string, 
			char **arr_var, int i);

/*first function : look for two things :
either a type variable ($) or double quote (state)*/

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
	int		i;

	i = 0;
	cmd->size_arr_var = countsubstr(var->command, '$');
	arr_string = (char **)malloc(sizeof(char *) * (cmd->size_arr_var + 1));
	if (!arr_string)
		ft_error(cmd, "Memory allocation failed for expander", 5, 50);
	arr_string = string_variables_bis(cmd, var->command, arr_string, i);
	return (arr_string);
}

char	**string_variables_bis(t_shell *cmd, char *command,
		char **arr_string, int i)
{
	int	j;
	int	start;

	j = 0;
	start = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '$')
		{
			i++;
			start = i;
			while (command[i] != '\0' && !check_valid_id(command[i])
				&& command[i] != '$')
				i++;
			if (command[i] == '$')
				i = i - 1;
			arr_string[j] = look_into_envir_quote(cmd, ft_substr(command, start,
						i - start));
			j++;
		}
		i++;
	}
	arr_string[j] = 0;
	return (arr_string);
}
/*  create via string_variables an array with the correct values of the variable
then rewrite the command line with str_join,
	replacing each var $XXX with the correct value*/

void	double_quote_env(t_shell *cmd, t_token *var)
{
	char	**arr_var;
	char	*new_string;
	int		i;

	i = 0;
	arr_var = string_variables(cmd, var);
	new_string = (char *)malloc(sizeof(char) * (length_arr_var(arr_var, cmd)
				+ length_string_without_var(var->command)) + 1);
	if (!new_string)
		ft_error(cmd, "Memory allocation failed for expander", 5, 50);
	new_string = double_quote_env_bis(var->command, new_string, arr_var, i);
	free_arr(arr_var);
	free(var->command);
	var->command = ft_strdup(new_string);
	free(new_string);
}

char	*double_quote_env_bis(char *command, char *new_string, 
		char **arr_var, int i)
{
	int		j;
	int		k;
	int		n;

	j = 0;
	k = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '$')
		{
			i++;
			n = 0;
			while (command[i] != '\0'
				&& !check_valid_id(command[i])
				&& command[i] != '$')
				i++;
			while (arr_var[k][n] != '\0')
				new_string[j++] = arr_var[k][n++];
			k++;
		}
		else
			new_string[j++] = command[i++];
	}
	new_string[j] = '\0';
	return (new_string);
}


/*  we need only what is after the $ ($USER
	-> USER) and compare with USER with env_lst
and replace the correct value in the tok_lst*/

void	look_into_envir(t_shell *cmd, t_token *var)
{
	t_env	*tmp;
	char	**string;

	tmp = cmd->env_lst;
	string = ft_split(var->command, '$');
	free(var->command);
	while (tmp != NULL)
	{
		if (ft_strncmp(string[0], "?", 1) == 0)
		{
			var->command = ft_strdup(ft_itoa(g_xcode));
			break ;
		}
		else if (ft_strncmp(string[0], tmp->name, ft_strlen(var->command)) == 0)
		{
			var->command = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	free_arr(string);
	if (tmp == NULL)
		var->command = ft_strdup("");
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
			string = ft_strdup(ft_itoa(g_xcode));
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
