/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:58:54 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/10 18:58:56 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlenconst8(const char *str)
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

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int		index;
	int		len;

	if (!s || !f)
		return ;
	len = ft_strlenconst8(s);
	index = 0;
	while (index < len)
	{
		f(index, &s[index]);
		index++;
	}
}

/*
void    *f(unsigned int i, char* s)
{
    s[i] = s[i] + 2;
}

int main(void)
{
    char    *s;
    s = "aaaabbbb";
    ft_striteri(s, f);
}*/
