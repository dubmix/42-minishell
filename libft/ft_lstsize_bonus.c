/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:06:59 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/15 20:07:00 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*tmp;

	counter = 0;
	tmp = lst;
	if (!lst)
		return (0);
	while (tmp->next != NULL)
	{
		counter++;
		tmp = tmp->next;
	}
	if (tmp->next == NULL)
		counter++;
	return (counter);
}
