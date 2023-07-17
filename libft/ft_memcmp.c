/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:23:29 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/02 15:23:30 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const char *s1, const char *s2, size_t n)
{
	size_t				index;
	const unsigned char	*tmps1;
	const unsigned char	*tmps2;

	tmps1 = (const unsigned char *)s1;
	tmps2 = (const unsigned char *)s2;
	index = 0;
	while (index < n)
	{
		if (tmps1[index] == tmps2[index])
			index++;
		else if (tmps1[index] < tmps2[index])
			return (-1);
		else if (tmps1[index] > tmps2[index])
			return (1);
	}
	return (0);
}

/*int	main(void)
{
	const char	str1[] = "helloworld";
	const char	str2[] = "hedloworlc";
	printf("%d", ft_strncmp(str1, str2, 8));
}

-1 if s1 less than s2
0 if s1 is equal to s2
+1 if s1 is greater than s2*/
