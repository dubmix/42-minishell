/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:36:46 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/02 19:36:48 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*checksub(void)
{
	char	*substr;

	substr = malloc (1 * sizeof(char));
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
	substr = (char *) malloc (sizeof(char) * (len + 1));
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

/*int	main(void)
{
	char	const* str = "jeveuxreduirecettephrase";
	printf("%s\n", ft_substr(str,5,2));
}*/
