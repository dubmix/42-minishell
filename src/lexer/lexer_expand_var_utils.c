/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_var_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:25:02 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/10 09:40:02 by pdelanno         ###   ########.fr       */
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
	string = ft_split(var->command, '$');
	free(var->command);
	look_into_envir_sub(string, var, tmp);
	// while (tmp != NULL)
	// {
	// 	if (ft_strncmp(string[0], "$", ft_strlen(string[0])) == 0)
	// 	{
	// 		var->command = ft_strdup("Process ID ");
	// 		break ;
	// 	}
	// 	else if (ft_strncmp(string[0], "?", 1) == 0)
	// 	{
	// 		var->command = ft_strdup(ft_itoa(g_xcode));
	// 		break ;
	// 	}
	// 	else if (ft_strncmp(string[0], tmp->name, ft_strlen(string[0])) == 0)
	// 	{
	// 		var->command = ft_strdup(tmp->value);
	// 		break ;
	// 	}
	// 	tmp = tmp->next;
	// }
	free_arr(string);
	if (tmp == NULL)
		var->command = ft_strdup("");
	return ;
}

void	look_into_envir_sub(char **string, t_token *var, t_env *tmp)
{
	while (tmp != NULL)
	{
		if (ft_strncmp(string[0], "$", ft_strlen(string[0])) == 0)
		{
			var->command = ft_strdup("Process ID ");
			return ;
		}
		else if (ft_strncmp(string[0], "?", 1) == 0)
		{
			var->command = ft_strdup(ft_itoa(g_xcode));
			return ;
		}
		else if (ft_strncmp(string[0], tmp->name, ft_strlen(string[0])) == 0)
		{
			var->command = ft_strdup(tmp->value);
			return ;
		}
		tmp = tmp->next;
	}
}

char	*look_into_envir_quote(t_shell *cmd, char *string)
{
	t_env	*tmp;

	tmp = cmd->env_lst;
	while (tmp != NULL)
	{
		if (ft_strncmp(string, "$", ft_strlen(string)) == 0)
		{
			string = look_into_envir_quote_sub(string);
			return (string);
		}
		else if (ft_strncmp(string, "?", ft_strlen(string)) == 0)
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

char	*look_into_envir_quote_sub(char *string)
{
	free(string);
	string = ft_strdup("Process ID ");
	return (string);
}
