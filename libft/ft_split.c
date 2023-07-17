/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:00:35 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/09 16:00:36 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	countsubstr(char const *s, char c)
{
	int		words;
	size_t	index;

	index = 0;
	words = 0;
	while (s[index] != '\0')
	{
		if ((s[index] != c && s[index + 1] == c)
			|| (s[index] != c && s[index + 1] == '\0'))
			words++;
		index++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	index;
	int		i;
	int		start;

	index = 0;
	i = 0;
	start = 0;
	arr = malloc(sizeof (char *) * (countsubstr(s, c) + 1));
	if (!arr || !s)
		return (NULL);
	while (index < ft_strlen(s))
	{
		if (s[index] == c && s[index + 1] != c)
			start = index + 1;
		if ((s[index] != c && s[index + 1] == c)
			|| (s[index] != c && s[index + 1] == '\0'))
		{
			arr[i] = ft_substr(s, start, (index + 1) - start);
			i++;
		}
		index++;
	}
	arr[i] = 0;
	return (arr);
}

/* int	main(void)
{
	char *s = "lorem ipsum doendisse";
	char	c;
	int		i;
	char **str;
	i = 0;
	c = ' ';
	str = ft_split(s, c);
} */
