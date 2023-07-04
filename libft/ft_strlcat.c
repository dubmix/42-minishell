/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:27:26 by edrouot           #+#    #+#             */
/*   Updated: 2022/11/30 12:27:29 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	index;
	size_t	lsrc;
	size_t	ldst;
	char	*s;

	s = (char *)src;
	i = 0;
	index = 0;
	lsrc = ft_strlen(s);
	ldst = ft_strlen(dst);
	if (size < ldst + 1)
		return (lsrc + size);
	i = ldst;
	while (s[index] != '\0' && i + 1 < size)
	{
		dst[i] = s[index];
		i++;
		index++;
	}
	dst[i] = '\0';
	return (lsrc + ldst);
}

/*int	main(void)
{
	char	*dest = "helloooo";
	const char	*src = "gjkhj";
	printf("%ld\n", ft_strlcat(dest, src, 100));
}*/
