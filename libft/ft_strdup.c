/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:14:42 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/08 16:14:44 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str2;
	int		index;
	int		length;

	index = 0;
	length = ft_strlen(s);
	str2 = (char *)malloc(sizeof(char) * (length + 1));
	if (str2 == 0)
		return (NULL);
	while (s[index] != '\0')
	{
		str2[index] = s[index];
		index++;
	}
	str2[index] = '\0';
	return (str2);
}

/*int	main(void)
{
	const char	*s;
	s = "testundeuxtrois";
	
	printf("%s\n",ft_strdup(s));
}*/
