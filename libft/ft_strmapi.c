/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:41:25 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/10 17:41:34 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlenconst(const char *str)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		counter++;
		i++;
	}
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstr;
	int		index;
	int		index2;
	int		len;

	len = ft_strlenconst(s);
	newstr = (char *) malloc (sizeof (char) * (len + 1));
	if (!newstr || !s || !f)
		return (NULL);
	index = 0;
	index2 = 0;
	while (index < len)
	{
		newstr[index2] = f(index, s[index]);
		index++;
		index2++;
	}
	newstr[index2] = '\0';
	return (newstr);
}

/*char    f(unsigned int i, char c)
{
    char str;

    str = c + 5;
    return (str);
}

int main(void)
{
    char    *s;
    s = "aaaabbbb";
    char    *newstr;
    newstr = ft_strmapi(s,*f);
    printf("%s\n", newstr);
}*/
