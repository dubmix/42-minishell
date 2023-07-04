/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:37:47 by edrouot           #+#    #+#             */
/*   Updated: 2022/11/30 17:37:49 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	index;

	index = 0;
	while (s[index])
	{
		if (s[index] == (char)c)
			return ((char *) &s[index]);
		index++;
	}
	if ((char) c == s[index])
		return ((char *) &s[index]);
	return (NULL);
}

/*int	main(void)
{
	const char	str[] = "teste";
	printf("%s", ft_strchr(str, 'e'));
}*/
