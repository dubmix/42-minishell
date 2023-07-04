/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:18:16 by edrouot           #+#    #+#             */
/*   Updated: 2022/11/29 18:18:18 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned long		i;
	unsigned char		*strdest;
	const unsigned char	*strsrc;

	strdest = dest;
	strsrc = src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (strdest > strsrc)
		while (n-- > 0)
			strdest[n] = strsrc[n];
	else
	{
		while (i < n)
		{
			strdest[i] = strsrc[i];
			i++;
		}
	}
	return (dest);
}

/*int	main(void)
{
	char	str[] = "aaaaaaaaaaaaaa";
	char	str1[] = "bbbbbbbbbbbb";
	
	printf("%s\n", ft_memmove(str1, str, 8));
}*/
