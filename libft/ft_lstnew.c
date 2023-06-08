/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:00:46 by pdelanno          #+#    #+#             */
/*   Updated: 2022/12/13 17:43:21 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstnew(void	*content)

{
	t_token	*newnode;

	newnode = (t_token *)malloc(sizeof(*newnode));
	if (newnode == 0)
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}
