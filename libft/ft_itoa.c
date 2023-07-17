/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:51:33 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/16 15:58:54 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		len = 12;
	if (n <= 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*checkitoa(char *str, int n, int index)
{
	if (n < 0)
	{
		str[0] = 45;
		n = n * (-1);
	}
	if (n == 0)
		str[0] = 48;
	while (n > 0)
	{
		str[index] = 48 + (n % 10);
		n = n / 10;
		index--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		index;

	index = ft_intlen(n);
	if (n == -2147483648)
	{
		str = malloc(sizeof(char) * (index - 1));
		if (!str)
			return (NULL);
		ft_strlcpy(str, "-2147483648", 12);
		return (str);
	}
	else
	{
		str = malloc(sizeof (char) * (index + 1));
		if (!str)
			return (NULL);
		str[index] = '\0';
		index = index - 1;
		str = checkitoa(str, n, index);
	}
	return (str);
}

/*int	main(void)
{
	int n;
  	n = -2144783648LL;
	printf("%s\n", ft_itoa(n));
}*/
