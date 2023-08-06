/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:32:19 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/06 09:44:14 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	checkset(char s, char const *set)
{
	int	index;

	index = 0;
	while (set[index] != '\0')
	{
		if (s == set[index])
			return (1);
		index++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strim;
	int		i;
	int		j;
	size_t	lengthtrim;

	i = 0;
	j = ft_strlen(s1) - 1;
	while (checkset(s1[i], set) == 1 && s1[i])
		i++;
	while (checkset(s1[j], set) == 1 && j > i)
		j--;
	lengthtrim = j - i + 1;
	strim = (char *)malloc (sizeof (char) * (lengthtrim + 1));
	if (!strim)
		return (NULL);
	ft_strlcpy(strim, (s1 + i), (lengthtrim + 1));
	return (strim);
}

