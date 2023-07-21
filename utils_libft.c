/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:00:35 by edrouot           #+#    #+#             */
/*   Updated: 2023/07/21 15:29:32 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	long unsigned int	index;

	index = 0;
	if (!s1 || !s2 || n == 0)
		return (0);
	while ((s1[index] != '\0' || s2[index] != '\0') && index < n)
	{
		if (s1[index] == s2[index])
			index++;
		else
			return ((unsigned char)(s1[index]) - (unsigned char)(s2[index]));
	}
	return (0);
}


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


size_t	lengthcombine(char const *s1, char const *s2)
{
	size_t		l1;
	size_t		l2;
	size_t		l3;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	l3 = l1 + l2;
	return (l3);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		l3;
	char		*s3;
	int			sindex;
	size_t		bindex;

	l3 = lengthcombine(s1, s2);
	s3 = (char *)malloc(sizeof(char) * (l3 + 1));
	if (!s3)
		return (NULL);
	sindex = 0;
	bindex = 0;
	while (bindex < ft_strlen(s1))
		s3[bindex++] = s1[sindex++];
	sindex = 0;
	while (bindex < l3)
		s3[bindex++] = s2[sindex++];
	s3[bindex] = '\0';
	return (s3);
}


size_t	lengthstr(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (lengthstr(src));
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	return (lengthstr(src));
}
