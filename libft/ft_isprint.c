/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:44:39 by edrouot           #+#    #+#             */
/*   Updated: 2022/11/29 12:44:42 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_isprint(31)); // return 0
	printf("%d\n", ft_isprint(32)); // return 1
	printf("%d\n", ft_isprint('1')); // return 1
	printf("%d\n", ft_isprint(57)); // return 1
	printf("%d\n", ft_isprint(126)); // return 1
	printf("%d\n", ft_isprint(127)); // return 0
}*/
