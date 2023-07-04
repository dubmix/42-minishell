/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:36:56 by edrouot           #+#    #+#             */
/*   Updated: 2022/11/29 12:36:58 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_isalnum(47)); // return 0
	printf("%d\n", ft_isalnum('0')); // return 1
	printf("%d\n", ft_isalnum('b')); // return 1
	printf("%d\n", ft_isalnum(57)); // return 1
	printf("%d\n", ft_isalnum(58)); // return 0
	printf("%d\n", ft_isalnum(97)); // return 1
}*/
