/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trncmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:15:10 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/01 20:15:11 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	long unsigned int	index;

	index = 0;
	if (!s1 || !s2 || n == 0)
		return (0);
	while ((s1[index] != '\0' || s2[index] != '\0') && index < n)
	{
		if (s1[index] == s2[index])
			index++;
		else
			return ((unsigned char)(s1[index]) - (unsigned char)(s2[index]));
	}
	return (0);
}

/*int	main(void)
{
		printf("%d\n",ft_strncmp("salut", "salut", 5)); //0
		printf("%d\n",ft_strncmp("test", "testss", 7)); // -1
		printf("%d\n",ft_strncmp("testss", "test", 7)); //1
		printf("%d\n",ft_strncmp("test", "tEst", 4)); //1
		printf("%d\n",ft_strncmp("", "test", 4));// -1
		printf("%d\n",ft_strncmp("test", "", 4)); //1
		printf("%d\n",ft_strncmp("abcdefghij", "abcdefgxyz", 3)); //0
		printf("%d\n",ft_strncmp("abcdefgh", "abcdwxyz", 4)); //0
		printf("%d\n",ft_strncmp("zyxbcdefgh", "abcdwxyz", 0)); //0
		printf("%d\n",ft_strncmp("abcdefgh", "", 0)); //0
		printf("%d\n",ft_strncmp("test\200", "test\0", 6)); //1
}*/
