/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:34:04 by edrouot           #+#    #+#             */
/*   Updated: 2022/11/29 12:34:06 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_isdigit(47)); // return 0
	printf("%d\n", ft_isdigit('0')); // return 1
	printf("%d\n", ft_isdigit('1')); // return 1
	printf("%d\n", ft_isdigit(57)); // return 1
	printf("%d\n", ft_isdigit(58)); // return 0
	printf("%d\n", ft_isdigit(97)); // return 0
}*/
