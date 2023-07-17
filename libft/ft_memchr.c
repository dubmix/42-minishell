/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:38:28 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/01 20:38:30 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	long unsigned int	index;
	const char			*tmps;

	tmps = s;
	index = 0;
	while (index < n)
	{
		if (tmps[index] == (char)c)
			return ((char *) &tmps[index]);
		else
			index++;
	}
	return (0);
}

/*
int	main(void)
{
	const char	str[] = "je teste cette fonction";
	printf("%p", ft_memchr(str, 116, 8));
}*/
