/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:03:03 by pdelanno          #+#    #+#             */
/*   Updated: 2022/12/13 17:35:58 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstmap(t_token *lst, void *(*f)(void *), void (*del)(void *))
{
	t_token	*first;
	t_token	*new;

	if (f == 0)
		return (NULL);
	first = 0;
	while (lst != 0)
	{
		new = ft_lstnew((*f)(lst->content));
		if (new == 0)
		{
			while (first != 0)
			{
				new = first->next;
				(*del)(first->content);
				free(first);
				first = new;
			}
			lst = 0;
			return (NULL);
		}
		ft_lstadd_back(&first, new);
		lst = lst->next;
	}
	return (first);
}
