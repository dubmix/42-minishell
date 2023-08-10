/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:14:42 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/10 15:37:01 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strdup(const char *s)
// {
// 	char	*str2;
// 	int		index;
// 	int		length;

// 	index = 0;
// 	length = ft_strlen(s);
// 	str2 = (char *)malloc(sizeof(char) * (length + 1));
// 	if (!str2)
// 		return (NULL);
// 	while (s[index] != '\0')
// 	{
// 		str2[index] = s[index];
// 		index++;
// 	}
// 	str2[index] = '\0';
// 	return (str2);
// }

char	*ft_strdup(const char *s)
{
	int		len;
	char	*ret;

	len = ft_strlen(s);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, len + 1);
	return (ret);
}

/*int	main(void)
{
	const char	*s;
	s = "testundeuxtrois";
	
	printf("%s\n",ft_strdup(s));
}*/
