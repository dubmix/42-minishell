/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:26:25 by edrouot           #+#    #+#             */
/*   Updated: 2022/11/29 13:26:27 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n != 0)
	{
		*str = c;
		n--;
		str++;
	}
	return (s);
}

/*int	main(void)
{
	char	str[] = "je veux remplacer le je";
	int	c;
	size_t	a;

	c = 65;
	a = 2;
	printf("%s", ft_memset(str,c,8));
}*/
