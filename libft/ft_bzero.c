/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:45:26 by edrouot           #+#    #+#             */
/*   Updated: 2022/11/29 17:45:28 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n != 0)
	{
		*str = '\0';
		n--;
		str++;
	}
}

/*int	main(void)
{
	char	str[] = "je veux remplacer le je";
	int	c;
	size_t	a;

	c = 65;
	a = 2;
	//printf("%s\n", ft_bzero(str,8));
	//printf("%s\n", bzero(str,8));
}*/
