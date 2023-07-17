/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalpha.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:19:33 by edrouot           #+#    #+#             */
/*   Updated: 2022/11/29 12:19:35 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_isalpha(100)); // return 1
	printf("%d\n", ft_isalpha('a')); // return 1
	printf("%d\n", ft_isalpha('!')); // return 0
	printf("%d\n", ft_isalpha(95)); // return 0
	printf("%d\n", ft_isalpha(65)); // return 1
	printf("%d\n", ft_isalpha(97)); // return 1
}*/
