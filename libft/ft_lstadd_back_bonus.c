/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:12:55 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/16 16:17:32 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst != NULL && *lst != NULL)
	{
		tmp = *lst;
		tmp = ft_lstlast(*lst);
		tmp->next = new;
		return ;
	}
	*lst = new;
}
