/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:41:16 by edrouot           #+#    #+#             */
/*   Updated: 2022/11/29 12:41:18 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c < 0 || c > 127)
		return (0);
	else
		return (1);
}

/*int	main(void)
{
	printf("%d\n", ft_isascii(-1)); // return 0
	printf("%d\n", ft_isascii('0')); // return 1
	printf("%d\n", ft_isascii('b')); // return 1
	printf("%d\n", ft_isascii(127)); // return 1
	printf("%d\n", ft_isascii(128)); // return 0
	printf("%d\n", ft_isascii(200)); // return 0
}*/
