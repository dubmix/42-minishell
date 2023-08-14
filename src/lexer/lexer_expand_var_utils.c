/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_var_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:25:02 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/13 17:28:00 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	look_into_envir(t_shell *cmd, t_token *var)
{
	t_env	*tmp;
	char	**string;

	tmp = cmd->env_lst;
	if (ft_strncmp(var->command, "$$", ft_strlen(var->command)) == 0)
	{
		free(var->command);
		var->command = ft_strdup("Process ID ");
		return ;
	}
	string = ft_split(var->command, '$');
	free(var->command);
	look_into_envir_sub(string, var, tmp);
	free_arr(string);
	if (tmp == NULL)
		var->command = ft_strdup("");
	return ;
}

void	look_into_envir_sub(char **string, t_token *var, t_env *tmp)
{
	char	*str;

	while (tmp != NULL)
	{
		if (ft_strncmp(string[0], "?", 1) == 0)
		{
			str = ft_itoa(g_xcode);
			var->command = ft_strdup(str);
			free(str);
			break ;
		}
		else if (ft_strncmp(string[0], tmp->name, ft_strlen(string[0])) == 0)
		{
			var->command = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

char	*look_into_envir_quote(t_shell *cmd, char *string)
{
	t_env	*tmp;
	char	*str;

	tmp = cmd->env_lst;
	while (tmp != NULL)
	{
		if (ft_strncmp(string, "?", ft_strlen(string)) == 0)
		{
			free(string);
			str = ft_itoa(g_xcode);
			string = ft_strdup(str);
			free(str);
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
	free(string);
	string = ft_strdup("");
	return (string);
}

int	string_variables_tri(char *command, int i)
{
	while (command[i] != '\0' && !check_valid_id(command[i])
		&& command[i] != '$')
		i++;
	if (command[i] == '$' && command[i - 1] != '$')
		i = i - 1;
	return (i);
}
