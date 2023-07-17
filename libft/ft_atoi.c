/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:08:22 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/02 18:08:23 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	int	index;
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	index = 0;
	while (nptr[index] == '\t' || nptr[index] == '\n' || nptr[index] == '\v'
		|| nptr[index] == '\f' || nptr[index] == '\r' || nptr[index] == ' ')
		index++;
	if (nptr[index] == '+' || nptr[index] == '-')
	{
		if (nptr[index++] == '-')
			sign = -1;
		else if (nptr[index] == '+' && (nptr[index + 1] == '-'
				|| nptr[index + 1] == '+'))
			return (0);
	}
	while (nptr[index] != '\0' && nptr[index] >= '0' && nptr[index] <= '9')
	{
		result = result * 10 + (nptr[index] - 48);
		index++;
	}
	return ((int)(sign * result));
}

/*int	main(void)
{

	printf("%d\n", ft_atoi("\007 8"));
	printf("%d\n", atoi("\007 8"));  //0  // correct
	
	printf("%d\n", ft_atoi("546:5")); // 546 // correct
	
	printf("%d\n", ft_atoi("-4886")); // -4886
	printf("%d\n", ft_atoi("+548")); //548
	printf("%d\n", ft_atoi("054854")); // 54854
	printf("%d\n", ft_atoi("000074")); //74
	printf("%d\n", ft_atoi("+-54")); // 0
	printf("%d\n", ft_atoi("-+48")); //0
	printf("%d\n", ft_atoi("--47")); //0
	printf("%d\n", ft_atoi("++47")); //0
	printf("%d\n", ft_atoi("+47+5")); //0
	printf("%d\n", ft_atoi("-47-5")); //-47
	printf("%d\n", ft_atoi("\e475")); //0
	printf("%d\n", ft_atoi("\t\n\r\v\f  469 \n")); //469
	printf("%d\n", ft_atoi("-2147483648")); //-2147483648
	printf("%d\n", ft_atoi("2147483647")); //2147483647
	printf("%d\n", ft_atoi("\t\n\r\v\fd469 \n")); //0
	printf("%d\n", ft_atoi("\n\n\n  -46\b9 \n5d6")); //-46
	printf("%d\n", ft_atoi("")); //0
}*/
