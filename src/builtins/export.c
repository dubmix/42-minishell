/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:29:20 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/02 09:43:20 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize_test(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	export(t_shell *cmd)
{
	char    **str;
	t_shell **tmp;

	tmp = &cmd;
	while ((*tmp)->cmd_lst)
	{
		str = ft_split(((*tmp)->cmd_lst->command[1]), '=');
		// while ((*tmp)->env_lst)
		// {
			if (var_exists((*tmp)->env_lst, str[0]) == 0)
			{
				write(1, "h", 1);
				printf("%s %s\n", str[0], str[1]);
				printf("list size at beg of export is %d\n", ft_lstsize_test((*tmp)->env_lst));
				new_node_env(&(*tmp)->env_lst, str);
				//printf("%d\n", ft_lstsize_test((*tmp)->env_lst));
				//free_array(str);
				break ;
			}
			//(*tmp)->env_lst = (*tmp)->env_lst->next;
			//free_array(str);
		//}
		(*tmp)->cmd_lst = (*tmp)->cmd_lst->next;
	}
	// print_list((*tmp)->env_lst);
	printf("list size at end of export is%d\n", ft_lstsize_test((cmd->env_lst)));
	update_envp_copy(cmd);
	return (EXIT_SUCCESS);
}

void	update_envp_copy(t_shell *cmd)
{
	t_env *temp;
	int i;
	char *string;
	char *temp_string;
	
	free_arr(cmd->envp_copy);
	cmd->envp_copy = (char **)malloc(sizeof(ft_lstsize_test(cmd->env_lst) + 1));
	temp = cmd->env_lst;
	i = 0;
	while(temp != NULL)
	{
		printf("list size at end of export is%d %d\n", ft_lstsize_test((cmd->env_lst)), i);
		string = ft_strjoin(temp->name, "=");
		temp_string = ft_strjoin(string, temp->value);
		free(string);
		cmd->envp_copy[i] = ft_strdup(temp_string);
		free(temp_string);
		i++;
		temp = temp->next;
	}

}

int	export_error(char *str)
{
	printf("minishell: export: '%s': not a valid identifier", str);
	return(EXIT_FAILURE);
}

int check_valid_id(char c)
{
	if (c >= 32 && c <= 47)
		return (1);
	else if (c >= 58 && c <= 64)
		return (1);
	else if (c >= 91 && c <= 96)
		return (1);
	else if (c >= 123 && c <= 126)
		return (1);
	else
		return (0);
}

int var_exists(t_env *env, char *str)
{
	t_env *head;

	head = env;
	while (head)
	{
		if (ft_strncmp(head->name, str, ft_strlen(str)) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

int	check_param(char *str)
{
	int i;

	i = 0;
	if (str[i] == '=')
		return (EXIT_FAILURE);
	 if (ft_isdigit(str[i]))
	 	return (export_error(str));
	// if (ft_findchar(str, '=') == 0)
	// 	return (export_error(str));
	// while (str[i] != '=')
	// {
	// 	if (check_valid_id(str[i]) == 1)
	// 		return (export_error(str));
	// 	i++;
	// }
	return (0);
}

int	ft_findchar(char *str, char c)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:29:20 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/31 11:50:52 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize_test(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	export(t_shell *cmd)
{
	char    **str;
	t_shell **tmp;

	tmp = &cmd;
	while ((*tmp)->cmd_lst)
	{
		str = ft_split(((*tmp)->cmd_lst->command[1]), '=');
		// while ((*tmp)->env_lst)
		// {
			if (var_exists((*tmp)->env_lst, str[0]) == 0)
			{
				//printf("%s %s\n", str[0], str[1]);
				printf("list size at beg of export is %d\n", ft_lstsize_test((*tmp)->env_lst));
				new_node_env(&(*tmp)->env_lst, str, *(*tmp)->cmd_lst->command);
				//printf("%d\n", ft_lstsize_test((*tmp)->env_lst));
				//free_array(str);
				break ;
			}
			(*tmp)->env_lst = (*tmp)->env_lst->next;
			//free_array(str);
		//}
		(*tmp)->cmd_lst = (*tmp)->cmd_lst->next;
	}
	printf("list size at end of export is%d\n", ft_lstsize_test((cmd->env_lst)));
	return (EXIT_SUCCESS);
}

int	export_error(char *str)
{
	printf("minishell: export: '%s': not a valid identifier", str);
	return(EXIT_FAILURE);
}

int check_valid_id(char c)
{
	if (c >= 32 && c <= 47)
		return (1);
	else if (c >= 58 && c <= 64)
		return (1);
	else if (c >= 91 && c <= 96)
		return (1);
	else if (c >= 123 && c <= 126)
		return (1);
	else
		return (0);
}

int var_exists(t_env *env, char *str)
{
	t_env *head;

	head = env;
	while (head)
	{
		if (ft_strncmp(head->name, str, ft_strlen(str)) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

int	check_param(char *str)
{
	int i;

	i = 0;
	if (str[i] == '=')
		return (EXIT_FAILURE);
	 if (ft_isdigit(str[i]))
	 	return (export_error(str));
	// if (ft_findchar(str, '=') == 0)
	// 	return (export_error(str));
	// while (str[i] != '=')
	// {
	// 	if (check_valid_id(str[i]) == 1)
	// 		return (export_error(str));
	// 	i++;
	// }
	return (0);
}

int	ft_findchar(char *str, char c)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
