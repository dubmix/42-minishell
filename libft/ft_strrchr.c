/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:15:15 by edrouot           #+#    #+#             */
/*   Updated: 2022/11/30 18:15:17 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int	index;

	index = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *) s + index);
	while (index >= 0)
	{
		if (s[index] == (char)c)
			return ((char *) s + index);
		index--;
	}
	return (NULL);
}

/*int	main(void)
{
	const char	str[] = "teste";
	printf("%s", ft_strrchr(str, 'e'));
}*/
