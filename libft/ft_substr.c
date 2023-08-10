/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:36:46 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/10 15:48:43 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*checksub(void)
{
	char	*substr;

	substr = ft_calloc(sizeof(char), 1);
	if (!substr)
		return (NULL);
	substr[0] = '\0';
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int		i;
	char				*substr;

	if (!s)
		return (0);
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if (ft_strlen(s) < start)
		return (checksub());
	substr = ft_calloc(sizeof(char), (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*ret;

// 	if (!s)
// 		return (NULL);
// 	if (start >= ft_strlen(s))
// 		len = 0;
// 	else if (ft_strlen(s + start) < len)
// 		len = ft_strlen(s + start);
// 	ret = malloc(sizeof(char) * (len + 1));
// 	if (!ret)
// 		return (NULL);
// 	ft_strlcpy(ret, s + start, len + 1);
// 	return (ret);
// }
